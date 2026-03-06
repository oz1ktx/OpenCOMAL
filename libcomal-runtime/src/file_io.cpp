/// @file file_io.cpp
/// COMAL file I/O implementation.

#include "comal_file_io.h"

#include <cstring>

namespace comal::runtime {

// ── FileTable destructor ────────────────────────────────────────────────

FileTable::~FileTable() {
    closeAll();
}

// ── open ────────────────────────────────────────────────────────────────

void FileTable::open(int64_t fno, const std::string& filename,
                     FileMode mode, int64_t reclen, bool read_only) {
    if (files_.count(fno))
        throw ComalError(ErrorCode::Open,
            "File #" + std::to_string(fno) + " is already open");

    const char* fmode;
    switch (mode) {
    case FileMode::Read:   fmode = "r"; break;
    case FileMode::Write:  fmode = "w"; break;
    case FileMode::Append: fmode = "a"; break;
    case FileMode::Random: fmode = read_only ? "rb" : "r+b"; break;
    }

    FILE* fp = std::fopen(filename.c_str(), fmode);
    if (!fp) {
        // For Random mode, try creating the file
        if (mode == FileMode::Random && !read_only) {
            fp = std::fopen(filename.c_str(), "w+b");
        }
        if (!fp)
            throw ComalError(ErrorCode::Open,
                "Cannot open \"" + filename + "\"");
    }

    files_[fno] = FileEntry{fno, fp, mode, read_only, reclen, filename};
}

// ── close ───────────────────────────────────────────────────────────────

void FileTable::close(int64_t fno) {
    if (fno == 0) {
        closeAll();
        return;
    }

    auto it = files_.find(fno);
    if (it == files_.end())
        throw ComalError(ErrorCode::Close,
            "File #" + std::to_string(fno) + " is not open");

    if (it->second.fp)
        std::fclose(it->second.fp);
    files_.erase(it);
}

// ── get ─────────────────────────────────────────────────────────────────

FileEntry& FileTable::get(int64_t fno) {
    auto it = files_.find(fno);
    if (it == files_.end())
        throw ComalError(ErrorCode::Open,
            "File #" + std::to_string(fno) + " is not open");
    return it->second;
}

bool FileTable::isOpen(int64_t fno) const {
    return files_.count(fno) > 0;
}

// ── isEof ───────────────────────────────────────────────────────────────

bool FileTable::isEof(int64_t fno) {
    auto& f = get(fno);
    if (!f.fp) return true;
    int c = std::fgetc(f.fp);
    if (c == EOF) return true;
    std::ungetc(c, f.fp);
    return false;
}

// ── readValue ───────────────────────────────────────────────────────────

Value FileTable::readValue(int64_t fno, Value::Type expected_type) {
    auto& f = get(fno);
    if (!f.fp)
        throw ComalError(ErrorCode::Read, "File #" + std::to_string(fno) + " not readable");

    // Binary read with type tag (matches legacy COMAL format)
    char type_byte;
    if (std::fread(&type_byte, 1, 1, f.fp) != 1)
        throw ComalError(ErrorCode::Eof, "End of file on #" + std::to_string(fno));

    switch (type_byte) {
    case 1: { // V_INT
        long val;
        if (std::fread(&val, sizeof(val), 1, f.fp) != 1)
            throw ComalError(ErrorCode::Read, "Read error on file #" + std::to_string(fno));
        return Value(static_cast<int64_t>(val));
    }
    case 2: { // V_FLOAT
        double val;
        if (std::fread(&val, sizeof(val), 1, f.fp) != 1)
            throw ComalError(ErrorCode::Read, "Read error on file #" + std::to_string(fno));
        return Value(val);
    }
    case 3: { // V_STRING
        long len;
        if (std::fread(&len, sizeof(len), 1, f.fp) != 1)
            throw ComalError(ErrorCode::Read, "Read error on file #" + std::to_string(fno));
        std::string val(len, '\0');
        if (len > 0 && std::fread(val.data(), 1, len, f.fp) != static_cast<size_t>(len))
            throw ComalError(ErrorCode::Read, "Read error on file #" + std::to_string(fno));
        return Value(std::move(val));
    }
    default:
        throw ComalError(ErrorCode::Read,
            "Unknown type byte " + std::to_string((int)type_byte) + " in file #" + std::to_string(fno));
    }
}

// ── writeValue ──────────────────────────────────────────────────────────

void FileTable::writeValue(int64_t fno, const Value& val) {
    auto& f = get(fno);
    if (!f.fp || f.read_only)
        throw ComalError(ErrorCode::Write,
            "File #" + std::to_string(fno) + " not writable");

    // Binary write with type tag (matches legacy COMAL format)
    switch (val.type()) {
    case Value::Type::Int: {
        char type_byte = 1; // V_INT
        std::fwrite(&type_byte, 1, 1, f.fp);
        long v = static_cast<long>(val.asInt());
        std::fwrite(&v, sizeof(v), 1, f.fp);
        break;
    }
    case Value::Type::Float: {
        char type_byte = 2; // V_FLOAT
        std::fwrite(&type_byte, 1, 1, f.fp);
        double v = val.asFloat();
        std::fwrite(&v, sizeof(v), 1, f.fp);
        break;
    }
    case Value::Type::String: {
        char type_byte = 3; // V_STRING
        std::fwrite(&type_byte, 1, 1, f.fp);
        long len = static_cast<long>(val.asString().size());
        std::fwrite(&len, sizeof(len), 1, f.fp);
        if (len > 0)
            std::fwrite(val.asString().data(), 1, len, f.fp);
        break;
    }
    default: break;
    }
}

// ── seek ────────────────────────────────────────────────────────────────

void FileTable::seek(int64_t fno, int64_t recno) {
    auto& f = get(fno);
    if (f.mode != FileMode::Random)
        throw ComalError(ErrorCode::Pos, "Cannot seek on non-RANDOM file");
    if (f.reclen <= 0)
        throw ComalError(ErrorCode::Pos, "File has no record length");

    long offset = static_cast<long>((recno - 1) * f.reclen);
    if (std::fseek(f.fp, offset, SEEK_SET) != 0)
        throw ComalError(ErrorCode::Pos,
            "Seek error on file #" + std::to_string(fno));
}

// ── closeAll ────────────────────────────────────────────────────────────

void FileTable::closeAll() {
    for (auto& [fno, entry] : files_) {
        if (entry.fp) {
            std::fclose(entry.fp);
            entry.fp = nullptr;
        }
    }
    files_.clear();
}

} // namespace comal::runtime

/// @file file_io.cpp
/// COMAL file I/O implementation.

#include "comal_file_io.h"

#include <cstring>
#include <cstdint>
#include <condition_variable>
#include <deque>
#include <memory>
#include <mutex>

namespace comal::runtime {

namespace {

struct QueueState {
    std::mutex mutex;
    std::condition_variable cv;
    std::deque<std::string> messages;
};

class QueueRegistry {
public:
    std::shared_ptr<QueueState> getOrCreate(const std::string& name) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = queues_.find(name);
        if (it != queues_.end()) {
            return it->second;
        }
        auto q = std::make_shared<QueueState>();
        queues_[name] = q;
        return q;
    }

    static QueueRegistry& instance() {
        static QueueRegistry registry;
        return registry;
    }

private:
    std::mutex mutex_;
    std::unordered_map<std::string, std::shared_ptr<QueueState>> queues_;
};

} // namespace

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

    if (mode == FileMode::QueueRead || mode == FileMode::QueueWrite) {
        // Ensure the named queue exists in the shared registry.
        (void)QueueRegistry::instance().getOrCreate(filename);
        files_[fno] = FileEntry{fno, nullptr, mode, false, 0, filename, filename};
        return;
    }

    const char* fmode;
    switch (mode) {
    case FileMode::Read:   fmode = "r"; break;
    case FileMode::Write:  fmode = "w"; break;
    case FileMode::Append: fmode = "a"; break;
    case FileMode::Random: fmode = read_only ? "rb" : "r+b"; break;
    case FileMode::QueueRead:
    case FileMode::QueueWrite:
        fmode = "r";
        break;
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

    files_[fno] = FileEntry{fno, fp, mode, read_only, reclen, filename, ""};
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
    if (f.mode == FileMode::QueueRead || f.mode == FileMode::QueueWrite)
        return false;
    if (!f.fp) return true;
    int c = std::fgetc(f.fp);
    if (c == EOF) return true;
    std::ungetc(c, f.fp);
    return false;
}

// ── readValue ───────────────────────────────────────────────────────────

Value FileTable::readValue(int64_t fno, Value::Type expected_type) {
    auto& f = get(fno);
    if (f.mode == FileMode::QueueRead || f.mode == FileMode::QueueWrite)
        throw ComalError(ErrorCode::Read, "Cannot READ FILE binary data from QUEUE file #" + std::to_string(fno));
    if (!f.fp)
        throw ComalError(ErrorCode::Read, "File #" + std::to_string(fno) + " not readable");

    // Binary read with type tag (matches legacy COMAL format)
    char type_byte;
    if (std::fread(&type_byte, 1, 1, f.fp) != 1)
        throw ComalError(ErrorCode::Eof, "End of file on #" + std::to_string(fno));

    switch (type_byte) {
    case 1: { // V_INT
        int32_t val;
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
        int32_t len;
        if (std::fread(&len, sizeof(len), 1, f.fp) != 1)
            throw ComalError(ErrorCode::Read, "Read error on file #" + std::to_string(fno));
        if (len < 0)
            throw ComalError(ErrorCode::Read, "Negative string length in file #" + std::to_string(fno));
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
    if (f.mode == FileMode::QueueRead || f.mode == FileMode::QueueWrite)
        throw ComalError(ErrorCode::Write, "Cannot WRITE FILE binary data to QUEUE file #" + std::to_string(fno));
    if (!f.fp || f.read_only)
        throw ComalError(ErrorCode::Write,
            "File #" + std::to_string(fno) + " not writable");

    // Binary write with type tag (matches legacy COMAL format)
    switch (val.type()) {
    case Value::Type::Int: {
        char type_byte = 1; // V_INT
        std::fwrite(&type_byte, 1, 1, f.fp);
        int32_t v = static_cast<int32_t>(val.asInt());
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
        int32_t len = static_cast<int32_t>(val.asString().size());
        std::fwrite(&len, sizeof(len), 1, f.fp);
        if (len > 0)
            std::fwrite(val.asString().data(), 1, len, f.fp);
        break;
    }
    default: break;
    }
    
    // Flush to ensure data is written (important for RANDOM file mode)
    std::fflush(f.fp);
}

// ── printText / printNewline / readTextLine ────────────────────────────

void FileTable::printText(int64_t fno, const std::string& text) {
    auto& f = get(fno);
    if (f.mode == FileMode::QueueRead || f.mode == FileMode::QueueWrite)
        throw ComalError(ErrorCode::Write,
            "Queue channels do not support streaming PRINT; use queue message writes");
    if (!f.fp || f.read_only)
        throw ComalError(ErrorCode::Write,
            "File #" + std::to_string(fno) + " not writable");
    if (!text.empty() && std::fputs(text.c_str(), f.fp) == EOF)
        throw ComalError(ErrorCode::Write,
            "Write error on file #" + std::to_string(fno));
}

void FileTable::printNewline(int64_t fno) {
    auto& f = get(fno);
    if (f.mode == FileMode::QueueRead || f.mode == FileMode::QueueWrite)
        throw ComalError(ErrorCode::Write,
            "Queue channels do not support newline writes");
    if (!f.fp || f.read_only)
        throw ComalError(ErrorCode::Write,
            "File #" + std::to_string(fno) + " not writable");
    if (std::fputc('\n', f.fp) == EOF)
        throw ComalError(ErrorCode::Write,
            "Write error on file #" + std::to_string(fno));
}

std::string FileTable::readTextLine(int64_t fno) {
    auto& f = get(fno);
    if (f.mode == FileMode::QueueRead)
        return readQueueMessage(fno);
    if (f.mode == FileMode::QueueWrite)
        throw ComalError(ErrorCode::Read,
            "Queue #" + std::to_string(fno) + " is open for WRITE");
    if (!f.fp)
        throw ComalError(ErrorCode::Read,
            "File #" + std::to_string(fno) + " not readable");
    std::string line;
    int c;
    bool got_char = false;
    while ((c = std::fgetc(f.fp)) != EOF && c != '\n') {
        line += static_cast<char>(c);
        got_char = true;
    }
    if (c == EOF && !got_char)
        throw ComalError(ErrorCode::Eof,
            "End of file on #" + std::to_string(fno));
    // Strip trailing CR for Windows-format files
    if (!line.empty() && line.back() == '\r')
        line.pop_back();
    return line;
}

void FileTable::writeQueueMessage(int64_t fno, const std::string& text) {
    auto& f = get(fno);
    if (f.mode != FileMode::QueueWrite)
        throw ComalError(ErrorCode::Write,
            "File #" + std::to_string(fno) + " is not open as QUEUE WRITE");

    auto queue = QueueRegistry::instance().getOrCreate(f.queue_name);
    {
        std::lock_guard<std::mutex> lock(queue->mutex);
        queue->messages.push_back(text);
    }
    queue->cv.notify_one();
}

std::string FileTable::readQueueMessage(int64_t fno) {
    auto& f = get(fno);
    if (f.mode != FileMode::QueueRead)
        throw ComalError(ErrorCode::Read,
            "File #" + std::to_string(fno) + " is not open as QUEUE READ");

    auto queue = QueueRegistry::instance().getOrCreate(f.queue_name);
    std::unique_lock<std::mutex> lock(queue->mutex);
    queue->cv.wait(lock, [&queue]() { return !queue->messages.empty(); });
    std::string msg = std::move(queue->messages.front());
    queue->messages.pop_front();
    return msg;
}

// ── seek ────────────────────────────────────────────────────────────────

void FileTable::seek(int64_t fno, int64_t recno) {
    auto& f = get(fno);
    if (f.mode == FileMode::QueueRead || f.mode == FileMode::QueueWrite)
        throw ComalError(ErrorCode::Pos, "Cannot seek on QUEUE file");
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

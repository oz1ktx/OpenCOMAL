#ifndef COMAL_FILE_IO_H
#define COMAL_FILE_IO_H

/// @file comal_file_io.h
/// File I/O management for the COMAL runtime.
/// Replaces legacy file_rec linked list.

#include <cstdint>
#include <cstdio>
#include <string>
#include <unordered_map>

#include "comal_error.h"
#include "comal_value.h"

namespace comal::runtime {

/// Open modes matching COMAL semantics
enum class FileMode {
    Read,
    Write,
    Append,
    Random
};

/// One open file descriptor
struct FileEntry {
    int64_t comal_fno;       // COMAL file number (the # number)
    FILE* fp{nullptr};       // C stream
    FileMode mode{FileMode::Read};
    bool read_only{false};
    int64_t reclen{0};       // record length for RANDOM files
    std::string filename;    // for diagnostics
};

/// Manages all open COMAL files.
class FileTable {
public:
    ~FileTable();

    /// OPEN FILE fno, filename, mode [RECLEN rlen] [READ]
    void open(int64_t fno, const std::string& filename, FileMode mode,
              int64_t reclen = 0, bool read_only = false);

    /// CLOSE FILE fno  (fno == 0 → close all)
    void close(int64_t fno);

    /// Look up an open file. Throws ComalError if not found.
    FileEntry& get(int64_t fno);

    /// Check if a file number is open.
    bool isOpen(int64_t fno) const;

    /// Check EOF on a file.
    bool isEof(int64_t fno);

    /// READ# / WRITE# binary I/O
    Value readValue(int64_t fno, Value::Type expected_type);
    void writeValue(int64_t fno, const Value& val);

    /// Position a random-access file
    void seek(int64_t fno, int64_t recno);

    /// Close all files (called at program end).
    void closeAll();

private:
    std::unordered_map<int64_t, FileEntry> files_;
};

} // namespace comal::runtime

#endif // COMAL_FILE_IO_H

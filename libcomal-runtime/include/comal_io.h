#ifndef COMAL_IO_H
#define COMAL_IO_H

/// @file comal_io.h
/// Abstract I/O interface for the COMAL runtime.
///
/// The runtime calls these methods instead of writing to stdout/stdin
/// directly.  Two backends are provided:
///
///   - TerminalIO  (default) — uses std::cout / std::cin / ANSI escapes.
///   - (GUI)       — Qt signals/slots for the IDE (in comal-ide/).
///
/// SELECT OUTPUT/INPUT to files is handled at a higher level in the
/// interpreter; this interface covers interactive console I/O only.

#include <string>
#include <memory>

namespace comal::runtime {

class IOInterface {
public:
    virtual ~IOInterface() = default;

    /// Write text to the output area.
    virtual void print(const std::string& text) = 0;

    /// Read a line of input.  The prompt (if any) has already been
    /// printed via print() before this is called.
    /// Returns the user's input (without trailing newline).
    virtual std::string readLine() = 0;

    /// Clear the screen / output area.  (PAGE command)
    virtual void clearScreen() = 0;

    /// Position the cursor at (row, col).  1-based.  (CURSOR command)
    virtual void setCursor(int row, int col) = 0;
};

/// Default terminal backend — uses std::cout, std::cin, ANSI escapes.
class TerminalIO : public IOInterface {
public:
    void print(const std::string& text) override;
    std::string readLine() override;
    void clearScreen() override;
    void setCursor(int row, int col) override;
};

} // namespace comal::runtime

#endif // COMAL_IO_H

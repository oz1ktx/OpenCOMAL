#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace comal::docs {

struct KeywordDocEntry {
    const char* keyword;
    const char* category;
    const char* description;
};

inline const std::vector<KeywordDocEntry>& keywordDocEntries() {
    static const std::vector<KeywordDocEntry> entries = {
        {"PRINT", "I/O and Files", "Print values to the output device."},
        {"INPUT", "I/O and Files", "Read a value from the user."},
        {"IF", "Control Flow", "Conditional execution. Use with THEN, ELSE, ENDIF."},
        {"THEN", "Control Flow", "Introduces the true-branch of IF."},
        {"ELSE", "Control Flow", "Introduces the false-branch of IF."},
        {"ELIF", "Control Flow", "Else-if branch (IF ... ELIF ... ENDIF)."},
        {"END", "Control Flow", "Terminates a program, or closes a block (END IF, END FOR, END PROC, ...)."},
        {"ENDIF", "Control Flow", "Closes a multi-line IF block."},
        {"FOR", "Control Flow", "Counted loop: FOR var := start TO stop [STEP inc]."},
        {"TO", "Control Flow", "Upper bound in a FOR loop."},
        {"DOWNTO", "Control Flow", "Descending FOR direction: FOR i := hi DOWNTO lo."},
        {"STEP", "Control Flow", "Increment value in a FOR loop."},
        {"NEXT", "Control Flow", "End of a FOR loop body (or ENDFOR)."},
        {"ENDFOR", "Control Flow", "End of a FOR loop body."},
        {"WHILE", "Control Flow", "Loop while a condition is true."},
        {"ENDWHILE", "Control Flow", "End of a WHILE loop body."},
        {"REPEAT", "Control Flow", "Loop body that repeats UNTIL a condition is true."},
        {"UNTIL", "Control Flow", "Condition that terminates a REPEAT loop."},
        {"DO", "Control Flow", "Start of a DO block (used with LOOP/UNTIL forms)."},
        {"IN", "Control Flow", "Membership/iteration helper keyword in selected statements."},
        {"CASE", "Control Flow", "Multi-way branch: CASE expr OF ... ENDCASE."},
        {"WHEN", "Control Flow", "Branch inside a CASE block."},
        {"OTHERWISE", "Control Flow", "Default branch inside a CASE block."},
        {"ENDCASE", "Control Flow", "End of a CASE block."},
        {"OF", "Control Flow", "Part of CASE ... OF."},
        {"EXIT", "Control Flow", "Exit a loop early."},
        {"LOOP", "Control Flow", "Infinite loop (LOOP ... ENDLOOP / EXIT WHEN)."},
        {"ENDLOOP", "Control Flow", "End of a LOOP block."},
        {"NULL", "Control Flow", "No-operation statement."},
        {"PROC", "Procedures", "Define a procedure: PROC name[(params)] ... ENDPROC."},
        {"ENDPROC", "Procedures", "End of a PROC definition."},
        {"FUNC", "Procedures", "Define a function: FUNC name[(params)] ... ENDFUNC."},
        {"ENDFUNC", "Procedures", "End of a FUNC definition."},
        {"RETURN", "Procedures", "Return a value from a FUNC."},
        {"EXEC", "Procedures", "Execute a procedure call."},
        {"LOCAL", "Procedures", "Declare local variables in a PROC or FUNC."},
        {"CLOSED", "Procedures", "Mark a PROC/FUNC as closed-scope (no access to outer variables)."},
        {"IMPORT", "Procedures", "Import names into a CLOSED procedure."},
        {"GLOBAL", "Procedures", "Alias for IMPORT in CLOSED procedure declarations."},
        {"EXPORT", "Procedures", "Export names from a CLOSED procedure."},
        {"LET", "Procedures", "Assignment (optional keyword, e.g. LET x := 5)."},
        {"REF", "Procedures", "Pass-by-reference parameter qualifier."},
        {"DYNAMIC", "Procedures", "Dynamic variable/array storage attribute."},
        {"STATIC", "Procedures", "Static variable/array storage attribute."},
        {"EXTERNAL", "Procedures", "Declare symbol defined in another module."},
        {"DIM", "Variables and Data", "Dimension (allocate) an array."},
        {"DATA", "Variables and Data", "Define inline data for READ statements."},
        {"READ", "Variables and Data", "Read the next value from a DATA list."},
        {"READ ONLY", "Variables and Data", "Open resource/file in read-only mode."},
        {"WRITE", "Variables and Data", "Write values to a file stream or device."},
        {"RESTORE", "Variables and Data", "Reset the DATA pointer."},
        {"OPEN", "I/O and Files", "Open a file handle for INPUT/OUTPUT/READ/WRITE."},
        {"CLOSE", "I/O and Files", "Close an open file handle."},
        {"FILE", "I/O and Files", "File-channel designator keyword (often used with #)."},
        {"APPEND", "I/O and Files", "Open/write mode that appends to an existing file."},
        {"SELECT", "I/O and Files", "Select output device."},
        {"SELECT INPUT", "I/O and Files", "Select default input channel/device."},
        {"SELECT OUTPUT", "I/O and Files", "Select default output channel/device."},
        {"PAGE", "I/O and Files", "Clear the screen."},
        {"CURSOR", "I/O and Files", "Position the cursor: CURSOR row, col."},
        {"ZONE", "I/O and Files", "Set the print zone width."},
        {"TAB", "I/O and Files", "Move to a specific column."},
        {"SPC", "I/O and Files", "Output a number of spaces."},
        {"SPC$", "I/O and Files", "String-valued spacing function."},
        {"USING", "I/O and Files", "Formatted output: PRINT USING format$ ; values."},
        {"UNIT", "I/O and Files", "Current/default unit number."},
        {"UNIT$", "I/O and Files", "Current/default unit name/path."},
        {"KEY$", "I/O and Files", "Last key input as a string."},
        {"INKEY$", "I/O and Files", "Non-blocking single-character input."},
        {"DIR", "I/O and Files", "Directory command or listing keyword."},
        {"DIR$", "I/O and Files", "Directory listing/info function returning string."},
        {"CHDIR", "I/O and Files", "Change current directory."},
        {"MKDIR", "I/O and Files", "Create a directory."},
        {"RMDIR", "I/O and Files", "Remove a directory."},
        {"NAME", "I/O and Files", "Rename a file."},
        {"DELETE", "I/O and Files", "Delete program lines."},
        {"LEN", "Strings", "Length of a string, or number of elements in an array."},
        {"LEFT$", "Strings", "Left substring: LEFT$(str, n)."},
        {"RIGHT$", "Strings", "Right substring: RIGHT$(str, n)."},
        {"MID$", "Strings", "Middle substring: MID$(str, start, length)."},
        {"SPLIT$", "Strings", "Split a string into parts: SPLIT$(str, delim, index)."},
        {"LOWER$", "Strings", "Convert a string to lowercase."},
        {"UPPER$", "Strings", "Convert a string to uppercase."},
        {"CHR$", "Strings", "Character corresponding to an ASCII code."},
        {"STR$", "Strings", "String representation of a number."},
        {"VAL", "Strings", "Numeric value of a string."},
        {"ORD", "Strings", "Character code of a single-character string."},
        {"RANDOM", "Math and Logic", "Randomize the random number generator."},
        {"RND", "Math and Logic", "Random number function."},
        {"PI", "Math and Logic", "Mathematical constant pi."},
        {"TRUE", "Math and Logic", "Boolean true constant."},
        {"FALSE", "Math and Logic", "Boolean false constant."},
        {"INT", "Math and Logic", "Convert to integer (truncate toward zero)."},
        {"ABS", "Math and Logic", "Absolute value."},
        {"SGN", "Math and Logic", "Sign of a numeric expression (-1, 0, 1)."},
        {"ROUND", "Math and Logic", "Round to nearest integer/value."},
        {"FRAC", "Math and Logic", "Fractional part of a number."},
        {"SIN", "Math and Logic", "Sine function."},
        {"COS", "Math and Logic", "Cosine function."},
        {"TAN", "Math and Logic", "Tangent function."},
        {"ATN", "Math and Logic", "Arc tangent function."},
        {"ASN", "Math and Logic", "Arc sine function."},
        {"ACS", "Math and Logic", "Arc cosine function."},
        {"EXP", "Math and Logic", "Exponential function e^x."},
        {"LOG", "Math and Logic", "Natural logarithm."},
        {"LN", "Math and Logic", "Natural logarithm (alias)."},
        {"RAD", "Math and Logic", "Convert degrees to radians mode/value."},
        {"DEG", "Math and Logic", "Convert radians to degrees mode/value."},
        {"SQR", "Math and Logic", "Square root."},
        {"DIV", "Math and Logic", "Integer division operator."},
        {"MOD", "Math and Logic", "Remainder operator."},
        {"AND", "Math and Logic", "Logical conjunction operator."},
        {"AND THEN", "Math and Logic", "Short-circuit logical conjunction."},
        {"OR", "Math and Logic", "Logical disjunction operator."},
        {"OR THEN", "Math and Logic", "Short-circuit logical disjunction."},
        {"NOT", "Math and Logic", "Logical negation operator."},
        {"EOD", "Runtime and Errors", "End-of-DATA indicator."},
        {"EOF", "Runtime and Errors", "End-of-file indicator/function."},
        {"EOR", "Runtime and Errors", "Logical exclusive OR."},
        {"ERR", "Runtime and Errors", "Current runtime error code."},
        {"ERRLINE", "Runtime and Errors", "Line number of the current runtime error."},
        {"ERRTEXT$", "Runtime and Errors", "Text message for the current runtime error."},
        {"TRAP", "Runtime and Errors", "Set up an error/escape handler: TRAP ESC/ERR."},
        {"ESC", "Runtime and Errors", "Escape condition keyword used with TRAP."},
        {"ESCAPE", "Runtime and Errors", "Equivalent to pressing the escape key."},
        {"HANDLER", "Runtime and Errors", "Error/escape handler block."},
        {"ENDTRAP", "Runtime and Errors", "End of a TRAP block."},
        {"RETRY", "Runtime and Errors", "Retry after handling an error/escape in a TRAP handler."},
        {"STOP", "Runtime and Errors", "Halt program execution."},
        {"DRAW", "Graphics and Sound", "Execute a graphics command: DRAW subcommand args."},
        {"TONE", "Graphics and Sound", "Play a simple sine tone: TONE frequency duration (ms)."},
        {"PLAY", "Graphics and Sound", "Play a melody or instrument sequence (MML/MIDI-like string)."},
        {"SLEEP", "Graphics and Sound", "Pause execution for a number of milliseconds."},
        {"SYS", "System", "Execute a system command."},
        {"SYS$", "System", "System information: SYS$(info)."},
        {"OS", "System", "Operating-system command statement."},
        {"PASS", "System", "Alias for OS command statement."},
    };
    return entries;
}

inline const std::unordered_map<std::string, std::string>& keywordDocsMap() {
    static const std::unordered_map<std::string, std::string> docs = [] {
        std::unordered_map<std::string, std::string> result;
        result.reserve(keywordDocEntries().size());
        for (const auto& entry : keywordDocEntries()) {
            result.emplace(entry.keyword, entry.description);
        }
        return result;
    }();
    return docs;
}

inline const std::vector<std::string>& completionKeywords() {
    static const std::vector<std::string> keywords = [] {
        std::vector<std::string> result;
        result.reserve(keywordDocEntries().size());
        for (const auto& entry : keywordDocEntries()) {
            result.emplace_back(entry.keyword);
        }
        return result;
    }();
    return keywords;
}

} // namespace comal::docs
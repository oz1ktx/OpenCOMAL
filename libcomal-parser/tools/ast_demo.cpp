#include "comal_ast_modern.h"
#include "comal_memory.h"
#include <iostream>
#include <cassert>
#include <charconv>
#include <array>

using namespace comal;

// ============================================================================
// Part 1: Expression tree demo (from Phase 1)
// ============================================================================
static void demo_expressions() {
    std::cout << "=== Part 1: Expression Trees ===\n\n";

    // Build expression tree: (10 + 20) * 3
    Expression* ten = make_int_expr(PARSE_POOL, 10);
    Expression* twenty = make_int_expr(PARSE_POOL, 20);
    Expression* add = make_binary_expr(PARSE_POOL, '+', ten, twenty);

    Expression* three = make_int_expr(PARSE_POOL, 3);
    Expression* multiply = make_binary_expr(PARSE_POOL, '*', add, three);

    std::cout << "Built expression tree: (10 + 20) * 3\n\n";

    // Visit the expression tree
    std::cout << "Expression tree traversal:\n";
    int depth = 0;
    visit_expression(multiply, [&depth](Expression* expr) {
        for (int i = 0; i < depth; ++i) std::cout << "  ";

        switch (expr->opType()) {
            case OpType::IntNum:
                std::cout << "INT: " << expr->asNum() << "\n";
                break;
            case OpType::Binary:
                std::cout << "BINARY: " << char(expr->op()) << "\n";
                depth++;
                break;
            default:
                std::cout << "OTHER\n";
                break;
        }
    });
    std::cout << "\n";

    // Build and reverse an expression list
    auto* exp1 = make_int_expr(PARSE_POOL, 1);
    auto* exp2 = make_int_expr(PARSE_POOL, 2);
    auto* exp3 = make_int_expr(PARSE_POOL, 3);

    ExpList* list = nullptr;
    list = cons_exp(PARSE_POOL, exp1, list);
    list = cons_exp(PARSE_POOL, exp2, list);
    list = cons_exp(PARSE_POOL, exp3, list);

    std::cout << "Expression list (reversed): ";
    for (ExpList* node = list; node != nullptr; node = node->next()) {
        std::cout << node->exp()->asNum();
        if (node->next()) std::cout << ", ";
    }
    std::cout << "\n";

    list = reverse_exp_list(list);

    std::cout << "Expression list (after reverse): ";
    for (ExpList* node = list; node != nullptr; node = node->next()) {
        std::cout << node->exp()->asNum();
        if (node->next()) std::cout << ", ";
    }
    std::cout << "\n";

    std::cout << "List length: " << list_length(list) << "\n";

    // Type-safe variant access
    if (auto* num_ptr = std::get_if<int64_t>(&ten->data())) {
        std::cout << "Type-safe variant access: ten = " << *num_ptr << " ✓\n";
    }

    // Float expressions - plain double, no source text baggage
    auto* pi = make_float_expr(PARSE_POOL, 3.14159265358979323846);
    assert(pi->opType() == OpType::Float);
    assert(pi->asFloat() == 3.14159265358979323846);

    // Demonstrate shortest round-trip formatting with std::to_chars
    std::array<char, 32> buf{};
    auto [ptr, ec] = std::to_chars(buf.data(), buf.data() + buf.size(),
                                   pi->asFloat());
    assert(ec == std::errc{});
    std::string_view fstr(buf.data(), static_cast<size_t>(ptr - buf.data()));
    std::cout << "Float (shortest round-trip): " << fstr << " ✓\n";

    auto* half = make_float_expr(PARSE_POOL, 0.5);
    assert(half->asFloat() == 0.5);

    // Verify variant holds double, not the old Double struct
    assert(std::holds_alternative<double>(pi->data()));
    std::cout << "Float stored as plain double (no text member) ✓\n";

    std::cout << "\n";
}

// ============================================================================
// Part 2: Statement / ComalLine demo (Phase 2 - NEW)
// ============================================================================
static void demo_statements() {
    std::cout << "=== Part 2: Statements (ComalLine) ===\n\n";

    // ---- 2a: FOR statement ----
    // FOR i := 1 TO 10 STEP 2
    auto* lval = make_int_expr(PARSE_POOL, 0);   // placeholder for 'i'
    auto* from = make_int_expr(PARSE_POOL, 1);
    auto* to   = make_int_expr(PARSE_POOL, 10);
    auto* step = make_int_expr(PARSE_POOL, 2);

    auto* for_line = make_for_line(PARSE_POOL, 100, lval, from, 1, to, step);

    assert(for_line->command() == StatementType::For);
    assert(for_line->lineNumber() == 100);
    assert(for_line->asFor().from->asNum() == 1);
    assert(for_line->asFor().to->asNum() == 10);
    assert(for_line->asFor().step->asNum() == 2);
    std::cout << "FOR i:=1 TO 10 STEP 2  [line " << for_line->lineNumber()
              << "]  ✓\n";

    // ---- 2b: IF statement ----
    // IF x > 5 THEN ...
    auto* cond = make_binary_expr(PARSE_POOL, '>', make_int_expr(PARSE_POOL, 0),
                                  make_int_expr(PARSE_POOL, 5));
    auto* if_line = make_if_line(PARSE_POOL, 200, cond);

    assert(if_line->command() == StatementType::If);
    assert(if_line->asIfWhile().exp != nullptr);
    std::cout << "IF x>5 THEN ...        [line " << if_line->lineNumber()
              << "]  ✓\n";

    // ---- 2c: WHILE statement ----
    auto* wcond = make_binary_expr(PARSE_POOL, '<',
                                   make_int_expr(PARSE_POOL, 0),
                                   make_int_expr(PARSE_POOL, 100));
    auto* while_line = make_while_line(PARSE_POOL, 300, wcond);

    assert(while_line->command() == StatementType::While);
    std::cout << "WHILE x<100 DO ...     [line " << while_line->lineNumber()
              << "]  ✓\n";

    // ---- 2d: PRINT statement ----
    // PRINT "Hello"; 42
    auto* hello_str = make_int_expr(PARSE_POOL, 0); // placeholder
    auto* num42     = make_int_expr(PARSE_POOL, 42);
    auto* plist = pool_new<PrintList>(PARSE_POOL, num42, 0, nullptr);
    plist = pool_new<PrintList>(PARSE_POOL, hello_str, ';', plist);

    auto* print_line = make_print_line(PARSE_POOL, 400, plist);

    assert(print_line->command() == StatementType::Print);
    assert(print_line->asPrint().printroot != nullptr);
    assert(list_length(print_line->asPrint().printroot) == 2);
    std::cout << "PRINT \"Hello\"; 42     [line " << print_line->lineNumber()
              << "]  ✓\n";

    // ---- 2e: Simple statements (no data) ----
    auto* end_line   = make_line(PARSE_POOL, 500, StatementType::End);
    auto* null_line  = make_line(PARSE_POOL, 510, StatementType::Null);
    auto* retry_line = make_line(PARSE_POOL, 520, StatementType::Retry);

    assert(end_line->command() == StatementType::End);
    assert(null_line->command() == StatementType::Null);
    assert(retry_line->command() == StatementType::Retry);
    std::cout << "END / NULL / RETRY     [lines 500-520]  ✓\n";

    // ---- 2f: TRAP ESC statement ----
    auto* trap_line = make_line(PARSE_POOL, 600, StatementType::Trap,
                                ComalLine::Contents{TrapRec{1}});
    assert(trap_line->asTrap().esc == 1);
    std::cout << "TRAP ESC               [line " << trap_line->lineNumber()
              << "]  ✓\n";

    // ---- 2g: End markers ----
    auto* endif_line   = make_line(PARSE_POOL, 700, StatementType::EndIf);
    auto* endfor_line  = make_line(PARSE_POOL, 710, StatementType::EndFor);
    auto* endwhile_line= make_line(PARSE_POOL, 720, StatementType::EndWhile);

    assert(endif_line->command() == StatementType::EndIf);
    assert(endfor_line->command() == StatementType::EndFor);
    assert(endwhile_line->command() == StatementType::EndWhile);
    std::cout << "ENDIF / ENDFOR / ENDWHILE  ✓\n";

    std::cout << "\n";

    // ---- 2h: Link lines into a program ----
    std::cout << "--- Linked program listing ---\n";
    for_line->setNext(if_line);
    if_line->setNext(print_line);
    print_line->setNext(end_line);

    int count = 0;
    visit_lines(for_line, [&count](ComalLine* line) {
        std::cout << "  " << line->lineNumber() << ": ";
        switch (line->command()) {
            case StatementType::For:   std::cout << "FOR ..."; break;
            case StatementType::If:    std::cout << "IF ..."; break;
            case StatementType::Print: std::cout << "PRINT ..."; break;
            case StatementType::End:   std::cout << "END"; break;
            default: std::cout << "???"; break;
        }
        std::cout << "\n";
        ++count;
    });
    assert(count == 4);
    std::cout << "Program traversal (" << count << " lines)  ✓\n";

    // ---- 2i: Variant type safety ----
    std::cout << "\nVariant type safety:\n";
    bool caught = false;
    try {
        // for_line contains ForRec, not PrintRec - should throw
        [[maybe_unused]] auto& bad = for_line->asPrint();
    } catch (const std::bad_variant_access&) {
        caught = true;
    }
    assert(caught);
    std::cout << "  bad_variant_access on type mismatch  ✓\n";

    // Correct access via std::get_if
    if (auto* fr = std::get_if<ForRec>(&for_line->contents())) {
        std::cout << "  get_if<ForRec> on FOR line: from="
                  << fr->from->asNum() << " to=" << fr->to->asNum() << "  ✓\n";
    }
    std::cout << "\n";
}

// ============================================================================
int main() {
    std::cout << "=== Modern COMAL AST Demo ===\n\n";

    demo_expressions();
    demo_statements();

    std::cout << "=== All demos passed ===\n";
    return 0;
}

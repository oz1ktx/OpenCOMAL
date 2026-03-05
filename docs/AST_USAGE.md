# Modern AST Usage Examples

## Creating Modern AST Nodes

### Example 1: Creating an integer expression

```cpp
#include "comal_ast_modern.h"
#include "comal_memory.h"

// Allocate from parse pool using placement new
using namespace comal;

// Integer constant: 42
auto* expr = pool_new<Expression>(PARSE_POOL, 
    OpType::IntNum, 
    0,  // op not used for constants
    Expression::Data{int64_t{42}});
```

### Example 2: Creating a binary expression (addition)

```cpp
// Create: 10 + 20
auto* left = pool_new<Expression>(PARSE_POOL, 
    OpType::IntNum, 0,
    Expression::Data{int64_t{10}});

auto* right = pool_new<Expression>(PARSE_POOL,
    OpType::IntNum, 0,
    Expression::Data{int64_t{20}});

TwoExp addPair{left, right};

auto* addExpr = pool_new<Expression>(PARSE_POOL,
    OpType::Binary,
    '+',  // operator
    Expression::Data{addPair});
```

### Example 3: Creating an expression list

```cpp
// Create list [1, 2, 3]
auto* expr3 = pool_new<Expression>(PARSE_POOL, OpType::IntNum, 0, 
    Expression::Data{int64_t{3}});
auto* list3 = pool_new<ExpList>(PARSE_POOL, expr3);

auto* expr2 = pool_new<Expression>(PARSE_POOL, OpType::IntNum, 0,
    Expression::Data{int64_t{2}});
auto* list2 = pool_new<ExpList>(PARSE_POOL, expr2, list3);

auto* expr1 = pool_new<Expression>(PARSE_POOL, OpType::IntNum, 0,
    Expression::Data{int64_t{1}});
auto* list1 = pool_new<ExpList>(PARSE_POOL, expr1, list2);

// list1 is the head
```

### Example 4: Using ParseTree RAII wrapper

```cpp
// Create a parse tree that owns the pool
mem_pool* pool = /* get pool somehow */;
auto* root_expr = pool_new<Expression>(/* ... */);

ParseTree tree(pool, root_expr);

// Use the tree...
Expression* root = static_cast<Expression*>(tree.root());

// Pool is automatically freed when tree goes out of scope
```

## Pattern: Accessing Expression Data

```cpp
void process_expression(const Expression* expr) {
    switch (expr->opType()) {
        case OpType::IntNum: {
            int64_t value = expr->asNum();
            std::cout << "Integer: " << value << "\n";
            break;
        }
        
        case OpType::Float: {
            const auto& fval = expr->asFloat();
            std::cout << "Float: " << fval.val << "\n";
            break;
        }
        
        case OpType::Binary: {
            const auto& twoexp = expr->asTwoExp();
            std::cout << "Binary op: " << char(expr->op()) << "\n";
            process_expression(twoexp.exp1);  // recurse
            process_expression(twoexp.exp2);
            break;
        }
        
        case OpType::String: {
            string* str = expr->asString();
            std::cout << "String: " << std::string_view(str->s, str->len) << "\n";
            break;
        }
        
        default:
            std::cout << "Other type\n";
            break;
    }
}
```

## Pattern: Iterating Lists

```cpp
void print_exp_list(const ExpList* list) {
    for (const ExpList* node = list; node != nullptr; node = node->next()) {
        process_expression(node->exp());
    }
}
```

## Ownership Rules

- **Owned pointers**: Parent is responsible for children. Pool cleanup handles deallocation.
- **Borrowed pointers**: Reference to objects owned elsewhere (e.g., symbol table).
- **No manual delete**: Pool cleanup frees all memory in bulk.

Example:
```cpp
Expression* parent = pool_new<Expression>(
    PARSE_POOL, OpType::Binary, '+',
    Expression::Data{TwoExp{left, right}}  // parent owns left & right
);

// left and right are now owned by parent
// They'll be freed when the pool is freed
```

## Migration Strategy

During the transition from legacy C structs:

1. **Parse with legacy code** → produces `struct expression*`
2. **Convert to modern** → `convert_expression(old_exp)` creates `Expression*`
3. **Work with modern API** → type-safe, clean interface
4. **Convert back if needed** → `convert_to_legacy_expression(new_exp)`

Eventually, the parser will produce modern types directly.

## Qt Integration Notes

The raw pointer + parent ownership model matches Qt perfectly:

```cpp
// Qt style
QLabel* label = new QLabel("Text", parent);
// parent owns label, deleted when parent is deleted

// Comal style
Expression* expr = pool_new<Expression>(PARSE_POOL, /*...*/);
// pool owns expr, freed when pool is freed
```

Both use "parent owns children" with bulk cleanup.

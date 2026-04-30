/// @file test_scene_model.cpp
/// Tests for Scene, Group, and command execution on the scene model.

#include "comal_scene_model.h"
#include "comal_graphics_commands.h"
#include <cassert>
#include <cmath>
#include <iostream>
#include <string>

using namespace comal::graphics;

static int tests_passed = 0;
static int tests_failed = 0;

#define TEST(name)                                                \
    do {                                                          \
        std::cout << "  " #name "... ";                           \
        std::cout.flush();                                        \
    } while (0)

#define PASS()                                                    \
    do {                                                          \
        std::cout << "OK\n";                                      \
        ++tests_passed;                                           \
    } while (0)

#define FAIL(msg)                                                 \
    do {                                                          \
        std::cout << "FAIL: " << (msg) << "\n";                   \
        ++tests_failed;                                           \
    } while (0)

#define ASSERT(cond, msg)                                         \
    do {                                                          \
        if (!(cond)) { FAIL(msg); return; }                       \
    } while (0)

#define NEAR(a, b) (std::abs((a) - (b)) < 1e-9)

// ── Helper: make a ParsedCommand ────────────────────────────────────────

static ParsedCommand makeCmd(const std::string& cmd,
                             std::vector<double> args,
                             std::vector<std::string> group = {}) {
    ParsedCommand pc;
    pc.command = cmd;
    pc.args = std::move(args);
    pc.groupPath = std::move(group);
    pc.lineNo = 1;
    return pc;
}

static ParsedCommand makeTextCmd(double x, double y, const std::string& text,
                                 std::vector<std::string> group = {}) {
    ParsedCommand pc;
    pc.command = "text";
    pc.args = {x, y};
    pc.stringArgs = {text};
    pc.groupPath = std::move(group);
    pc.lineNo = 1;
    return pc;
}

// ── Group tests ─────────────────────────────────────────────────────────

static void test_group_find_or_create() {
    TEST(group_find_or_create);
    Group root;
    root.name = "root";

    Group* a = root.findOrCreateChild("A");
    ASSERT(a != nullptr,     "should create A");
    ASSERT(a->name == "A",   "name should be A");
    ASSERT(root.children.size() == 1, "one child");

    Group* a2 = root.findOrCreateChild("A");
    ASSERT(a2 == a,          "should return same pointer");
    ASSERT(root.children.size() == 1, "still one child");

    root.findOrCreateChild("B");
    ASSERT(root.children.size() == 2, "two children");
    PASS();
}

static void test_group_find_child() {
    TEST(group_find_child);
    Group root;
    ASSERT(root.findChild("X") == nullptr, "empty group returns null");

    root.findOrCreateChild("X");
    ASSERT(root.findChild("X") != nullptr, "should find X");
    ASSERT(root.findChild("Y") == nullptr, "should not find Y");
    PASS();
}

static void test_group_clear() {
    TEST(group_clear);
    Group root;
    root.findOrCreateChild("A");
    root.findOrCreateChild("B");
    root.shapes.push_back(Shape{LineShape{0,0,1,1}});

    root.clear();
    ASSERT(root.shapes.empty(),   "shapes cleared");
    ASSERT(root.children.empty(), "children cleared");
    ASSERT(root.childIndex.empty(), "index cleared");
    PASS();
}

// ── Scene tests ─────────────────────────────────────────────────────────

static void test_scene_resolve_group_empty() {
    TEST(scene_resolve_group_empty);
    Scene scene;
    Group* g = scene.resolveGroup({});
    ASSERT(g == &scene.root(), "empty path resolves to root");
    PASS();
}

static void test_scene_resolve_group_nested() {
    TEST(scene_resolve_group_nested);
    Scene scene;
    Group* g = scene.resolveGroup({"Ship", "Engine"});
    ASSERT(g != nullptr, "should create nested group");
    ASSERT(g->name == "Engine", "leaf name");

    // Verify hierarchy
    Group* ship = scene.root().findChild("Ship");
    ASSERT(ship != nullptr, "Ship should exist");
    ASSERT(ship->findChild("Engine") == g, "Engine should be child of Ship");
    PASS();
}

static void test_scene_resolve_group_idempotent() {
    TEST(scene_resolve_group_idempotent);
    Scene scene;
    Group* g1 = scene.resolveGroup({"A", "B"});
    Group* g2 = scene.resolveGroup({"A", "B"});
    ASSERT(g1 == g2, "same path should resolve to same group");
    PASS();
}

static void test_scene_clear() {
    TEST(scene_clear);
    Scene scene;
    scene.resolveGroup({"X"});
    scene.root().shapes.push_back(Shape{CircleShape{0,0,5}});

    scene.clear();
    ASSERT(scene.root().shapes.empty(),   "shapes cleared");
    ASSERT(scene.root().children.empty(), "children cleared");
    PASS();
}

static void test_scene_make_shape() {
    TEST(scene_make_shape);
    Scene scene;
    scene.strokeColor = Color{255, 0, 0};
    scene.hasStroke = true;
    scene.fillColor = Color{0, 255, 0};
    scene.hasFill = false;
    scene.lineWidth = 3.0;

    Shape s = scene.makeShape(CircleShape{10, 20, 5});
    ASSERT(s.strokeColor == Color(255, 0, 0), "stroke color");
    ASSERT(s.hasStroke == true, "has stroke");
    ASSERT(s.fillColor == Color(0, 255, 0), "fill color");
    ASSERT(s.hasFill == false, "no fill");
    ASSERT(NEAR(s.lineWidth, 3.0), "line width");
    PASS();
}

// ── executeCommand tests: shapes ────────────────────────────────────────

static void test_exec_circle() {
    TEST(exec_circle);
    Scene scene;
    auto err = executeCommand(scene, makeCmd("circle", {100, 200, 50}));
    ASSERT(err.empty(), err);
    ASSERT(scene.root().shapes.size() == 1, "one shape");
    auto& shape = scene.root().shapes[0];
    ASSERT(std::holds_alternative<CircleShape>(shape.data), "should be circle");
    auto& c = std::get<CircleShape>(shape.data);
    ASSERT(NEAR(c.cx, 100) && NEAR(c.cy, 200) && NEAR(c.r, 50), "coords");
    PASS();
}

static void test_exec_line() {
    TEST(exec_line);
    Scene scene;
    auto err = executeCommand(scene, makeCmd("line", {0, 0, 100, 100}));
    ASSERT(err.empty(), err);
    ASSERT(scene.root().shapes.size() == 1, "one shape");
    auto& s = std::get<LineShape>(scene.root().shapes[0].data);
    ASSERT(NEAR(s.x1, 0) && NEAR(s.y1, 0) && NEAR(s.x2, 100) && NEAR(s.y2, 100), "coords");
    PASS();
}

static void test_exec_rect() {
    TEST(exec_rect);
    Scene scene;
    auto err = executeCommand(scene, makeCmd("rect", {10, 20, 30, 40}));
    ASSERT(err.empty(), err);
    auto& s = std::get<RectShape>(scene.root().shapes[0].data);
    ASSERT(NEAR(s.x, 10) && NEAR(s.y, 20) && NEAR(s.w, 30) && NEAR(s.h, 40), "coords");
    PASS();
}

static void test_exec_ellipse() {
    TEST(exec_ellipse);
    Scene scene;
    auto err = executeCommand(scene, makeCmd("ellipse", {5, 10, 15, 20}));
    ASSERT(err.empty(), err);
    auto& s = std::get<EllipseShape>(scene.root().shapes[0].data);
    ASSERT(NEAR(s.x, 5) && NEAR(s.y, 10) && NEAR(s.w, 15) && NEAR(s.h, 20), "coords");
    PASS();
}

static void test_exec_pixel() {
    TEST(exec_pixel);
    Scene scene;
    auto err = executeCommand(scene, makeCmd("pixel", {12, 34, 10, 20, 30, 128}));
    ASSERT(err.empty(), err);
    ASSERT(scene.root().shapes.size() == 1, "one shape");
    ASSERT(std::holds_alternative<PixelShape>(scene.root().shapes[0].data), "should be pixel");
    auto& p = std::get<PixelShape>(scene.root().shapes[0].data);
    ASSERT(NEAR(p.x, 12) && NEAR(p.y, 34), "coords");
    ASSERT(p.color == Color(10, 20, 30, 128), "pixel color");
    PASS();
}

// ── executeCommand tests: styles ────────────────────────────────────────

static void test_exec_stroke() {
    TEST(exec_stroke);
    Scene scene;
    auto err = executeCommand(scene, makeCmd("stroke", {255, 0, 128}));
    ASSERT(err.empty(), err);
    ASSERT(scene.strokeColor == Color(255, 0, 128), "stroke color");
    ASSERT(scene.hasStroke, "stroke enabled");
    PASS();
}

static void test_exec_stroke_with_alpha() {
    TEST(exec_stroke_with_alpha);
    Scene scene;
    auto err = executeCommand(scene, makeCmd("stroke", {100, 200, 50, 128}));
    ASSERT(err.empty(), err);
    ASSERT(scene.strokeColor == Color(100, 200, 50, 128), "stroke color with alpha");
    PASS();
}

static void test_exec_fill() {
    TEST(exec_fill);
    Scene scene;
    auto err = executeCommand(scene, makeCmd("fill", {10, 20, 30}));
    ASSERT(err.empty(), err);
    ASSERT(scene.fillColor == Color(10, 20, 30), "fill color");
    ASSERT(scene.hasFill, "fill enabled");
    PASS();
}

static void test_exec_noStroke() {
    TEST(exec_noStroke);
    Scene scene;
    auto err = executeCommand(scene, makeCmd("noStroke", {}));
    ASSERT(err.empty(), err);
    ASSERT(!scene.hasStroke, "stroke disabled");
    PASS();
}

static void test_exec_noFill() {
    TEST(exec_noFill);
    Scene scene;
    auto err = executeCommand(scene, makeCmd("noFill", {}));
    ASSERT(err.empty(), err);
    ASSERT(!scene.hasFill, "fill disabled");
    PASS();
}

static void test_exec_lineWidth() {
    TEST(exec_lineWidth);
    Scene scene;
    auto err = executeCommand(scene, makeCmd("lineWidth", {5.5}));
    ASSERT(err.empty(), err);
    ASSERT(NEAR(scene.lineWidth, 5.5), "line width");
    PASS();
}

// ── executeCommand tests: canvas ────────────────────────────────────────

static void test_exec_background() {
    TEST(exec_background);
    Scene scene;
    auto err = executeCommand(scene, makeCmd("background", {30, 30, 60}));
    ASSERT(err.empty(), err);
    ASSERT(scene.backgroundColor == Color(30, 30, 60), "bg color");
    PASS();
}

static void test_exec_clear() {
    TEST(exec_clear);
    Scene scene;
    // Add a shape first
    executeCommand(scene, makeCmd("circle", {1, 2, 3}));
    ASSERT(scene.root().shapes.size() == 1, "precondition");

    auto err = executeCommand(scene, makeCmd("clear", {}));
    ASSERT(err.empty(), err);
    ASSERT(scene.root().shapes.empty(), "shapes cleared");
    PASS();
}

// ── executeCommand tests: transforms ────────────────────────────────────

static void test_exec_translate() {
    TEST(exec_translate);
    Scene scene;
    auto err = executeCommand(scene, makeCmd("translate", {50, 75}, {"Ship"}));
    ASSERT(err.empty(), err);

    Group* ship = scene.root().findChild("Ship");
    ASSERT(ship != nullptr, "Ship group should exist");
    ASSERT(NEAR(ship->x, 50), "x");
    ASSERT(NEAR(ship->y, 75), "y");
    PASS();
}

static void test_exec_rotate() {
    TEST(exec_rotate);
    Scene scene;
    auto err = executeCommand(scene, makeCmd("rotate", {45.0}, {"Wheel"}));
    ASSERT(err.empty(), err);

    Group* wheel = scene.root().findChild("Wheel");
    ASSERT(wheel != nullptr, "Wheel group should exist");
    ASSERT(NEAR(wheel->rotation, 45.0), "rotation");
    PASS();
}

static void test_exec_scale() {
    TEST(exec_scale);
    Scene scene;
    auto err = executeCommand(scene, makeCmd("scale", {2.0, 3.0}, {"Box"}));
    ASSERT(err.empty(), err);

    Group* box = scene.root().findChild("Box");
    ASSERT(box != nullptr, "Box group should exist");
    ASSERT(NEAR(box->scaleX, 2.0), "scaleX");
    ASSERT(NEAR(box->scaleY, 3.0), "scaleY");
    PASS();
}

// ── executeCommand tests: grouped shapes ────────────────────────────────

static void test_exec_shape_in_group() {
    TEST(exec_shape_in_group);
    Scene scene;
    auto err = executeCommand(scene, makeCmd("circle", {10, 20, 5}, {"Sprite"}));
    ASSERT(err.empty(), err);

    // Root should have no shapes
    ASSERT(scene.root().shapes.empty(), "root has no shapes");

    // Sprite group should have one circle
    Group* sprite = scene.root().findChild("Sprite");
    ASSERT(sprite != nullptr, "Sprite should exist");
    ASSERT(sprite->shapes.size() == 1, "one shape in Sprite");
    ASSERT(std::holds_alternative<CircleShape>(sprite->shapes[0].data), "circle");
    PASS();
}

static void test_exec_shape_in_nested_group() {
    TEST(exec_shape_in_nested_group);
    Scene scene;
    auto err = executeCommand(scene, makeCmd("rect", {0, 0, 10, 10}, {"Ship", "Wing"}));
    ASSERT(err.empty(), err);

    Group* ship = scene.root().findChild("Ship");
    ASSERT(ship != nullptr, "Ship exists");
    Group* wing = ship->findChild("Wing");
    ASSERT(wing != nullptr, "Wing exists");
    ASSERT(wing->shapes.size() == 1, "one shape in Wing");
    PASS();
}

// ── Style snapshot in shapes ────────────────────────────────────────────

static void test_style_snapshot() {
    TEST(style_snapshot);
    Scene scene;

    // Set custom style
    executeCommand(scene, makeCmd("stroke", {255, 0, 0}));
    executeCommand(scene, makeCmd("fill", {0, 0, 255}));
    executeCommand(scene, makeCmd("lineWidth", {3.0}));

    // Draw a shape — it should capture current style
    executeCommand(scene, makeCmd("circle", {50, 50, 25}));

    auto& shape = scene.root().shapes[0];
    ASSERT(shape.strokeColor == Color(255, 0, 0), "stroke snapshot");
    ASSERT(shape.fillColor == Color(0, 0, 255),   "fill snapshot");
    ASSERT(NEAR(shape.lineWidth, 3.0),             "lineWidth snapshot");

    // Change style again
    executeCommand(scene, makeCmd("stroke", {0, 255, 0}));

    // Previous shape should retain original style
    ASSERT(shape.strokeColor == Color(255, 0, 0), "style not mutated");
    PASS();
}

// ── Multiple shapes accumulate ──────────────────────────────────────────

static void test_multiple_shapes() {
    TEST(multiple_shapes);
    Scene scene;
    executeCommand(scene, makeCmd("circle", {10, 20, 5}));
    executeCommand(scene, makeCmd("rect", {0, 0, 100, 100}));
    executeCommand(scene, makeCmd("line", {0, 0, 50, 50}));

    ASSERT(scene.root().shapes.size() == 3, "three shapes");
    ASSERT(std::holds_alternative<CircleShape>(scene.root().shapes[0].data), "shape 0 is circle");
    ASSERT(std::holds_alternative<RectShape>(scene.root().shapes[1].data),   "shape 1 is rect");
    ASSERT(std::holds_alternative<LineShape>(scene.root().shapes[2].data),   "shape 2 is line");
    PASS();
}

// ── fontSize style command ─────────────────────────────────────────────

static void test_exec_fontSize() {
    TEST(exec_fontSize);
    Scene scene;
    auto err = executeCommand(scene, makeCmd("fontSize", {24.0}));
    ASSERT(err.empty(), err);
    ASSERT(NEAR(scene.fontSize, 24.0), "fontSize updated");
    PASS();
}

static void test_exec_fontSize_invalid() {
    TEST(exec_fontSize_invalid);
    Scene scene;
    auto err = executeCommand(scene, makeCmd("fontSize", {0.0}));
    ASSERT(!err.empty(), "should reject size 0");
    auto err2 = executeCommand(scene, makeCmd("fontSize", {-5.0}));
    ASSERT(!err2.empty(), "should reject negative size");
    PASS();
}

// ── text shape command ─────────────────────────────────────────────────

static void test_exec_text_basic() {
    TEST(exec_text_basic);
    Scene scene;
    auto err = executeCommand(scene, makeTextCmd(100.0, 200.0, "Hello"));
    ASSERT(err.empty(), err);
    ASSERT(scene.root().shapes.size() == 1, "one shape");
    auto& shape = scene.root().shapes[0];
    ASSERT(std::holds_alternative<TextShape>(shape.data), "should be TextShape");
    auto& t = std::get<TextShape>(shape.data);
    ASSERT(NEAR(t.x, 100.0) && NEAR(t.y, 200.0), "coords");
    ASSERT(t.text == "Hello", "text content");
    ASSERT(NEAR(t.fontSize, 12.0), "default fontSize snapshot");
    PASS();
}

static void test_exec_text_fontSize_snapshot() {
    TEST(exec_text_fontSize_snapshot);
    Scene scene;
    executeCommand(scene, makeCmd("fontSize", {20.0}));
    executeCommand(scene, makeTextCmd(0.0, 0.0, "Big"));

    executeCommand(scene, makeCmd("fontSize", {8.0}));
    executeCommand(scene, makeTextCmd(0.0, 0.0, "Small"));

    ASSERT(scene.root().shapes.size() == 2, "two text shapes");
    ASSERT(NEAR(std::get<TextShape>(scene.root().shapes[0].data).fontSize, 20.0),
           "first text snapshots fontSize=20");
    ASSERT(NEAR(std::get<TextShape>(scene.root().shapes[1].data).fontSize, 8.0),
           "second text snapshots fontSize=8");
    PASS();
}

static void test_exec_text_inherits_stroke() {
    TEST(exec_text_inherits_stroke);
    Scene scene;
    executeCommand(scene, makeCmd("stroke", {255, 0, 0}));
    executeCommand(scene, makeTextCmd(10.0, 10.0, "Red text"));

    auto& shape = scene.root().shapes[0];
    ASSERT(shape.strokeColor == Color(255, 0, 0), "stroke color snapshot");
    PASS();
}

static void test_exec_text_in_group() {
    TEST(exec_text_in_group);
    Scene scene;
    auto err = executeCommand(scene, makeTextCmd(5.0, 10.0, "Label", {"HUD"}));
    ASSERT(err.empty(), err);
    ASSERT(scene.root().shapes.empty(), "nothing in root");
    Group* hud = scene.root().findChild("HUD");
    ASSERT(hud != nullptr, "HUD group created");
    ASSERT(hud->shapes.size() == 1, "one shape in HUD");
    ASSERT(std::holds_alternative<TextShape>(hud->shapes[0].data), "is TextShape");
    PASS();
}

static void test_exec_text_missing_string_arg() {
    TEST(exec_text_missing_string_arg);
    Scene scene;
    // Call without stringArgs — executeCommand guards against this
    ParsedCommand pc;
    pc.command = "text";
    pc.args = {10.0, 20.0};
    // no stringArgs
    auto err = executeCommand(scene, pc);
    ASSERT(!err.empty(), "should return error for missing string arg");
    PASS();
}

// ── main ────────────────────────────────────────────────────────────────

int main() {
    std::cout << "=== Group tests ===\n";
    test_group_find_or_create();
    test_group_find_child();
    test_group_clear();

    std::cout << "\n=== Scene tests ===\n";
    test_scene_resolve_group_empty();
    test_scene_resolve_group_nested();
    test_scene_resolve_group_idempotent();
    test_scene_clear();
    test_scene_make_shape();

    std::cout << "\n=== executeCommand: shapes ===\n";
    test_exec_circle();
    test_exec_line();
    test_exec_rect();
    test_exec_ellipse();
    test_exec_pixel();

    std::cout << "\n=== executeCommand: styles ===\n";
    test_exec_stroke();
    test_exec_stroke_with_alpha();
    test_exec_fill();
    test_exec_noStroke();
    test_exec_noFill();
    test_exec_lineWidth();

    std::cout << "\n=== executeCommand: canvas ===\n";
    test_exec_background();
    test_exec_clear();

    std::cout << "\n=== executeCommand: transforms ===\n";
    test_exec_translate();
    test_exec_rotate();
    test_exec_scale();

    std::cout << "\n=== executeCommand: grouped ===\n";
    test_exec_shape_in_group();
    test_exec_shape_in_nested_group();

    std::cout << "\n=== Style & accumulation ===\n";
    test_style_snapshot();
    test_multiple_shapes();

    std::cout << "\n=== fontSize command ===\n";
    test_exec_fontSize();
    test_exec_fontSize_invalid();

    std::cout << "\n=== text command ===\n";
    test_exec_text_basic();
    test_exec_text_fontSize_snapshot();
    test_exec_text_inherits_stroke();
    test_exec_text_in_group();
    test_exec_text_missing_string_arg();

    std::cout << "\n--- Results: " << tests_passed << " passed, "
              << tests_failed << " failed ---\n";

    return tests_failed > 0 ? 1 : 0;
}

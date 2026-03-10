#pragma once

/// @file comal_graphics.h
/// Abstract graphics interface for the COMAL runtime.
///
/// The runtime calls these methods when executing graphics commands.
/// Two backends are envisioned:
///
///   - NullGraphics (default) — silently ignores all calls (headless).
///   - (GUI)                  — Qt signals/slots for the IDE (in comal-ide/).
///
/// This is the counterpart to IOInterface but for drawing operations.

#include <cstdint>
#include <string>
#include <memory>

namespace comal::graphics {

// ── Color ───────────────────────────────────────────────────────────────

struct Color {
    uint8_t r{0}, g{0}, b{0}, a{255};

    Color() = default;
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
        : r(r), g(g), b(b), a(a) {}

    bool operator==(const Color&) const = default;
};

// ── GraphicsInterface ───────────────────────────────────────────────────

/// Abstract interface for graphics output.
/// All coordinates are in a logical canvas space (default 640×480).
class GraphicsInterface {
public:
    virtual ~GraphicsInterface() = default;

    // ── Canvas ──────────────────────────────────────────────────────────

    /// Set the canvas background color.
    virtual void setBackground(const Color& color) = 0;

    /// Clear the canvas to the current background color.
    virtual void clear() = 0;

    // ── Style (stateful) ────────────────────────────────────────────────

    /// Set the stroke (outline) color.
    virtual void setStroke(const Color& color) = 0;

    /// Disable stroke.
    virtual void setNoStroke() = 0;

    /// Set the fill color.
    virtual void setFill(const Color& color) = 0;

    /// Disable fill.
    virtual void setNoFill() = 0;

    /// Set the line width for strokes.
    virtual void setLineWidth(double width) = 0;

    // ── Shapes ──────────────────────────────────────────────────────────

    /// Draw a line from (x1,y1) to (x2,y2).
    virtual void drawLine(double x1, double y1, double x2, double y2) = 0;

    /// Draw a rectangle at (x,y) with dimensions w×h.
    virtual void drawRect(double x, double y, double w, double h) = 0;

    /// Draw a circle centered at (cx,cy) with radius r.
    virtual void drawCircle(double cx, double cy, double r) = 0;

    /// Draw an ellipse bounded by the rectangle at (x,y) w×h.
    virtual void drawEllipse(double x, double y, double w, double h) = 0;

    // ── Transforms (group-level) ────────────────────────────────────────

    /// Translate the current group by (dx,dy).
    virtual void translate(const std::string& group, double dx, double dy) = 0;

    /// Rotate the current group by deg degrees.
    virtual void rotate(const std::string& group, double deg) = 0;

    /// Scale the current group uniformly or non-uniformly.
    virtual void scale(const std::string& group, double sx, double sy) = 0;

    // ── Grouping ────────────────────────────────────────────────────────

    /// Push into a named group (created on first use).
    /// All subsequent shape/style commands target this group.
    virtual void beginGroup(const std::string& name) = 0;

    /// Pop back to the parent group (or root).
    virtual void endGroup() = 0;
};

// ── NullGraphics ────────────────────────────────────────────────────────

/// Default no-op backend — silently ignores all graphics calls.
/// Used when running headless (CLI) or when no graphics panel is attached.
class NullGraphics : public GraphicsInterface {
public:
    void setBackground(const Color&) override {}
    void clear() override {}
    void setStroke(const Color&) override {}
    void setNoStroke() override {}
    void setFill(const Color&) override {}
    void setNoFill() override {}
    void setLineWidth(double) override {}
    void drawLine(double, double, double, double) override {}
    void drawRect(double, double, double, double) override {}
    void drawCircle(double, double, double) override {}
    void drawEllipse(double, double, double, double) override {}
    void translate(const std::string&, double, double) override {}
    void rotate(const std::string&, double) override {}
    void scale(const std::string&, double, double) override {}
    void beginGroup(const std::string&) override {}
    void endGroup() override {}
};

} // namespace comal::graphics

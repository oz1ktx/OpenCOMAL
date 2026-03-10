#pragma once

/// @file comal_scene_model.h
/// Scene graph model for the graphics engine.
///
/// The scene is a tree of Groups rooted at an implicit "root" group.
/// Each group has:
///   - A list of child shapes (drawn in order)
///   - Transform properties (x, y, rotation, scaleX, scaleY)
///   - Child groups (nested sprites)
///   - Style state at creation time
///
/// The model is renderer-agnostic: the IDE's GraphicsPanel reads it
/// to produce QGraphicsItems or QML items.

#include "comal_graphics.h"

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <variant>
#include <optional>

namespace comal::graphics {

// ── Shape records ───────────────────────────────────────────────────────

struct LineShape {
    double x1, y1, x2, y2;
};

struct RectShape {
    double x, y, w, h;
};

struct CircleShape {
    double cx, cy, r;
};

struct EllipseShape {
    double x, y, w, h;
};

using ShapeData = std::variant<LineShape, RectShape, CircleShape, EllipseShape>;

/// A drawn shape with the style that was active when it was created.
struct Shape {
    ShapeData data;
    Color strokeColor{0, 0, 0, 255};
    bool  hasStroke{true};
    Color fillColor{255, 255, 255, 255};
    bool  hasFill{true};
    double lineWidth{1.0};
};

// ── Group (node in the scene tree) ──────────────────────────────────────

struct Group {
    std::string name;

    // Shapes owned by this group (drawn in order)
    std::vector<Shape> shapes;

    // Child groups (ordered for draw order; lookup by name via index)
    std::vector<std::unique_ptr<Group>> children;
    std::unordered_map<std::string, Group*> childIndex;

    // Transform properties
    double x{0}, y{0};
    double rotation{0};
    double scaleX{1}, scaleY{1};

    /// Find or create a child group by name.
    Group* findOrCreateChild(const std::string& childName) {
        auto it = childIndex.find(childName);
        if (it != childIndex.end())
            return it->second;
        auto child = std::make_unique<Group>();
        child->name = childName;
        Group* ptr = child.get();
        childIndex[childName] = ptr;
        children.push_back(std::move(child));
        return ptr;
    }

    /// Find a child group by name (returns nullptr if not found).
    Group* findChild(const std::string& childName) const {
        auto it = childIndex.find(childName);
        return (it != childIndex.end()) ? it->second : nullptr;
    }

    /// Clear all shapes and children.
    void clear() {
        shapes.clear();
        children.clear();
        childIndex.clear();
    }
};

// ── Scene ───────────────────────────────────────────────────────────────

/// The complete scene: a root group plus global style state.
class Scene {
public:
    Scene();

    /// The root group (implicit canvas layer).
    Group& root() { return root_; }
    const Group& root() const { return root_; }

    /// Resolve a group path (e.g. {"Spaceship", "Engine"}) from root.
    /// Creates intermediate groups as needed.
    Group* resolveGroup(const std::vector<std::string>& path);

    /// Clear the entire scene (all groups and shapes).
    void clear();

    // ── Current style state (set by style commands) ─────────────────────

    Color strokeColor{0, 0, 0, 255};
    bool  hasStroke{true};
    Color fillColor{255, 255, 255, 255};
    bool  hasFill{true};
    double lineWidth{1.0};
    Color backgroundColor{240, 240, 255, 255};

    /// Create a Shape record using the current style state.
    Shape makeShape(ShapeData data) const;

private:
    Group root_;
};

// ── Command executor ────────────────────────────────────────────────────

class CommandRegistry;
struct ParsedCommand;

/// Execute a parsed command, updating the scene model.
/// Returns an error message on failure, or empty string on success.
std::string executeCommand(Scene& scene, const ParsedCommand& cmd);

} // namespace comal::graphics

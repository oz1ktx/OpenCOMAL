/// @file scene_model.cpp
/// Scene model and command executor implementation.

#include "comal_scene_model.h"
#include "comal_graphics_commands.h"

#include <cmath>
#include <algorithm>

namespace comal::graphics {

// ── Scene ───────────────────────────────────────────────────────────────

Scene::Scene() {
    root_.name = "root";
}

Group* Scene::resolveGroup(const std::vector<std::string>& path) {
    std::lock_guard<std::recursive_mutex> lock(scene_mutex_);
    Group* current = &root_;
    for (const auto& name : path)
        current = current->findOrCreateChild(name);
    return current;
}

void Scene::clear() {
    std::lock_guard<std::recursive_mutex> lock(scene_mutex_);
    root_.clear();
    // Reset all style state to defaults so each run starts consistently.
    strokeColor = Color{0, 0, 0, 255};
    hasStroke = true;
    fillColor = Color{255, 255, 255, 255};
    hasFill = true;
    lineWidth = 1.0;
    fontSize = 12.0;
    backgroundColor = Color{240, 240, 255, 255};
}

Shape Scene::makeShape(ShapeData data) const {
    std::lock_guard<std::recursive_mutex> lock(scene_mutex_);
    Shape s;
    s.data = std::move(data);
    s.strokeColor = strokeColor;
    s.hasStroke = hasStroke;
    s.fillColor = fillColor;
    s.hasFill = hasFill;
    s.lineWidth = lineWidth;
    return s;
}

// ── Command executor ────────────────────────────────────────────────────

static uint8_t clampByte(double v) {
    return static_cast<uint8_t>(std::clamp(v, 0.0, 255.0));
}

std::string executeCommand(Scene& scene, const ParsedCommand& cmd) {
    // Acquire lock for entire command execution to ensure atomic style + shape operations
    auto lock = scene.acquireLock();
    Group* target = scene.resolveGroup(cmd.groupPath);
    const auto& a = cmd.args;
    const auto& name = cmd.command;

    // ── Canvas ──────────────────────────────────────────────────────────
    if (name == "background") {
        uint8_t alpha = (a.size() >= 4) ? clampByte(a[3]) : 255;
        scene.backgroundColor = Color(clampByte(a[0]), clampByte(a[1]),
                                       clampByte(a[2]), alpha);
        return {};
    }
    if (name == "clear") {
        scene.clear();
        return {};
    }

    // ── Styles ──────────────────────────────────────────────────────────
    if (name == "stroke") {
        uint8_t alpha = (a.size() >= 4) ? clampByte(a[3]) : 255;
        scene.strokeColor = Color(clampByte(a[0]), clampByte(a[1]),
                                   clampByte(a[2]), alpha);
        scene.hasStroke = true;
        return {};
    }
    if (name == "fill") {
        uint8_t alpha = (a.size() >= 4) ? clampByte(a[3]) : 255;
        scene.fillColor = Color(clampByte(a[0]), clampByte(a[1]),
                                 clampByte(a[2]), alpha);
        scene.hasFill = true;
        return {};
    }
    if (name == "noFill") {
        scene.hasFill = false;
        return {};
    }
    if (name == "noStroke") {
        scene.hasStroke = false;
        return {};
    }
    if (name == "lineWidth") {
        scene.lineWidth = a[0];
        return {};
    }
    if (name == "fontSize") {
        if (a[0] <= 0)
            return "fontSize: size must be positive";
        scene.fontSize = a[0];
        return {};
    }

    // ── Shapes ──────────────────────────────────────────────────────────
    if (name == "line") {
        target->shapes.push_back(
            scene.makeShape(LineShape{a[0], a[1], a[2], a[3]}));
        return {};
    }
    if (name == "rect") {
        target->shapes.push_back(
            scene.makeShape(RectShape{a[0], a[1], a[2], a[3]}));
        return {};
    }
    if (name == "circle") {
        target->shapes.push_back(
            scene.makeShape(CircleShape{a[0], a[1], a[2]}));
        return {};
    }
    if (name == "ellipse") {
        target->shapes.push_back(
            scene.makeShape(EllipseShape{a[0], a[1], a[2], a[3]}));
        return {};
    }
    if (name == "pixel") {
        uint8_t alpha = (a.size() >= 6) ? clampByte(a[5]) : 255;
        target->shapes.push_back(scene.makeShape(PixelShape{
            a[0],
            a[1],
            Color(clampByte(a[2]), clampByte(a[3]), clampByte(a[4]), alpha),
        }));
        return {};
    }
    if (name == "text") {
        const auto& sa = cmd.stringArgs;
        if (sa.empty())
            return "text: missing text argument";
        target->shapes.push_back(
            scene.makeShape(TextShape{a[0], a[1], sa[0], scene.fontSize}));
        return {};
    }

    // ── Transforms ──────────────────────────────────────────────────────
    if (name == "translate") {
        target->x += a[0];
        target->y += a[1];
        return {};
    }
    if (name == "rotate") {
        target->rotation += a[0];
        return {};
    }
    if (name == "scale") {
        if (a.size() >= 2) {
            target->scaleX *= a[0];
            target->scaleY *= a[1];
        } else {
            target->scaleX *= a[0];
            target->scaleY *= a[0];
        }
        return {};
    }

    return "Unknown command: '" + name + "'";
}

} // namespace comal::graphics

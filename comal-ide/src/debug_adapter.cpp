#include "debug_adapter.h"
#include "comal_interpreter.h"
#include <QVariantMap>

using namespace comal::runtime;

/// Debug adapter for COMAL runtime.
class ComalDebugAdapter final : public IDebugAdapter {
public:
    explicit ComalDebugAdapter(Interpreter* interp) : interp_(interp) {}

    QVariantList getVariables() const override {
        if (!interp_) return {};
        auto vars = interp_->getVariables();
        QVariantList varList;
        for (const auto& var : vars) {
            QVariantMap varMap;
            varMap["name"] = QString::fromStdString(var.name);
            varMap["type"] = QString::fromStdString(var.type);
            varMap["value"] = QString::fromStdString(var.value);
            varMap["scope"] = QString::fromStdString(var.scope);
            varList.append(varMap);
        }
        return varList;
    }

    QVariantList getCallStack() const override {
        if (!interp_) return {};
        auto stack = interp_->getCallStack();
        QVariantList stackList;
        for (const auto &frame : stack) {
            QVariantMap frameMap;
            frameMap["name"] = QString::fromStdString(frame.name);
            frameMap["line"] = frame.line;
            stackList.append(frameMap);
        }
        return stackList;
    }

    QVariantList getRegisters() const override {
        // Not applicable for COMAL
        return {};
    }

    QVariantList getFlags() const override {
        // Not applicable for COMAL
        return {};
    }

    QByteArray getMemory(std::uint16_t /*address*/, std::size_t /*count*/) const override {
        // Not applicable for COMAL
        return {};
    }

    QVariantList getDisassembly(std::uint16_t /*address*/, std::size_t /*count*/) const override {
        // Not applicable for COMAL
        return {};
    }

    std::uint16_t getCurrentLocation() const override {
        if (!interp_ || !interp_->curline) {
            return 0;
        }
        return static_cast<std::uint16_t>(interp_->curline->lineNumber());
    }

private:
    Interpreter* interp_;
};

/// Debug adapter for Z80 machine (stub for now).
class Z80DebugAdapter final : public IDebugAdapter {
public:
    explicit Z80DebugAdapter(void* /*z80Machine*/) {
        // TODO: implement after Z80Machine is exposed
    }

    QVariantList getVariables() const override {
        // Not applicable for Z80
        return {};
    }

    QVariantList getCallStack() const override {
        // Not applicable for Z80
        return {};
    }

    QVariantList getRegisters() const override {
        // TODO: extract from Z80 CPU state
        return {};
    }

    QVariantList getFlags() const override {
        // TODO: extract from Z80 CPU flags
        return {};
    }

    QByteArray getMemory(std::uint16_t /*address*/, std::size_t /*count*/) const override {
        // TODO: read from Z80 memory buffer
        return {};
    }

    QVariantList getDisassembly(std::uint16_t /*address*/, std::size_t /*count*/) const override {
        // TODO: disassemble Z80 instructions
        return {};
    }

    std::uint16_t getCurrentLocation() const override {
        // TODO: return current PC
        return 0;
    }

private:
    void* z80Machine_;
};

std::unique_ptr<IDebugAdapter> DebugAdapterFactory::createComalAdapter(Interpreter* interp)
{
    return std::make_unique<ComalDebugAdapter>(interp);
}

std::unique_ptr<IDebugAdapter> DebugAdapterFactory::createZ80Adapter(void* z80Machine)
{
    return std::make_unique<Z80DebugAdapter>(z80Machine);
}

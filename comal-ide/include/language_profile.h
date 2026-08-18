#pragma once

#include <QString>
#include <vector>

enum class LanguageId {
    Comal,
    Z80Assembly,
};

inline LanguageId detectLanguageFromFilePath(const QString &filePath)
{
    const QString lower = filePath.toLower();
    if (lower.endsWith(".asm") || lower.endsWith(".z80") || lower.endsWith(".s") || lower.endsWith(".com")) {
        return LanguageId::Z80Assembly;
    }
    return LanguageId::Comal;
}

inline bool isComalLanguage(LanguageId language)
{
    return language == LanguageId::Comal;
}

/// Configuration for a programming language in the OpenCOMAL IDE.
struct LanguageProfile {
    LanguageId id;
    QString name;
    std::vector<QString> fileExtensions;  // e.g., [".lst", ".comal"]
    QString lspServerCommand;              // command to launch LSP server
    QString formatterType;                 // "comal" or "z80"
    bool debuggable;                       // supports breakpoints/stepping
};

/// Get the language profile for the given language ID.
inline LanguageProfile getLanguageProfile(LanguageId language)
{
    if (language == LanguageId::Z80Assembly) {
        return {
            LanguageId::Z80Assembly,
            "Z80 Assembly",
            {".asm", ".z80", ".s", ".com"},
            "comal-lsp --language z80",
            "z80",
            true
        };
    }
    return {
        LanguageId::Comal,
        "COMAL",
        {".lst", ".comal"},
        "comal-lsp --language comal",
        "comal",
        true
    };
}

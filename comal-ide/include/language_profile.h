#pragma once

#include <QString>

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

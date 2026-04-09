#include "help_panel.h"
#include "comal_keyword_docs.h"

#include <QVBoxLayout>
#include <QTextBrowser>
#include <QMap>
#include <QStringList>

static QString buildDefaultHelpHtml()
{
    static const QStringList categoryOrder = {
        "Control Flow",
        "Procedures",
        "Variables and Data",
        "I/O and Files",
        "Strings",
        "Math and Logic",
        "Runtime and Errors",
        "Graphics and Sound",
        "System"
    };

    QMap<QString, QStringList> grouped;
    for (const auto &entry : comal::docs::keywordDocEntries()) {
        grouped[QString::fromUtf8(entry.category)]
            .append(QString::fromUtf8(entry.keyword));
    }

    QString html;
    html += "<h2>OpenCOMAL Quick Reference</h2>";
    html += "<table border=\"1\" cellpadding=\"4\" cellspacing=\"0\">";
    html += "<tr><th>Category</th><th>Keywords</th></tr>";

    for (const QString &category : categoryOrder) {
        const auto it = grouped.find(category);
        if (it == grouped.end()) {
            continue;
        }
        html += "<tr><td>" + category.toHtmlEscaped() + "</td><td>";
        html += it.value().join(", ").toHtmlEscaped();
        html += "</td></tr>";
    }

    for (auto it = grouped.cbegin(); it != grouped.cend(); ++it) {
        if (categoryOrder.contains(it.key())) {
            continue;
        }
        html += "<tr><td>" + it.key().toHtmlEscaped() + "</td><td>";
        html += it.value().join(", ").toHtmlEscaped();
        html += "</td></tr>";
    }

    html += "</table>";
    html += "<p><i>Click a keyword in the editor for detailed help (via LSP hover).</i></p>";
    return html;
}

static const QString &defaultHelpHtml()
{
    static const QString html = buildDefaultHelpHtml();
    return html;
}

HelpPanel::HelpPanel(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    browser_ = new QTextBrowser(this);
    browser_->setOpenExternalLinks(false);
    browser_->setHtml(defaultHelpHtml());
    layout->addWidget(browser_);
}

void HelpPanel::showKeywordHelp(const QString &keyword)
{
    const QString upper = keyword.trimmed().toUpper();
    if (upper.isEmpty()) {
        browser_->setHtml(defaultHelpHtml());
        return;
    }

    const auto &docs = comal::docs::keywordDocsMap();
    const auto it = docs.find(upper.toStdString());
    const QString doc = it != docs.end()
        ? QString::fromStdString(it->second)
        : QStringLiteral("No dedicated documentation text yet for this keyword.");

    browser_->setHtml(
        "<h3>" + upper + "</h3>"
        "<p>" + doc + "</p>"
        "<p><i>Tip: keep cursor on a keyword in the editor to update this panel.</i></p>"
    );
}

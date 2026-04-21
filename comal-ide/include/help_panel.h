#pragma once

#include <QWidget>
#include <QString>

class QTextBrowser;

// Quick-reference panel for COMAL keywords.
class HelpPanel : public QWidget {
    Q_OBJECT

public:
    explicit HelpPanel(QWidget *parent = nullptr);

    void showKeywordHelp(const QString &keyword);
    void showLspHoverHelp(const QString &hoverText);

private:
    QTextBrowser *browser_;
};

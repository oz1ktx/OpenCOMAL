#pragma once

#include <QWidget>

class QTextBrowser;

// Quick-reference panel for COMAL keywords.
class HelpPanel : public QWidget {
    Q_OBJECT

public:
    explicit HelpPanel(QWidget *parent = nullptr);

    void showKeywordHelp(const QString &keyword);

private:
    QTextBrowser *browser_;
};

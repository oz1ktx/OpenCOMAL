#pragma once

#include <QWidget>
#include <QString>

class QTextEdit;
class QTabWidget;
class QLabel;

/// Assembly output panel displaying listing, diagnostics, and build statistics.
/// Shows:
/// - Listing tab: sjasmplus assembly listing (.lst content)
/// - Diagnostics tab: compilation errors/warnings
/// - Statistics tab: build timing, file sizes, memory usage
class AssemblyOutputPanel : public QWidget {
    Q_OBJECT

public:
    explicit AssemblyOutputPanel(QWidget *parent = nullptr);

    void clearListing();
    void displayListing(const QString &content);
    void displayDiagnostics(const QString &diagnostics);
    void displayStatistics(const QString &filename, double elapsedSeconds, 
                          const QString &outputPath, int outputSize);
    void displayError(const QString &errorMessage);
    
    void applyFont(const QFont &font);

private slots:
    void onClearListing();
    void onSaveListing();
    void showContextMenu(const QPoint &pos);

private:
    QTabWidget *tabs_;
    QTextEdit  *listingEdit_;
    QTextEdit  *diagnosticsEdit_;
    QTextEdit  *statisticsEdit_;
};

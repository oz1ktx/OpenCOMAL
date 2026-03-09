#pragma once

#include <QMainWindow>

class QTabWidget;
class QDockWidget;
class CodeEditorPanel;
class DirectCommandPanel;
class GraphicsPanel;
class DebugPanel;
class FileBrowserPanel;
class HelpPanel;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void createMenus();
    void createToolBar();
    void createStatusBar();
    void createPanels();
    void restoreDefaultLayout();

    // Central widget
    CodeEditorPanel *codeEditor_;

    // Dockable panels
    QDockWidget *directCommandDock_;
    QDockWidget *graphicsDock_;
    QDockWidget *debugDock_;
    QDockWidget *fileBrowserDock_;
    QDockWidget *helpDock_;

    DirectCommandPanel *directCommand_;
    GraphicsPanel      *graphics_;
    DebugPanel         *debug_;
    FileBrowserPanel   *fileBrowser_;
    HelpPanel          *help_;

private slots:
    void onRun();
    void onStop();
    void onStepInto();
    void onStepOver();
    void onContinue();
    void onFormatSource();
    void onResetLayout();
};

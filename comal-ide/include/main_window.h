#pragma once

#include <QMainWindow>
#include <memory>

class QTabWidget;
class QDockWidget;
class QLabel;
class CodeEditorPanel;
class DirectCommandPanel;
class GraphicsPanel;
class DebugPanel;
class FileBrowserPanel;
class HelpPanel;
class RunWorker;

namespace comal::graphics { class Scene; }

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createMenus();
    void createToolBar();
    void createStatusBar();
    void createPanels();
    void restoreDefaultLayout();
    void connectRunWorker();

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

    // Runtime worker
    RunWorker *worker_{nullptr};

    // Persistent graphics scene (shared across direct commands)
    std::unique_ptr<comal::graphics::Scene> persistentScene_;

    // Status bar widgets
    QLabel *posLabel_;
    QLabel *stateLabel_;

private slots:
    void onNew();
    void onOpen();
    void onSave();
    void onSaveAs();
    void onCloseTab();
    void onRun();
    void onStop();
    void onStepInto();
    void onStepOver();
    void onContinue();
    void onFormatSource();
    void onResetLayout();
    void onRunFinished();
    void onRunError(const QString &message, int lineNumber);
    void onDirectCommand(const QString &command);
    void updateCursorPos(int line, int col);
};

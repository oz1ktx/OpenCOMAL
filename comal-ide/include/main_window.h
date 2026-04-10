
#pragma once
#include <QMainWindow>
#include <memory>
#include "comal_lsp_client.h"

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
class QtIO;
class SettingsDialog;

namespace comal::graphics { class Scene; }
namespace comal::runtime { class Interpreter; }

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    ComalLspClient *lspClient_ = nullptr;
    void createMenus();
    void createToolBar();
    void createStatusBar();
    void createPanels();
    void restoreDefaultLayout();
    void connectRunWorker();

    void startSingleStepRun(const QString &title);
    
    // Settings persistence
    void saveWindowState();
    void restoreWindowState();
    void applyFontSettingsFromDialog(SettingsDialog *dialog);

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
    bool lastActionWasDirectCommand_{false};

    // Persistent interpreter and I/O backend shared across all worker executions
    // This allows PROCs defined in one run to be callable from direct commands
    QtIO *persistentIO_{nullptr};
    std::shared_ptr<comal::runtime::Interpreter> persistentInterp_;

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
    void onBreak(); // Break handler
    void onStepInto();
    void onStepOver();
    void onContinue();
    void onFormatSource();
    void onResetLayout();
    void onRunFinished();
    void onRunError(const QString &message, int lineNumber);
    void onExecutionPaused(int lineNumber);
    void onDirectCommand(const QString &command);
    void updateCursorPos(int line, int col);
    void onSettings();
};

#include "main_window.h"
#include "code_editor_panel.h"
#include "direct_command_panel.h"
#include "graphics_panel.h"
#include "debug_panel.h"
#include "file_browser_panel.h"
#include "help_panel.h"
#include "run_worker.h"
#include "qt_io.h"
#include "settings_dialog.h"
#include "comal_scene_model.h"
#include "comal_interpreter.h"

#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QDockWidget>
#include <QLabel>
#include <QAction>
#include <QKeySequence>
#include <QFileDialog>
#include <QSettings>
#include <QCloseEvent>
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <Qsci/qsciscintilla.h>

namespace {

QString resolveComalLspPath()
{
    const QString appDir = QCoreApplication::applicationDirPath();
    const QStringList candidates {
        "/usr/bin/comal-lsp",
        QDir(appDir).filePath("comal-lsp"),
        QDir(appDir).filePath("../comal-lsp/comal-lsp"),
    };

    for (const QString &candidate : candidates) {
        const QFileInfo info(candidate);
        if (info.exists() && info.isFile() && info.isExecutable()) {
            return info.absoluteFilePath();
        }
    }

    // Keep startup resilient even when discovery fails.
    return candidates.first();
}

QString extractHoverText(const QJsonObject &hover)
{
    const QJsonValue contentsValue = hover.value("contents");

    if (contentsValue.isString()) {
        return contentsValue.toString();
    }

    if (contentsValue.isObject()) {
        const QJsonObject contentsObj = contentsValue.toObject();
        if (contentsObj.value("value").isString()) {
            return contentsObj.value("value").toString();
        }
        return {};
    }

    if (contentsValue.isArray()) {
        QStringList parts;
        const QJsonArray partsArray = contentsValue.toArray();
        for (const QJsonValue &part : partsArray) {
            if (part.isString()) {
                const QString text = part.toString().trimmed();
                if (!text.isEmpty()) {
                    parts.append(text);
                }
                continue;
            }
            if (part.isObject()) {
                const QJsonObject obj = part.toObject();
                if (obj.value("value").isString()) {
                    const QString text = obj.value("value").toString().trimmed();
                    if (!text.isEmpty()) {
                        parts.append(text);
                    }
                }
            }
        }
        return parts.join("\n\n");
    }

    return {};
}

} // namespace

MainWindow::~MainWindow() = default;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , persistentScene_(std::make_unique<comal::graphics::Scene>())
    , persistentIO_(new QtIO)
    , persistentInterp_(std::make_shared<comal::runtime::Interpreter>())
{
    setWindowTitle("OpenCOMAL IDE");
    resize(1280, 800);

    // Set up the persistent I/O backend on the persistent interpreter
    persistentInterp_->setIO(std::unique_ptr<comal::runtime::IOInterface>(persistentIO_));

    createPanels();
    createMenus();

    createToolBar();
    createStatusBar();
    restoreDefaultLayout();

    // Wire the persistent I/O signals to the output panel
    connect(persistentIO_, &QtIO::textOutput,
            directCommand_, &DirectCommandPanel::appendOutput,
            Qt::QueuedConnection);

    connect(persistentIO_, &QtIO::screenCleared, directCommand_, [this]() {
        directCommand_->clearOutputPanel();
    }, Qt::QueuedConnection);

    connect(persistentIO_, &QtIO::cursorMoved, directCommand_, [this](int r, int c) {
        directCommand_->appendOutput(
            QString("[CURSOR %1,%2]").arg(r).arg(c));
    }, Qt::QueuedConnection);

    connect(persistentIO_, &QtIO::inputRequested, directCommand_, [this](const QString &prompt) {
        directCommand_->showInputMarker(prompt);
        directCommand_->setInputEnabled(true);
    }, Qt::QueuedConnection);

    // LSP client setup
    lspClient_ = new ComalLspClient(this);
    codeEditor_->setLspClient(lspClient_);
    connect(lspClient_, &ComalLspClient::hoverReceived, this,
            [this](const QString &, const QJsonObject &hover) {
                const QString hoverText = extractHoverText(hover);
                if (!hoverText.trimmed().isEmpty()) {
                    help_->showLspHoverHelp(hoverText);
                }
            });
    lspClient_->startServer(resolveComalLspPath());

    // Restore window state and settings from previous session
    restoreWindowState();
}

// ── Menus ───────────────────────────────────────────────────────────

void MainWindow::createMenus()
{
    // File
    auto *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(tr("&New"),        this, &MainWindow::onNew,    QKeySequence::New);
    fileMenu->addAction(tr("&Open..."),    this, &MainWindow::onOpen,   QKeySequence::Open);
    fileMenu->addAction(tr("&Save"),       this, &MainWindow::onSave,   QKeySequence::Save);
    fileMenu->addAction(tr("Save &As..."), this, &MainWindow::onSaveAs);
    fileMenu->addSeparator();
    fileMenu->addAction(tr("Recent Files"))->setEnabled(false);
    fileMenu->addSeparator();
    fileMenu->addAction(tr("&Close"),      this, &MainWindow::onCloseTab, QKeySequence::Close);
    fileMenu->addAction(tr("E&xit"),       this, &QWidget::close, QKeySequence::Quit);

    // Edit
    auto *editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(tr("&Undo"), this, [this]{
        if (auto *e = codeEditor_->currentEditor()) e->undo();
    }, QKeySequence::Undo);
    editMenu->addAction(tr("&Redo"), this, [this]{
        if (auto *e = codeEditor_->currentEditor()) e->redo();
    }, QKeySequence::Redo);
    editMenu->addSeparator();
    editMenu->addAction(tr("Cu&t"), this, [this]{
        if (auto *e = codeEditor_->currentEditor()) e->cut();
    }, QKeySequence::Cut);
    editMenu->addAction(tr("&Copy"), this, [this]{
        if (auto *e = codeEditor_->currentEditor()) e->copy();
    }, QKeySequence::Copy);
    editMenu->addAction(tr("&Paste"), this, [this]{
        if (auto *e = codeEditor_->currentEditor()) e->paste();
    }, QKeySequence::Paste);
    editMenu->addSeparator();
    editMenu->addAction(tr("&Find/Replace..."), this, []{}, QKeySequence::Find);
    editMenu->addSeparator();
    editMenu->addAction(tr("Format &Source"), this, &MainWindow::onFormatSource,
                         QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_F));

    // Program
    auto *progMenu = menuBar()->addMenu(tr("&Program"));
    progMenu->addAction(tr("&Run"),               this, &MainWindow::onRun,
                         QKeySequence(Qt::Key_F5));
    progMenu->addAction(tr("&Stop"),              this, &MainWindow::onStop,
                         QKeySequence(Qt::SHIFT | Qt::Key_F5));
    progMenu->addAction(tr("&Break"),             this, &MainWindow::onBreak,
                         QKeySequence(Qt::Key_F6));
    progMenu->addAction(tr("Step &Into"),         this, &MainWindow::onStepInto,
                         QKeySequence(Qt::Key_F11));
    progMenu->addAction(tr("Step &Over"),         this, &MainWindow::onStepOver,
                         QKeySequence(Qt::Key_F10));
    progMenu->addAction(tr("&Continue"),          this, &MainWindow::onContinue,
                         QKeySequence(Qt::Key_F5));
    progMenu->addSeparator();
    progMenu->addAction(tr("Toggle &Breakpoint"), this, [this]{
        if (codeEditor_)
            codeEditor_->toggleBreakpointAtCurrentLine();
    }, QKeySequence(Qt::Key_F9));

    // View — toggle each dock panel
    auto *viewMenu = menuBar()->addMenu(tr("&View"));
    viewMenu->addAction(directCommandDock_->toggleViewAction());
    viewMenu->addAction(graphicsDock_->toggleViewAction());
    viewMenu->addAction(debugDock_->toggleViewAction());
    viewMenu->addAction(fileBrowserDock_->toggleViewAction());
    viewMenu->addAction(helpDock_->toggleViewAction());
    viewMenu->addSeparator();
    viewMenu->addAction(tr("&Reset Layout"), this, &MainWindow::onResetLayout);

    // Settings
    auto *settingsMenu = menuBar()->addMenu(tr("&Settings"));
    settingsMenu->addAction(tr("&Fonts && Colors..."), this, &MainWindow::onSettings);
    settingsMenu->addSeparator();
    settingsMenu->addAction(tr("&Editor Preferences..."))->setEnabled(false);
    settingsMenu->addAction(tr("&Key Bindings..."))->setEnabled(false);

    // Help
    auto *helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(tr("COMAL &Quick Reference"), this, []{});
    helpMenu->addSeparator();
    helpMenu->addAction(tr("&About OpenCOMAL IDE"), this, []{});
}

// ── Toolbar ─────────────────────────────────────────────────────────

void MainWindow::createToolBar()
{
    auto *tb = addToolBar(tr("Program"));
    tb->setObjectName("ProgramToolBar");

    tb->addAction(tr("Run"),       this, &MainWindow::onRun);
    tb->addAction(tr("Stop"),      this, &MainWindow::onStop);
    tb->addAction(tr("Break"),     this, &MainWindow::onBreak);
    tb->addSeparator();
    tb->addAction(tr("Step Into"), this, &MainWindow::onStepInto);
    tb->addAction(tr("Step Over"), this, &MainWindow::onStepOver);
    tb->addAction(tr("Continue"),  this, &MainWindow::onContinue);
}

// ── Status bar ──────────────────────────────────────────────────────

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
    posLabel_ = new QLabel(tr("Ln 1, Col 1"));
    posLabel_->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    statusBar()->addPermanentWidget(posLabel_);

    stateLabel_ = new QLabel(tr("Ready"));
    stateLabel_->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    statusBar()->addPermanentWidget(stateLabel_);
}

// ── Panels ──────────────────────────────────────────────────────────

void MainWindow::createPanels()
{
    // Central: code editor (tabbed)
    codeEditor_ = new CodeEditorPanel(this);
    setCentralWidget(codeEditor_);

    // Direct Command / Output — bottom
    directCommand_ = new DirectCommandPanel;
    directCommandDock_ = new QDockWidget(tr("Direct Command"), this);
    directCommandDock_->setObjectName("DirectCommandDock");
    directCommandDock_->setWidget(directCommand_);

    // Graphics canvas — right
    graphics_ = new GraphicsPanel;
    graphicsDock_ = new QDockWidget(tr("Graphics"), this);
    graphicsDock_->setObjectName("GraphicsDock");
    graphicsDock_->setWidget(graphics_);

    // Debug — bottom-right
    debug_ = new DebugPanel;
    debugDock_ = new QDockWidget(tr("Debug"), this);
    debugDock_->setObjectName("DebugDock");
    debugDock_->setWidget(debug_);

    // File browser — left
    fileBrowser_ = new FileBrowserPanel;
    fileBrowserDock_ = new QDockWidget(tr("Files"), this);
    fileBrowserDock_->setObjectName("FilesDock");
    fileBrowserDock_->setWidget(fileBrowser_);

    connect(fileBrowser_, &FileBrowserPanel::fileDoubleClicked,
            codeEditor_,  &CodeEditorPanel::openFile);

    // Cursor position tracking
    connect(codeEditor_, &CodeEditorPanel::cursorPositionChanged,
            this,        &MainWindow::updateCursorPos);

    // Breakpoints → debug panel
    connect(codeEditor_, &CodeEditorPanel::breakpointsChanged,
            debug_, &DebugPanel::updateBreakpoints,
            Qt::QueuedConnection);

    // Keep running interpreter in sync with breakpoint changes while running.
    connect(codeEditor_, &CodeEditorPanel::breakpointsChanged, this, [this](const QString &, const QVector<int> &lines) {
        if (worker_ && worker_->isRunning()) {
            worker_->setBreakpoints(std::vector<int>(lines.begin(), lines.end()));
        }
    });

    // Update debug panel when user switches files
    connect(codeEditor_, &CodeEditorPanel::currentFileChanged, this, [this](const QString &filePath) {
        if (!debug_) return;
        debug_->updateBreakpoints(filePath, codeEditor_->breakpointsForCurrentFile());
    });

    // Help — right
    help_ = new HelpPanel;
    helpDock_ = new QDockWidget(tr("Help"), this);
    helpDock_->setObjectName("HelpDock");
    helpDock_->setWidget(help_);

        // Contextual keyword help from editor cursor position (independent of LSP hover).
        connect(codeEditor_, &CodeEditorPanel::keywordUnderCursorChanged,
            help_, &HelpPanel::showKeywordHelp);

    // Direct command execution (when no program is running)
    connect(directCommand_, &DirectCommandPanel::lineEntered,
            this, &MainWindow::onDirectCommand);

    // GraphicsPanel clear request → clear the persistent scene too
    connect(graphics_, &GraphicsPanel::clearRequested, this, [this]() {
        persistentScene_->clear();
        graphics_->clearCanvas();
    });
}

// ── Default layout ──────────────────────────────────────────────────
//
//  ┌──────────┬────────────────────────┬──────────────┐
//  │  Files   │     Code Editor        │  Graphics    │
//  │  (left)  │     (central, tabs)    │  (right)     │
//  │          │                        │              │
//  │          │                        ├──────────────┤
//  │          │                        │  Help        │
//  │          │                        │  (right-bot) │
//  │          ├────────────────────────┼──────────────┤
//  │          │  Direct Command        │  Debug       │
//  │          │  (bottom)              │  (bottom-rt) │
//  └──────────┴────────────────────────┴──────────────┘
//
void MainWindow::restoreDefaultLayout()
{
    addDockWidget(Qt::LeftDockWidgetArea,   fileBrowserDock_);
    addDockWidget(Qt::BottomDockWidgetArea, directCommandDock_);
    addDockWidget(Qt::RightDockWidgetArea,  graphicsDock_);
    addDockWidget(Qt::RightDockWidgetArea,  helpDock_);
    addDockWidget(Qt::BottomDockWidgetArea, debugDock_);

    // Stack help below graphics on the right
    splitDockWidget(graphicsDock_, helpDock_, Qt::Vertical);

    // Put debug to the right of direct command at the bottom
    splitDockWidget(directCommandDock_, debugDock_, Qt::Horizontal);

    // Start with help hidden (user can show via View menu)
    helpDock_->hide();
}

// ── Run / Stop ────────────────────────────────────────────────────────

void MainWindow::connectRunWorker()
{
    auto *io = worker_->io();

    // Only connect I/O signals if this is NOT the persistent I/O
    // (persistent I/O signals are already connected in MainWindow constructor)
    if (io != persistentIO_) {
        // Output from the runtime → Direct Command panel
        connect(io, &QtIO::textOutput,
                directCommand_, &DirectCommandPanel::appendOutput,
                Qt::QueuedConnection);

        connect(io, &QtIO::screenCleared, directCommand_, [this]() {
            directCommand_->clearOutputPanel();
        }, Qt::QueuedConnection);

        connect(io, &QtIO::cursorMoved, directCommand_, [this](int r, int c) {
            directCommand_->appendOutput(
                QString("[CURSOR %1,%2]").arg(r).arg(c));
        }, Qt::QueuedConnection);

        // Input request: show marker in output and enable the input line
        connect(io, &QtIO::inputRequested, directCommand_, [this](const QString &prompt) {
            directCommand_->showInputMarker(prompt);
            directCommand_->setInputEnabled(true);
        }, Qt::QueuedConnection);
    }

    // Execution finished / error
    connect(worker_, &RunWorker::finished,
            this, &MainWindow::onRunFinished, Qt::QueuedConnection);
    connect(worker_, &RunWorker::errorOccurred,
            this, &MainWindow::onRunError, Qt::QueuedConnection);

    // Graphics scene changed — re-render the graphics panel
    connect(worker_, &RunWorker::sceneChanged, this, [this]() {
        graphics_->renderScene(worker_->graphicsScene());
        worker_->onSceneRendered();
    }, Qt::QueuedConnection);

    // Execution suspended (break/step) — highlight current line
    connect(worker_, &RunWorker::suspended, this, &MainWindow::onExecutionPaused,
            Qt::QueuedConnection);

    // Variables changed — update debug panel
    connect(worker_, &RunWorker::variablesChanged, debug_, &DebugPanel::updateVariables,
            Qt::QueuedConnection);

    // Call stack changed — update debug panel
    connect(worker_, &RunWorker::callStackChanged, debug_, &DebugPanel::updateCallStack,
            Qt::QueuedConnection);

    // Jump to source line when a call stack frame is activated
    connect(debug_, &DebugPanel::frameActivated, this, [this](int line) {
        codeEditor_->highlightExecutionLine(line);
    }, Qt::QueuedConnection);
}

void MainWindow::onRun()
{
    if (worker_ && worker_->isRunning()) return;

    auto *editor = codeEditor_->currentEditor();
    if (!editor) return;

    QString source = editor->text();
    lastActionWasDirectCommand_ = false;
    directCommand_->appendOutput("\n--- RUN ---\n");
    codeEditor_->clearErrorHighlight();
    codeEditor_->clearExecutionHighlight();
    // Clear scene for full program runs
    persistentScene_->clear();
    graphics_->clearCanvas();
    // Create a fresh worker each run. Do NOT reuse persistentInterp_ here:
    // it retains the previously loaded program and loadSource() will not
    // overwrite progroot, causing the wrong program to run.
    // persistentInterp_ is used only for direct commands.
    delete worker_;
    worker_ = new RunWorker(this);
    worker_->setGraphicsScene(persistentScene_.get());
    worker_->setSource(source);
    {
        auto bps = codeEditor_->breakpointsForCurrentFile();
        worker_->setBreakpoints(std::vector<int>(bps.begin(), bps.end()));
    }
    connectRunWorker();

    stateLabel_->setText(tr("Running"));
    worker_->start();
}

void MainWindow::onStop()
{
    if (worker_ && worker_->isRunning()) {
        worker_->requestStop();
        // Also unblock readLine if it's waiting for input
        worker_->io()->provideInput("");
        stateLabel_->setText(tr("Stopping..."));
    }
}

void MainWindow::onRunFinished()
{
    const bool completedDirectCommand = lastActionWasDirectCommand_;
    lastActionWasDirectCommand_ = false;
    stateLabel_->setText(tr("Ready"));
    directCommand_->setInputEnabled(false);
    codeEditor_->clearExecutionHighlight();

    if (completedDirectCommand)
        directCommand_->focusInput();
}

void MainWindow::onRunError(const QString &message, int lineNumber)
{
    QString msg = "\nERROR: " + message;
    if (lineNumber > 0)
        msg += " (line " + QString::number(lineNumber) + ")";
    msg += "\n";
    directCommand_->appendOutput(msg);
    stateLabel_->setText(tr("Error"));
    directCommand_->setInputEnabled(false);

    codeEditor_->clearExecutionHighlight();
    if (lineNumber > 0)
        codeEditor_->highlightErrorLine(lineNumber);
}

void MainWindow::onExecutionPaused(int lineNumber)
{
    codeEditor_->clearErrorHighlight();
    codeEditor_->highlightExecutionLine(lineNumber);
    stateLabel_->setText(tr("Paused"));
}

void MainWindow::onDirectCommand(const QString &command)
{
    // If a program is running and waiting for input, feed it
    if (worker_ && worker_->isRunning()) {
        if (directCommand_->isInputForProgram()) {
            directCommand_->echoInput(command);
            directCommand_->setInputEnabled(false);
            worker_->io()->provideInput(command);
        }
        return;
    }

    // Otherwise, execute as a direct COMAL command
    lastActionWasDirectCommand_ = true;
    if (!worker_) {
        worker_ = new RunWorker(this);
        worker_->setGraphicsScene(persistentScene_.get());
        worker_->setExternalInterpreter(persistentInterp_);
        connectRunWorker();
    } else {
        // Reuse existing worker; just set external interpreter again to ensure consistency
        worker_->setExternalInterpreter(persistentInterp_);
    }
    worker_->setDirectCommand(command);
    stateLabel_->setText(tr("Running"));
    worker_->start();
}

void MainWindow::onNew()
{
    codeEditor_->newTab("Untitled");
}

void MainWindow::onOpen()
{
    QString path = QFileDialog::getOpenFileName(
        this, tr("Open File"), QString(),
        tr("COMAL Files (*.lst *.cml *.prl *.prc);;All Files (*)"));
    if (!path.isEmpty())
        codeEditor_->openFile(path);
}

void MainWindow::onSave()
{
    codeEditor_->saveFile();
}

void MainWindow::onSaveAs()
{
    codeEditor_->saveFileAs();
}

void MainWindow::onCloseTab()
{
    codeEditor_->closeCurrentTab();
}

void MainWindow::updateCursorPos(int line, int col)
{
    posLabel_->setText(tr("Ln %1, Col %2").arg(line).arg(col));
}

void MainWindow::startSingleStepRun(const QString &title)
{
    if (worker_ && worker_->isRunning()) {
        lastActionWasDirectCommand_ = false;
        worker_->setSingleStep(true);
        worker_->requestContinue();
        stateLabel_->setText(tr("Stepping"));
        return;
    }

    auto *editor = codeEditor_->currentEditor();
    if (!editor) return;

    QString source = editor->text();
    lastActionWasDirectCommand_ = false;
    directCommand_->appendOutput("\n--- " + title + " ---\n");
    codeEditor_->clearErrorHighlight();
    codeEditor_->clearExecutionHighlight();
    // Clear scene for full program runs
    persistentScene_->clear();
    graphics_->clearCanvas();
    // Create a fresh worker each run (no persistentInterp_ — see onRun() comment).
    delete worker_;
    worker_ = new RunWorker(this);
    worker_->setGraphicsScene(persistentScene_.get());
    worker_->setSource(source);
    {
        auto bps = codeEditor_->breakpointsForCurrentFile();
        worker_->setBreakpoints(std::vector<int>(bps.begin(), bps.end()));
    }
    worker_->setSingleStep(true);  // Enable single-step mode
    connectRunWorker();

    stateLabel_->setText(tr("Stepping"));
    worker_->start();
}

void MainWindow::onStepInto()
{
    startSingleStepRun(tr("STEP INTO"));
}

void MainWindow::onStepOver()
{
    startSingleStepRun(tr("STEP OVER"));
}

void MainWindow::onFormatSource(){ codeEditor_->formatSource(); }

void MainWindow::onResetLayout()
{
    // Remove all docks and re-add in default positions
    removeDockWidget(fileBrowserDock_);
    removeDockWidget(directCommandDock_);
    removeDockWidget(graphicsDock_);
    removeDockWidget(debugDock_);
    removeDockWidget(helpDock_);
    restoreDefaultLayout();
    fileBrowserDock_->show();
    directCommandDock_->show();
    graphicsDock_->show();
    debugDock_->show();
}

void MainWindow::onBreak()
{
    if (!worker_ || !worker_->isRunning())
        return;
    worker_->requestBreak();
    stateLabel_->setText(tr("Paused (Break)"));
}

void MainWindow::onContinue()
{
    if (worker_ && worker_->isRunning()) {
        worker_->setSingleStep(false);  // Disable single-step when continuing
        worker_->requestContinue();
        stateLabel_->setText(tr("Running"));
    }
}

// ── Settings & Persistence ──────────────────────────────────────────

void MainWindow::onSettings()
{
    auto *dialog = new SettingsDialog(this);

    connect(dialog, &SettingsDialog::fontsApplied, this,
            [this](const QFont &editorFont, const QFont &outputFont) {
        if (codeEditor_)
            codeEditor_->applyFontToAllEditors(editorFont);
        if (directCommand_)
            directCommand_->applyFont(outputFont);
    });

    if (dialog->exec() == QDialog::Accepted) {
        applyFontSettingsFromDialog(dialog);
    }
    delete dialog;
}

void MainWindow::saveWindowState()
{
    QSettings settings("OpenCOMAL", "IDE");

    // Save window geometry (position and size)
    settings.setValue("MainWindow/Geometry", saveGeometry());
    settings.setValue("MainWindow/WindowState", saveState());

    // Save dock visibility and positions
    settings.setValue("Docks/DirectCommandVisible", directCommandDock_->isVisible());
    settings.setValue("Docks/GraphicsVisible", graphicsDock_->isVisible());
    settings.setValue("Docks/DebugVisible", debugDock_->isVisible());
    settings.setValue("Docks/FileBrowserVisible", fileBrowserDock_->isVisible());
    settings.setValue("Docks/HelpVisible", helpDock_->isVisible());

    settings.sync();
}

void MainWindow::restoreWindowState()
{
    QSettings settings("OpenCOMAL", "IDE");

    // Restore window geometry (position and size)
    QByteArray geometry = settings.value("MainWindow/Geometry", QByteArray()).toByteArray();
    if (!geometry.isEmpty()) {
        restoreGeometry(geometry);
    }

    QByteArray windowState = settings.value("MainWindow/WindowState", QByteArray()).toByteArray();
    if (!windowState.isEmpty()) {
        restoreState(windowState);
    }

    // Restore dock visibility
    bool directCommandVisible = settings.value("Docks/DirectCommandVisible", true).toBool();
    bool graphicsVisible = settings.value("Docks/GraphicsVisible", true).toBool();
    bool debugVisible = settings.value("Docks/DebugVisible", true).toBool();
    bool fileBrowserVisible = settings.value("Docks/FileBrowserVisible", true).toBool();
    bool helpVisible = settings.value("Docks/HelpVisible", false).toBool();

    directCommandDock_->setVisible(directCommandVisible);
    graphicsDock_->setVisible(graphicsVisible);
    debugDock_->setVisible(debugVisible);
    fileBrowserDock_->setVisible(fileBrowserVisible);
    helpDock_->setVisible(helpVisible);

    // Restore font settings and apply them
    QSettings fontSettings("OpenCOMAL", "IDE");
    QString editorFontFamily = fontSettings.value("EditorFont/Family", "Monospace").toString();
    int editorFontSize = fontSettings.value("EditorFont/Size", 11).toInt();
    QString outputFontFamily = fontSettings.value("OutputFont/Family", "Monospace").toString();
    int outputFontSize = fontSettings.value("OutputFont/Size", 11).toInt();

    // Apply editor font
    if (codeEditor_) {
        QFont editorFont(editorFontFamily, editorFontSize);
        codeEditor_->applyFontToAllEditors(editorFont);
    }

    // Apply output panel font
    if (directCommand_) {
        QFont outputFont(outputFontFamily, outputFontSize);
        directCommand_->applyFont(outputFont);
    }
}

void MainWindow::applyFontSettingsFromDialog(SettingsDialog *dialog)
{
    QFont editorFont = dialog->editorFont();
    QFont outputFont = dialog->outputFont();

    // Apply editor font to all tabs
    if (codeEditor_) {
        codeEditor_->applyFontToAllEditors(editorFont);
    }

    // Apply output panel font
    if (directCommand_) {
        directCommand_->applyFont(outputFont);
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveWindowState();
    QMainWindow::closeEvent(event);
}

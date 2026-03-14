#include "main_window.h"
#include "code_editor_panel.h"
#include "direct_command_panel.h"
#include "graphics_panel.h"
#include "debug_panel.h"
#include "file_browser_panel.h"
#include "help_panel.h"
#include "run_worker.h"
#include "qt_io.h"
#include "comal_scene_model.h"

#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QDockWidget>
#include <QLabel>
#include <QAction>
#include <QKeySequence>
#include <QFileDialog>
#include <Qsci/qsciscintilla.h>

MainWindow::~MainWindow() = default;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , persistentScene_(std::make_unique<comal::graphics::Scene>())
{
    setWindowTitle("OpenCOMAL IDE");
    resize(1280, 800);

    createPanels();
    createMenus();

    createToolBar();
    createStatusBar();
    restoreDefaultLayout();

    // LSP client setup
    lspClient_ = new ComalLspClient(this);
    codeEditor_->setLspClient(lspClient_);
    // Start LSP server (adjust path as needed)
    lspClient_->startServer("../build/comal-lsp/comal-lsp");
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
    progMenu->addAction(tr("Toggle &Breakpoint"), this, []{},
                         QKeySequence(Qt::Key_F9));

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
    settingsMenu->addAction(tr("&Font && Colors..."))->setEnabled(false);
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

    // Help — right
    help_ = new HelpPanel;
    helpDock_ = new QDockWidget(tr("Help"), this);
    helpDock_->setObjectName("HelpDock");
    helpDock_->setWidget(help_);

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

    // Output from the runtime → Direct Command panel
    connect(io, &QtIO::textOutput,
            directCommand_, &DirectCommandPanel::appendOutput,
            Qt::QueuedConnection);

    connect(io, &QtIO::screenCleared, directCommand_, [this]() {
        directCommand_->appendOutput("\n--- PAGE ---\n");
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

    // Execution finished / error
    connect(worker_, &RunWorker::finished,
            this, &MainWindow::onRunFinished, Qt::QueuedConnection);
    connect(worker_, &RunWorker::errorOccurred,
            this, &MainWindow::onRunError, Qt::QueuedConnection);

    // Graphics scene changed — re-render the graphics panel
    connect(worker_, &RunWorker::sceneChanged, this, [this]() {
        graphics_->renderScene(worker_->graphicsScene());
    }, Qt::QueuedConnection);

    // Execution suspended (break/step) — highlight current line
    connect(worker_, &RunWorker::suspended, this, &MainWindow::onExecutionPaused,
            Qt::QueuedConnection);
}

void MainWindow::onRun()
{
    if (worker_ && worker_->isRunning()) return;

    auto *editor = codeEditor_->currentEditor();
    if (!editor) return;

    QString source = editor->text();
    directCommand_->appendOutput("\n--- RUN ---\n");
    codeEditor_->clearErrorHighlight();
    codeEditor_->clearExecutionHighlight();
    // Clear scene for full program runs
    persistentScene_->clear();
    graphics_->clearCanvas();
    // Create a fresh worker each run
    delete worker_;
    worker_ = new RunWorker(this);
    worker_->setGraphicsScene(persistentScene_.get());
    worker_->setSource(source);
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
    directCommand_->appendOutput("\n--- DONE ---\n");
    stateLabel_->setText(tr("Ready"));
    directCommand_->setInputEnabled(false);
    codeEditor_->clearExecutionHighlight();
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
    delete worker_;
    worker_ = new RunWorker(this);
    worker_->setGraphicsScene(persistentScene_.get());
    worker_->setDirectCommand(command);
    connectRunWorker();
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
        worker_->setSingleStep(true);
        worker_->requestContinue();
        stateLabel_->setText(tr("Stepping"));
        return;
    }

    auto *editor = codeEditor_->currentEditor();
    if (!editor) return;

    QString source = editor->text();
    directCommand_->appendOutput("\n--- " + title + " ---\n");
    codeEditor_->clearErrorHighlight();
    codeEditor_->clearExecutionHighlight();
    // Clear scene for full program runs
    persistentScene_->clear();
    graphics_->clearCanvas();
    // Create a fresh worker each run
    delete worker_;
    worker_ = new RunWorker(this);
    worker_->setGraphicsScene(persistentScene_.get());
    worker_->setSource(source);
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

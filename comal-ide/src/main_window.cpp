#include "main_window.h"
#include "code_editor_panel.h"
#include "direct_command_panel.h"
#include "graphics_panel.h"
#include "debug_panel.h"
#include "file_browser_panel.h"
#include "help_panel.h"

#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QDockWidget>
#include <QLabel>
#include <QAction>
#include <QKeySequence>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("OpenCOMAL IDE");
    resize(1280, 800);

    createPanels();
    createMenus();
    createToolBar();
    createStatusBar();
    restoreDefaultLayout();
}

// ── Menus ───────────────────────────────────────────────────────────

void MainWindow::createMenus()
{
    // File
    auto *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(tr("&New"),        this, []{}  , QKeySequence::New);
    fileMenu->addAction(tr("&Open..."),    this, []{}  , QKeySequence::Open);
    fileMenu->addAction(tr("&Save"),       this, []{}  , QKeySequence::Save);
    fileMenu->addAction(tr("Save &As..."), this, []{});
    fileMenu->addSeparator();
    fileMenu->addAction(tr("Recent Files"))->setEnabled(false);
    fileMenu->addSeparator();
    fileMenu->addAction(tr("&Close"),      this, []{}  , QKeySequence::Close);
    fileMenu->addAction(tr("E&xit"),       this, &QWidget::close, QKeySequence::Quit);

    // Edit
    auto *editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(tr("&Undo"),          this, []{}, QKeySequence::Undo);
    editMenu->addAction(tr("&Redo"),          this, []{}, QKeySequence::Redo);
    editMenu->addSeparator();
    editMenu->addAction(tr("Cu&t"),           this, []{}, QKeySequence::Cut);
    editMenu->addAction(tr("&Copy"),          this, []{}, QKeySequence::Copy);
    editMenu->addAction(tr("&Paste"),         this, []{}, QKeySequence::Paste);
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
    tb->addSeparator();
    tb->addAction(tr("Step Into"), this, &MainWindow::onStepInto);
    tb->addAction(tr("Step Over"), this, &MainWindow::onStepOver);
    tb->addAction(tr("Continue"),  this, &MainWindow::onContinue);
}

// ── Status bar ──────────────────────────────────────────────────────

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
    auto *posLabel = new QLabel(tr("Ln 1, Col 1"));
    posLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    statusBar()->addPermanentWidget(posLabel);

    auto *stateLabel = new QLabel(tr("Ready"));
    stateLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    statusBar()->addPermanentWidget(stateLabel);
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

    // Help — right
    help_ = new HelpPanel;
    helpDock_ = new QDockWidget(tr("Help"), this);
    helpDock_->setObjectName("HelpDock");
    helpDock_->setWidget(help_);
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

// ── Slot stubs ──────────────────────────────────────────────────────

void MainWindow::onRun()         { statusBar()->showMessage(tr("Running...")); }
void MainWindow::onStop()        { statusBar()->showMessage(tr("Stopped")); }
void MainWindow::onStepInto()    { statusBar()->showMessage(tr("Step Into")); }
void MainWindow::onStepOver()    { statusBar()->showMessage(tr("Step Over")); }
void MainWindow::onContinue()    { statusBar()->showMessage(tr("Continuing...")); }
void MainWindow::onFormatSource(){ statusBar()->showMessage(tr("Format Source — not yet implemented")); }

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

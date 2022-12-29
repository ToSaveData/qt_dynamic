#include "mainwindow.h"

#include <QUrl>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QLineEdit>
#include <QWebEngineHistory>
#include <QApplication>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(600, 600);
    webEngineView = new QWebEngineView(this);
    webEngineView->setUrl(QUrl("http://www.google.com"));
    lineEditURL = new QLineEdit(this);
    assert(connect(lineEditURL, SIGNAL(returnPressed()), SLOT(goSlot())));

    QAction *actionOpen = new QAction("Open", this);
    assert(connect(actionOpen, SIGNAL(triggered()), SLOT(goSlot())));
    QAction *actionQuit = new QAction("Quit", this);
    assert(connect(actionQuit, SIGNAL(triggered()), qApp, SLOT(quit())));

    QAction *actionGo = new QAction("Go", this);
    assert(connect(actionGo, SIGNAL(triggered()), SLOT(goSlot())));

    QAction *actionBackward = new QAction("Back", this);
    assert(connect(actionBackward, SIGNAL(triggered()), SLOT(goBackwardSlot())));
    QAction *actionForward = new QAction("Forward", this);
    assert(connect(actionForward, SIGNAL(triggered()), SLOT(goForwardSlot())));

    QAction *actionHome = new QAction("Home", this);
    assert(connect(actionHome, SIGNAL(triggered()), SLOT(goHomeSlot())));

    QAction *actionReload = new QAction("Reload", this);
    assert(connect(actionReload, SIGNAL(triggered()), webEngineView, SLOT(reload())));

    QAction *actionStop = new QAction("Stop", this);
    assert(connect(actionStop, SIGNAL(triggered()), webEngineView, SLOT(stop())));

    QAction *actionAbout = new QAction("About", this);
    assert(connect(actionAbout, SIGNAL(triggered()), qApp, SLOT(aboutQt())));

    QMenuBar *menubar = menuBar();

    QMenu *menuFile = new QMenu("&File", menubar);
    menuFile->addAction(actionOpen);
    menuFile->addSeparator();
    menuFile->addAction(actionQuit);
    menubar->addMenu(menuFile);

    QMenu *menuView = new QMenu("&View", menubar);
    menuView->addAction(actionGo);
    menuView->addAction(actionBackward);
    menuView->addAction(actionForward);
    menuView->addAction(actionStop);
    menuView->addAction(actionReload);
    menuView->addSeparator();
    menuView->addAction(actionHome);
    menubar->addMenu(menuView);

    QMenu *menuHelp = new QMenu("&Help", menubar);
    menuHelp->addAction(actionAbout);
    menubar->addMenu(menuHelp);

    QToolBar *toolBarNavigaion = new QToolBar("Navigation", this);
    toolBarNavigaion->addAction(actionBackward);
    toolBarNavigaion->addAction(actionForward);
    toolBarNavigaion->addSeparator();
    toolBarNavigaion->addAction(actionReload);
    toolBarNavigaion->addAction(actionStop);
    toolBarNavigaion->addSeparator();
    toolBarNavigaion->addWidget(lineEditURL);
    addToolBar(Qt::TopToolBarArea, toolBarNavigaion);

//    QStatusBar * statusbar = statusBar();

    setCentralWidget(webEngineView);
}

MainWindow::~MainWindow()
{
}

void MainWindow::goSlot()
{
    QUrl url(lineEditURL->text());
    webEngineView->load(url);
    update();
}
void MainWindow::goBackwardSlot()
{
    QWebEngineHistory *history = webEngineView->history();
    if(history->canGoBack())    history->back();
    update();
}
void MainWindow::goForwardSlot()
{
    QWebEngineHistory *history = webEngineView->history();
    if(history->canGoForward())    history->forward();
    update();
}
void MainWindow::goHomeSlot()
{
    QUrl url(lineEditURL->text());
    webEngineView->load(url);
    update();
}

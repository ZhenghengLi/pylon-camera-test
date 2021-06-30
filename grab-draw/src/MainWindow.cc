#include "MainWindow.hh"
#include <iostream>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QApplication>

MainWindow::MainWindow() {

    resize(1000, 700);
    setWindowIcon(QIcon(":/icons/logo.png"));

    createActions();
    createMenus();
    createToolBars();
}

MainWindow::~MainWindow() {}

void MainWindow::closeEvent(QCloseEvent* event) {
    //
    std::cout << "Main Window is closed." << std::endl;
}

void MainWindow::createActions() {
    // about
    aboutQtAction_ = new QAction(tr("About &Qt"), this);
    aboutQtAction_->setStatusTip(tr("Show the Qt library's About box."));
    connect(aboutQtAction_, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    // start
    startAction_ = new QAction(tr("Start"), this);
    // stop
    stopAction_ = new QAction(tr("Stop"), this);
}

void MainWindow::createMenus() {
    QMenu* aboutMenu = menuBar()->addMenu(tr("&About"));
    aboutMenu->addAction(aboutQtAction_);
}

void MainWindow::createToolBars() {
    actionToolBar_ = addToolBar(tr("Actions"));
    actionToolBar_->addAction(startAction_);
    actionToolBar_->addAction(stopAction_);
}

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

    startAction_ = new QAction(tr("Start"), this);
    stopAction_ = new QAction(tr("Stop"), this);
    openAction_ = new QAction(tr("Open"), this);
    closeAction_ = new QAction(tr("Close"), this);
}

void MainWindow::createMenus() {
    QMenu* operationMenu = menuBar()->addMenu(tr("&Operations"));
    operationMenu->addAction(openAction_);
    operationMenu->addAction(closeAction_);
    operationMenu->addSeparator();
    operationMenu->addAction(startAction_);
    operationMenu->addAction(stopAction_);
    QMenu* aboutMenu = menuBar()->addMenu(tr("&About"));
    aboutMenu->addAction(aboutQtAction_);
}

void MainWindow::createToolBars() {
    operationToolBar_ = addToolBar(tr("Operations"));
    operationToolBar_->addAction(openAction_);
    operationToolBar_->addAction(closeAction_);
    operationToolBar_->addSeparator();
    operationToolBar_->addAction(startAction_);
    operationToolBar_->addAction(stopAction_);
}

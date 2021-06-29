#include "MainWindow.hh"
#include <iostream>
#include <QMenuBar>
#include <QMenu>
#include <QApplication>

MainWindow::MainWindow() {

    resize(1000, 700);
    setWindowIcon(QIcon(":/icons/logo.png"));

    createActions();
    createMenus();
}

void MainWindow::closeEvent(QCloseEvent* event) {
    //
    std::cout << "Main Window is closed." << std::endl;
}

void MainWindow::createActions() {
    aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setStatusTip(tr("Show the Qt library's About box."));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus() {
    QMenu* aboutMenu = menuBar()->addMenu(tr("&About"));
    aboutMenu->addAction(aboutQtAction);
}

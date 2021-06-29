#include "MainWindow.hh"
#include <iostream>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QApplication>

MainWindow::MainWindow() {
    resize(1000, 700);
    setWindowIcon(QIcon(":/images/logo.png"));
    createMenus();
}

void MainWindow::closeEvent(QCloseEvent* event) {
    //
    std::cout << "Main Window is closed." << std::endl;
}

void MainWindow::createMenus() {
    QAction* aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setStatusTip(tr("Show the Qt library's About box."));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    QMenu* about = menuBar()->addMenu(tr("&About"));
    about->addAction(aboutQtAction);
}

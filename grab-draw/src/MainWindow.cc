#include "MainWindow.hh"
#include <iostream>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QApplication>

MainWindow::MainWindow() {

    resize(1000, 700);
    setWindowIcon(QIcon(":/icons/logo.png"));

    imageGrabber_ = new ImageGrabber(this);
    imageCanvas_ = new ImageCanvas(this);
    connect(imageGrabber_, &ImageGrabber::imageGrabbed, imageCanvas_, &ImageCanvas::drawImage);

    createActions();
    createMenus();
    createToolBars();
}

MainWindow::~MainWindow() {}

void MainWindow::closeEvent(QCloseEvent* event) {
    imageGrabber_->close();
    std::cout << "Main Window is closed." << std::endl;
}

void MainWindow::createActions() {
    // about
    aboutQtAction_ = new QAction(tr("About &Qt"), this);
    aboutQtAction_->setStatusTip(tr("Show the Qt library's About box."));
    connect(aboutQtAction_, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    openAction_ = new QAction(tr("Open"), this);
    connect(openAction_, SIGNAL(triggered()), imageGrabber_, SLOT(open()));

    closeAction_ = new QAction(tr("Close"), this);
    connect(closeAction_, SIGNAL(triggered()), imageGrabber_, SLOT(close()));

    startAction_ = new QAction(tr("Start"), this);
    connect(startAction_, SIGNAL(triggered()), imageGrabber_, SLOT(start()));

    stopAction_ = new QAction(tr("Stop"), this);
    connect(stopAction_, SIGNAL(triggered()), imageGrabber_, SLOT(stop()));
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

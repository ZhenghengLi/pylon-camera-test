#include "MainWindow.hh"
#include <iostream>

MainWindow::MainWindow() {
    //
}

void MainWindow::closeEvent(QCloseEvent* event) {
    //
    std::cout << "Main Window is closed." << std::endl;
}
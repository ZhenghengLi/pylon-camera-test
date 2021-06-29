#include <iostream>
#include <QApplication>
#include <QProgressDialog>

#include "MainWindow.hh"

using namespace std;

int main(int argc, char** argv) {

    QApplication app(argc, argv);

    MainWindow* window = new MainWindow();

    window->show();

    return app.exec();
}
#include <iostream>
#include <QApplication>
#include <QProgressDialog>
#include <pylon/PylonBase.h>

#include "MainWindow.hh"

using namespace std;

int main(int argc, char** argv) {
    Pylon::PylonAutoInitTerm autoInitTerm;

    QApplication app(argc, argv);

    MainWindow* window = new MainWindow();

    window->show();

    return app.exec();
}

#ifndef __MainWindow_H__
#define __MainWindow_H__

#include <QMainWindow>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();

protected:
    void createMenus();
    void closeEvent(QCloseEvent* event) override;
};

#endif
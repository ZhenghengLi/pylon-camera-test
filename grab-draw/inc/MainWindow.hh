#ifndef __MainWindow_H__
#define __MainWindow_H__

#include <QMainWindow>
#include <QAction>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    void createActions();
    void createMenus();

private: // actions
    QAction* aboutQtAction;
};

#endif
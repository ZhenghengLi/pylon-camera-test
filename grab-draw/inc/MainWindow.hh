#ifndef __MainWindow_H__
#define __MainWindow_H__

#include <QMainWindow>
#include <QAction>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    void createActions();
    void createMenus();
    void createToolBars();

private: // actions
    QAction* aboutQtAction_;
    QAction* startAction_;
    QAction* stopAction_;

private: // toolbars
    QToolBar* actionToolBar_;
};

#endif
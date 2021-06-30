#ifndef __MainWindow_H__
#define __MainWindow_H__

#include <QMainWindow>
#include <QAction>
#include "ImageGrabber.hh"

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
    QAction* openAction_;
    QAction* closeAction_;

private: // toolbars
    QToolBar* operationToolBar_;

private: // qobjects
    ImageGrabber* imageGrabber_;
};

#endif
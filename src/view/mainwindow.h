#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mainwindowcontroller.h>
#include <iostream>
#include <QPoint>

namespace Ui {
class MainWindow;
}

using namespace std;
class MainWindowController;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    MainWindow(MainWindowController* mc);
    ~MainWindow();

    QPoint _dragPosition;

    void init_view();



    void mousePressEvent(QMouseEvent* event);

    void mouseMoveEvent(QMouseEvent* event);


    MainWindowController* _mainWindowCtrl;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

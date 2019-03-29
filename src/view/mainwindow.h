#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mainwindowcontroller.h>

namespace Ui {
class MainWindow;
}

class MainWindowController;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    MainWindow(MainWindowController* mc);
    ~MainWindow();

    void init_view();

    MainWindowController* _mainWindowCtrl;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

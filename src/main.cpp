
#include <QApplication>
#include "mainwindowcontroller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindowController* mc = new MainWindowController;
    mc->show();

    return a.exec();
}

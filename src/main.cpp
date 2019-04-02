
#include <QApplication>
#include "mainwindowcontroller.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindowController* mc = new MainWindowController;
    cout<<"11"<<endl;
    mc->show();

    return a.exec();
}

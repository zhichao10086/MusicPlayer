
#include <QApplication>
#include "mainwindowcontroller.h"
#include <iostream>
#include <Python.h>
#include "mp3header.h"
extern "C"
{
    #include <libavutil/avutil.h>
}


using namespace std;


int main(int argc, char *argv[])
{
    /*
    Py_Initialize();
    PyRun_SimpleString("print 'Hello Python! this is mengtianwxs'\n");
    PyObject* pm = PyImport_ImportModule("test");
    if(!pm){
        cout<<"cuowu"<<endl;
        Py_Finalize();
        return -1;
    }
    Py_Finalize();
    */
    cout<<av_version_info()<<endl;

    QApplication a(argc, argv);

    MainWindowController* mc = new MainWindowController;
    //cout<<"11"<<endl;
    mc->show();

    return a.exec();
}

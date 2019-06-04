
#include <QApplication>
#include "mainwindowcontroller.h"
#include <iostream>



using namespace std;

#undef main
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
    //avcodec_init();
    //av_register_all();
    //avformat_network_init();
    //avdevice_register_all();

    //cout<<av_version_info()<<endl;

    QApplication a(argc, argv);

    MainWindowController* mc = new MainWindowController;
    //cout<<"11"<<endl;
    mc->show();

    return a.exec();
}

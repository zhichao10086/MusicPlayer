
#include <QApplication>
#include "mainwindowcontroller.h"
#include <iostream>


extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
#include <libavutil/opt.h>
#include <libavutil/mathematics.h>
#include <libavutil/samplefmt.h>
#include <libavdevice/avdevice.h>
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

#include "mainwindowcontroller.h"

MainWindowController::MainWindowController()
{
    this->init();
}

void MainWindowController::init()
{
    this->_mainWindowModel = new MainWindowmodel(this);
    this->_mainWindow  = new MainWindow(this);



}

void MainWindowController::show()
{
    cout<<"mainwindhwo ahow"<<endl;
    this->_mainWindow->init_view();
    this->_mainWindow->show();

}

void MainWindowController::closeApp()
{
    cout<<"mainwindowctrl close app"<<endl;
    qApp->exit(0);
}

void MainWindowController::minApp()
{
    cout<<"sss"<<endl;
    this->_mainWindow->setWindowState(Qt::WindowMinimized);
}

void MainWindowController::maxApp()
{
//    QRect rect=QApplication::desktop()->availableGeometry();
//    this->_mainWindow->move(0,0);
//    this->_mainWindow->resize(rect.width(),rect.height());
    //this->_mainWindow->centralWidget()->hide();
    if(this->_mainWindow->isFullScreen()){
        qDebug()<<"max";
        this->_mainWindow->resize(1400,900);
        this->_mainWindow->setWindowState(Qt::WindowActive);
    }else{
        qDebug()<<"min";
        this->_mainWindow->setWindowState(Qt::WindowFullScreen);
    }


    //this->_mainWindow->centralWidget()->show();
}

MusicPlayerView *MainWindowController::getMusicPlayerView()
{
    return this->_mainWindowModel->getMusicPlayerView();
}

MainWindow *MainWindowController::getMainWindow() const
{
    return _mainWindow;
}

void MainWindowController::setMainWindow(MainWindow *mainWindow)
{
    _mainWindow = mainWindow;
}

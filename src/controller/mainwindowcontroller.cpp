#include "mainwindowcontroller.h"

MainWindowController::MainWindowController()
{
    this->init();
}

void MainWindowController::init()
{
    this->_mainWindowModel = new MainWindowmodel;
    this->_mainWindow  = new MainWindow(this);



}

void MainWindowController::show()
{
    this->_mainWindow->show();
}

MusicPlayerView *MainWindowController::getMusicPlayerView()
{
    return this->_mainWindowModel->getMusicPlayerView();
}

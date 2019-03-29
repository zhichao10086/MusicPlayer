#include "mainwindowcontroller.h"

MainWindowController::MainWindowController()
{
    this->init();
}

void MainWindowController::init()
{
    this->_mainWindow  = new MainWindow(this);
    this->_mainWindowModel = new MainWindowmodel;

    //为Model设置数据
    MusicPlayerController* mpc = new MusicPlayerController;
    this->_mainWindowModel->setMusicPlayerController(mpc);

}

void MainWindowController::show()
{
    this->_mainWindow->init_view();
    this->_mainWindow->show();
}

MusicPlayerView *MainWindowController::getMusicPlayerView()
{
    return this->_mainWindowModel->musicPlayerController()->musicPlayerView();
}

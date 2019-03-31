#include "mainwindowmodel.h"

MainWindowmodel::MainWindowmodel()
{
    init();
}

void MainWindowmodel::init()
{
    //初始化音乐器主界面控制器
    this->_musicPlayerController = new MusicPlayerController;

}

MusicPlayerView *MainWindowmodel::getMusicPlayerView() const
{
    return this->_musicPlayerController->musicPlayerView();
}

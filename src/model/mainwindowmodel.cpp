#include "mainwindowmodel.h"

MainWindowmodel::MainWindowmodel()
{
    init();
}

MainWindowmodel::MainWindowmodel(MainWindowController *mwc)
{
    this->_mainWindowCtrl = mwc;
    init();
}

void MainWindowmodel::init()
{

    this->_musicPlayerController = new MusicPlayerController(this->_mainWindowCtrl);


}

MusicPlayerView *MainWindowmodel::getMusicPlayerView() const
{
    return this->_musicPlayerController->musicPlayerView();
}

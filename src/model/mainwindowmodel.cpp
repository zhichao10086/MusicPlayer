#include "mainwindowmodel.h"

MainWindowmodel::MainWindowmodel()
{

}

MusicPlayerController *MainWindowmodel::musicPlayerController() const
{
    return _musicPlayerController;
}

void MainWindowmodel::setMusicPlayerController(MusicPlayerController *musicPlayerController)
{
    _musicPlayerController = musicPlayerController;
}

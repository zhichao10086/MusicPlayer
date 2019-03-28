#include "musicplayercontroller.h"

MusicPlayerController::MusicPlayerController()
{

    init();

}

MusicPlayerController *MusicPlayerController::newInstance()
{

    MusicPlayerController* mpc = new MusicPlayerController;

    return mpc;

}

void MusicPlayerController::init()
{
    _musicPlayerView = new MusicPlayerView(this,0);
    _musicPlayerModel = new MusicPlayerModel;
}

void MusicPlayerController::show()
{
    this->_musicPlayerView->show();
}

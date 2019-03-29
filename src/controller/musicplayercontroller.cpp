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

MusicPlayerView *MusicPlayerController::musicPlayerView() const
{
    return _musicPlayerView;
}

void MusicPlayerController::setMusicPlayerView(MusicPlayerView *musicPlayerView)
{
    _musicPlayerView = musicPlayerView;
}

void MusicPlayerController::init()
{
    _musicPlayerView = new MusicPlayerView(this);
    _musicPlayerModel = new MusicPlayerModel;
}

void MusicPlayerController::show()
{
    this->_musicPlayerView->show();
}

#include "musicplayercontroller.h"

MusicPlayerController::MusicPlayerController()
{
    //初始化mvc模型
    init();

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
    _musicPlayerModel = new MusicPlayerModel;
    _musicPlayerView = new MusicPlayerView(this);

}

void MusicPlayerController::init_view()
{

}

void MusicPlayerController::show()
{
    this->_musicPlayerView->show();
}

void MusicPlayerController::setMainWindowWidget(int mode)
{
    QWidget* w;

    switch (mode) {
    case LOCAL_FILE_WINDOW:
        w = this->_musicPlayerModel->localMusicView();
        break;
    case DOWNLOAD_FILE_WINDOW:

        break;
    default:
        break;
    }

    this->_musicPlayerView->setMainWindowWidget(w);

}

void MusicPlayerController::removeMainWindowWidget(int mode)
{
    this->_musicPlayerView->removeMainWindowWidget();
}

LocalMusicView *MusicPlayerController::getLocalMusicView()
{
    return this->_musicPlayerModel->_localMusicView;
}

PlayFuncView *MusicPlayerController::getPlayFuncView() const
{
    return this->_musicPlayerModel->pfView();
}

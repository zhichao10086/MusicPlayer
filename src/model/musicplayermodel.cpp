#include "musicplayermodel.h"

MusicPlayerModel::MusicPlayerModel()
{
    this->init();
}

void MusicPlayerModel::init()
{




    //播放功能控制器与界面
    _pfc = new PlayFuncController;
    _pfView = _pfc->playFuncView();
    _pfModel = _pfc->playFuncModel();

    //本地文件控制器与界面
    _localMusicCtrl  =  new LocalMusicController(_pfc);
    _localMusicModel = _localMusicCtrl->localMusicModel();
    _localMusicView = _localMusicCtrl->localMusicView();
}

LocalMusicController *MusicPlayerModel::localMusicCtrl() const
{
    return _localMusicCtrl;
}

LocalMusicView *MusicPlayerModel::localMusicView() const
{
    return _localMusicView;
}

PlayFuncView *MusicPlayerModel::pfView() const
{
    return _pfView;
}

void MusicPlayerModel::setPfView(PlayFuncView *pfView)
{
    _pfView = pfView;
}

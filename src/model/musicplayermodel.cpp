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

    //下载文件控制器与界面
    _downloadCtrl = new DownLoadController(_pfc);
    _downloadModel = _downloadCtrl->downLoadModel();
    _downloadView = _downloadCtrl->downLoadView();

}

MainWindow *MusicPlayerModel::mainWindow() const
{
    return _mainWindow;
}

void MusicPlayerModel::setMainWindow(MainWindow *mainWindow)
{
    _mainWindow = mainWindow;
}


MainWindowController *MusicPlayerModel::mainWindowCtrl() const
{
    return _mainWindowCtrl;
}

void MusicPlayerModel::setMainWindowCtrl(MainWindowController *mainWindowCtrl)
{
    _mainWindowCtrl = mainWindowCtrl;
}


DownLoadView *MusicPlayerModel::downloadView() const
{
    return _downloadView;
}

void MusicPlayerModel::setDownloadView(DownLoadView *downloadView)
{
    _downloadView = downloadView;
}

DownLoadModel *MusicPlayerModel::downloadModel() const
{
    return _downloadModel;
}

void MusicPlayerModel::setDownloadModel(DownLoadModel *downloadModel)
{
    _downloadModel = downloadModel;
}

DownLoadController *MusicPlayerModel::downloadCtrl() const
{
    return _downloadCtrl;
}

void MusicPlayerModel::setDownloadCtrl(DownLoadController *downloadCtrl)
{
    _downloadCtrl = downloadCtrl;
}

PlayFuncModel *MusicPlayerModel::pfModel() const
{
    return _pfModel;
}

void MusicPlayerModel::setPfModel(PlayFuncModel *pfModel)
{
    _pfModel = pfModel;
}

PlayFuncController *MusicPlayerModel::pfc() const
{
    return _pfc;
}

void MusicPlayerModel::setPfc(PlayFuncController *pfc)
{
    _pfc = pfc;
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

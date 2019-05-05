#include "musicplayermodel.h"

MusicPlayerModel::MusicPlayerModel()
{
    this->init();
}

MusicPlayerModel::MusicPlayerModel(MusicPlayerController *mpc)
{
    this->_musicPlayerCtrl = mpc;
    this->init();
}

void MusicPlayerModel::init()
{

    //播放功能控制器与界面
    _pfc = new PlayFuncController(this->_musicPlayerCtrl);
    _pfView = _pfc->playFuncView();
    _pfModel = _pfc->playFuncModel();

    MusicPlayerController::single_playfuncCtrl = _pfc;
    qDebug()<<"初始化播放控制完毕";

    //本地文件控制器与界面
    _localMusicCtrl  =  new LocalMusicController(_pfc);
    _localMusicModel = _localMusicCtrl->localMusicModel();
    _localMusicView = _localMusicCtrl->localMusicView();

    qDebug()<<"初始化本地控制完毕";


    //下载文件控制器与界面
    _downloadCtrl = new DownLoadController(_pfc);
    _downloadModel = _downloadCtrl->downLoadModel();
    _downloadView = _downloadCtrl->downLoadView();

    //歌曲列表详细界面
    _musicSheetDetialCtrl = MusicSheetDetialController::newInstance();
    _musicSheetDetialModel = _musicSheetDetialCtrl->msdModel();
    _musicSheetDetialView = _musicSheetDetialCtrl->msdView();

}

MusicSheetDetialController *MusicPlayerModel::musicSheetDetialCtrl() const
{
    return _musicSheetDetialCtrl;
}

void MusicPlayerModel::setMusicSheetDetialCtrl(MusicSheetDetialController *musicSheetDetialCtrl)
{
    _musicSheetDetialCtrl = musicSheetDetialCtrl;
}

MusicSheetDetialView *MusicPlayerModel::musicSheetDetialView() const
{
    return _musicSheetDetialView;
}

void MusicPlayerModel::setMusicSheetDetialView(MusicSheetDetialView *musicSheetDetialView)
{
    _musicSheetDetialView = musicSheetDetialView;
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

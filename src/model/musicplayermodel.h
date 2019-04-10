#ifndef MUSICPLAYERMODEL_H
#define MUSICPLAYERMODEL_H

#include "playfunccontroller.h"
#include "localmusiccontroller.h"
#include "downloadcontroller.h"
#include "downloadmodel.h"
#include "downloadview.h"
#include "mainwindowcontroller.h"
#include "mainwindow.h"


class DownLoadController;
class DownLoadModel;
class DownLoadView;
class MainWindowController;
class MainWindow;
class PlayFuncView;
class PlayFuncModel;
class LocalMusicController;
class LocalMusicModel;
class LocalMusicView;



class MusicPlayerModel
{
public:
    MusicPlayerModel();

    MusicPlayerModel(MusicPlayerController* mpc);

    /*
     *初始化需要的变量
     */
    void init();


    /*
     *要初始化的变量
     */
    MainWindowController* _mainWindowCtrl;
    MainWindow* _mainWindow;

    MusicPlayerController *_musicPlayerCtrl;

    PlayFuncController* _pfc;
    PlayFuncView *_pfView;
    PlayFuncModel* _pfModel;

    LocalMusicController* _localMusicCtrl;
    LocalMusicModel* _localMusicModel;
    LocalMusicView* _localMusicView;


    DownLoadController* _downloadCtrl;
    DownLoadModel* _downloadModel;
    DownLoadView* _downloadView;










    PlayFuncView *pfView() const;
    void setPfView(PlayFuncView *pfView);
    LocalMusicView *localMusicView() const;
    LocalMusicController *localMusicCtrl() const;
    PlayFuncController *pfc() const;
    void setPfc(PlayFuncController *pfc);
    PlayFuncModel *pfModel() const;
    void setPfModel(PlayFuncModel *pfModel);
    DownLoadController *downloadCtrl() const;
    void setDownloadCtrl(DownLoadController *downloadCtrl);
    DownLoadModel *downloadModel() const;
    void setDownloadModel(DownLoadModel *downloadModel);
    DownLoadView *downloadView() const;
    void setDownloadView(DownLoadView *downloadView);

    MainWindowController *mainWindowCtrl() const;
    void setMainWindowCtrl(MainWindowController *mainWindowCtrl);

    MainWindow *mainWindow() const;
    void setMainWindow(MainWindow *mainWindow);
};

#endif // MUSICPLAYERMODEL_H

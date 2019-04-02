#include "musicplayercontroller.h"

MusicPlayerController::MusicPlayerController()
{
    this->init();
    cout<<"musicPlayerctrl"<<endl;
}

MusicPlayerController::MusicPlayerController(MainWindowController *mwc)
{

    this->init();
    //初始化主窗口的handle
    this->_musicPlayerModel->setMainWindowCtrl(mwc);
    this->_musicPlayerModel->setMainWindow(mwc->getMainWindow());
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

void MusicPlayerController::closeApp()
{
    //MainWindow* mw = this->_musicPlayerModel->mainWindowCtrl()->getMainWindow();
    qApp->exit(0);
}

void MusicPlayerController::minApp()
{
//    MainWindow* mw = this->_musicPlayerModel->mainWindow();
//    mw->showMinimized();
    //mw->setWindowState(Qt::WindowMinimized);

    this->_musicPlayerModel->mainWindowCtrl()->minApp();
}

void MusicPlayerController::maxApp()
{

//    MainWindow* mw = (MainWindow*)this->_musicPlayerModel->mainWindow();
//    int width = QApplication::desktop()->width();

//    int height = QApplication::desktop()->height() ;
//    mw->move(0,0);

//    mw->resize(width,height);
    //    cout<<"maxApp"<<endl;
//    mw->setWindowState(Qt::WindowMaximized);
    this->_musicPlayerModel->mainWindowCtrl()->maxApp();
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
        this->connectLocalMusicListAndPlayFunc();
        break;
    case DOWNLOAD_FILE_WINDOW:
        w= this->_musicPlayerModel->downloadView();
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

void MusicPlayerController::connectLocalMusicListAndPlayFunc()
{
    PlayFuncController* pfc = this->_musicPlayerModel->pfc();
    LocalMusicController* lmc = this->_musicPlayerModel->localMusicCtrl();
    QObject::connect(pfc,&PlayFuncController::preSignal,lmc,&LocalMusicController::setCurIndexOnMusicList);
    QObject::connect(pfc,&PlayFuncController::nextSignal,lmc,&LocalMusicController::setCurIndexOnMusicList);
}

void MusicPlayerController::disconnectLocalMusicListAndPlayFunc()
{
    PlayFuncController* pfc = this->_musicPlayerModel->pfc();
    LocalMusicController* lmc = this->_musicPlayerModel->localMusicCtrl();
    QObject::disconnect(pfc,&PlayFuncController::preSignal,lmc,&LocalMusicController::setCurIndexOnMusicList);
    QObject::disconnect(pfc,&PlayFuncController::nextSignal,lmc,&LocalMusicController::setCurIndexOnMusicList);
}

void MusicPlayerController::hiddenWidgetToDo(QWidget* w)
{
    if(w == this->_musicPlayerModel->localMusicView()){
        this->disconnectLocalMusicListAndPlayFunc();
    }else if(w == this->_musicPlayerModel->downloadView()){

    }

}

PlayFuncView *MusicPlayerController::getPlayFuncView() const
{
    return this->_musicPlayerModel->pfView();
}

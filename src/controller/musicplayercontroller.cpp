#include "musicplayercontroller.h"

PlayFuncController* MusicPlayerController::single_playfuncCtrl = nullptr;


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

PlayFuncController *MusicPlayerController::getSinglePlayFuncCtrl()
{
    return MusicPlayerController::single_playfuncCtrl;
}

MusicSheetDetialView *MusicPlayerController::getMusicSheetDetialView()
{
    return this->_musicPlayerModel->musicSheetDetialView();
}


MusicPlayerView *MusicPlayerController::musicPlayerView() const
{
    return _musicPlayerView;
}

void MusicPlayerController::setMusicPlayerView(MusicPlayerView *musicPlayerView)
{
    _musicPlayerView = musicPlayerView;
}

QList<MusicSheet> MusicPlayerController::getCollectSheet()
{
    return GlobalVariable::get_global_User().collectedMusicSheets();

}

QList<MusicSheet> MusicPlayerController::getCreatedSheet()
{
    return GlobalVariable::get_global_User().createdMusicSheets();
}

MusicPlayerView *MusicPlayerController::getMusicPlayerView() const
{
    return _musicPlayerView;
}


void MusicPlayerController::init()
{
    /*
     * 初始化环境变量
     */
    this->initEnv();


    /*
     * 初始化全局变量
     */

    _musicPlayerModel = new MusicPlayerModel(this);
    qDebug()<<"musicplayermodel 完毕";
    _musicPlayerView = new MusicPlayerView(this);
    this->init_view();
    qDebug()<<"初始化完毕";

}

void MusicPlayerController::initEnv()
{
    /*
     *初始化环境
     */
    QString appPath = QDir::currentPath();
    QDir curDir(appPath);
    QDir localDir(appPath +"/"+ CONST_GLOBAL_STRING_LOCAL_DIR);

    if(!localDir.exists()){
        curDir.mkdir(CONST_GLOBAL_STRING_LOCAL_DIR);
    }

    GlobalVariable::global_local_file_path = localDir.absolutePath();

    QDir downloadDir(appPath +"/" + CONST_GLOBAL_STRING_DOWNLOAD_DIR);
    if(!downloadDir.exists()){
        curDir.mkdir(CONST_GLOBAL_STRING_DOWNLOAD_DIR);
    }

    QDir userDir(appPath + "/" + CONST_GLOBAL_STRING_USER_DIR);

    if(!userDir.exists()){
        curDir.mkdir(CONST_GLOBAL_STRING_USER_DIR);
    }

    QDir settingDir(appPath + "/" + CONST_GLOBAL_STRING_SETTING_DIR);

    if(!settingDir.exists()){
        curDir.mkdir(CONST_GLOBAL_STRING_SETTING_DIR);
    }

    //先读取配置文件，然后在判断要做的事情
    QFile settingFile(settingDir.absolutePath()  + "/"+ CONST_GLOBAL_STRING_SETTING_FILE_NAME);
    QJsonObject settingObj =  FileFuncController::getJsonObjFromFile(settingFile);

    GlobalVariable::settingObj = settingObj;



    if(!settingObj.value("autologin").toBool(false)){
        //如果不自动登陆则解析本地用户
        QFile userFile(userDir.absolutePath()+ "/"+ CONST_GLOBAL_STRING_LOCAL_USER_FILE_NAME);
        QJsonObject localUserObj = FileFuncController::getJsonObjFromFile(userFile);

        GlobalVariable::global_User =  User::jsonObj2User(localUserObj);
        GlobalVariable::global_user_absolute_file = userDir.absoluteFilePath(CONST_GLOBAL_STRING_LOCAL_USER_FILE_NAME);
    }

    //解析userObj
    //如果没有登陆 则初始化本地用户
    if(!GlobalVariable::IsLogin()){
        qDebug()<<"未实现 login";
    }

}

void MusicPlayerController::init_view()
{
    User& user = GlobalVariable::get_global_User();

    this->updateCreatedMusicSheetView(user.createdMusicSheets());
    this->updateCollectedMusicSheetView(user.collectedMusicSheets());

}

void MusicPlayerController::closeApp()
{
    //MainWindow* mw = this->_musicPlayerModel->mainWindowCtrl()->getMainWindow();

    User& user = GlobalVariable::get_global_User();

    QFile userFile(GlobalVariable::global_user_absolute_file);
    FileFuncController::saveJsonObjToFile(user.toJsonObj(),GlobalVariable::global_user_absolute_file);

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

void MusicPlayerController::createMusicSheet(MusicSheet ms)
{
    User& user = GlobalVariable::get_global_User();
    user.addCreatedMusicSheet(ms);
    this->updateCreatedMusicSheetView(user.createdMusicSheets());

}

void MusicPlayerController::show()
{
    this->_musicPlayerView->show();
}

void MusicPlayerController::showMusicDetialView(PlayMusicDetialView *pmdv)
{
    this->_musicPlayerView->setMainWindowWidget(pmdv);
}

void MusicPlayerController::showMusicSheetDetialView(MusicSheet &musicSheet)
{
    MusicSheetDetialView* msd =  this->_musicPlayerModel->musicSheetDetialView();
    msd->updateView(musicSheet);
    this->_musicPlayerView->setMainWindowWidget(msd);
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

void MusicPlayerController::updateCreatedMusicSheetView(QList<MusicSheet> msList)
{
    this->_musicPlayerView->updateCreatedMusicSheet(msList);
}

void MusicPlayerController::updateCollectedMusicSheetView(QList<MusicSheet> msList)
{
    this->_musicPlayerView->updateCollectedMusicSheet(msList);
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

QPoint MusicPlayerController::getMusicPlayerViewPos()
{
    return this->_musicPlayerView->pos();

}

PlayFuncView *MusicPlayerController::getPlayFuncView() const
{
    return this->_musicPlayerModel->pfView();
}

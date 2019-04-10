#include "playfunccontroller.h"

PlayFuncController::PlayFuncController()
{
    this->init();
}

PlayFuncController::PlayFuncController(MusicPlayerController *mpc)
{
    this->init();
    this->_playFuncModel->setMusicPlayerCtrl(mpc);
}


PlayFuncView *PlayFuncController::playFuncView() const
{
    return _playFuncView;
}

void PlayFuncController::setPlayFuncView(PlayFuncView *playFuncView)
{
    _playFuncView = playFuncView;
}

PlayFuncModel *PlayFuncController::playFuncModel() const
{
    return _playFuncModel;
}

void PlayFuncController::setPlayFuncModel(PlayFuncModel *playFuncModel)
{
    _playFuncModel = playFuncModel;
}

void PlayFuncController::init()
{
    //先将模型初始化 ，初始化后已经有了playSheetContorller;
    //错误原因 切记不要重复初始化，导致controller不对应。
    this->_playFuncModel = new PlayFuncModel(this);

    //播放列表控制器
    //PlaySheetController* psc = new PlaySheetController(this);
    //this->_playFuncModel->setPlaySheetCtrl(psc);

    this->_playFuncView = new PlayFuncView(this);


    //播放详细界面控制器
    PlayMusicDetialController* pmdc = PlayMusicDetialController::newInstance(this);
    this->_playFuncModel->setPlayMusicDetialCtrl(pmdc);

}

void PlayFuncController::init_view()
{

}

MusicPlayerView *PlayFuncController::getMusicPlayerView()
{
    return this->_playFuncModel->getMusicPlayerView();
}

QPoint PlayFuncController::getMusicPlayerViewPos()
{
    return this->_playFuncModel->musicPlayerCtrl()->getMusicPlayerViewPos();
}

void PlayFuncController::show()
{

}

void PlayFuncController::showDetialMusicView()
{
    //让主控制器去显示详细音乐界面  此时应该把音乐界面传过去
    PlayMusicDetialView* pmdv = this->playFuncModel()->getPlayMusicDetialCtrl()->playMusicDetialView();
    this->_playFuncModel->musicPlayerCtrl()->showMusicDetialView(pmdv);
}

void PlayFuncController::play()
{
    QMediaPlayer* mp = this->playFuncModel()->mediaPlayer();
    if(mp->state() != QMediaPlayer::PlayingState){
        this->playFuncModel()->mediaPlayer()->play();
        this->playFuncView()->setPauseView();
    }

}

bool PlayFuncController::playOrPause()
{

    if(this->playFuncModel()->mediaPlayer()->currentMedia().isNull())
        return false;

    if(this->playFuncModel()->mediaPlayer()->state() == QMediaPlayer::PlayingState){
        //如果是播放状态，暂停播放
        this->playFuncModel()->mediaPlayer()->pause();
        this->playFuncView()->setStartView();

    }else if(this->playFuncModel()->mediaPlayer()->state() == QMediaPlayer::StoppedState
             || this->playFuncModel()->mediaPlayer()->state() == QMediaPlayer::PausedState){
        cout<<"play"<<endl;
        this->playFuncModel()->mediaPlayer()->play();
        this->playFuncView()->setPauseView();

    }
    return true;
}

bool PlayFuncController::next()
{
    QMediaPlaylist*  mpl = this->playFuncModel()->mediaPlayList();
    this->pause();
    //int cur  = this->_playFuncModel->mediaPlayList()->currentIndex();
    if(mpl->currentIndex() == mpl->mediaCount() -1 ){
        mpl->setCurrentIndex(0);
    }else{
        this->playFuncModel()->mediaPlayList()->next();
    }
    this->playOrPause();
    emit nextSignal(mpl->currentIndex());
    return true;
}

bool PlayFuncController::pre()
{
    QMediaPlaylist*  mpl = this->playFuncModel()->mediaPlayList();
    this->pause();
    if(mpl->currentIndex() == 0){
        mpl->setCurrentIndex(mpl->mediaCount() -1);

    }else{
        mpl->previous();
    }

    this->playOrPause();
    emit preSignal(mpl->currentIndex());
    return true;
}

bool PlayFuncController::pause()
{
    if(this->playFuncModel()->mediaPlayer()->state() == QMediaPlayer::PlayingState){
        //如果是播放状态，暂停播放
        this->playFuncModel()->mediaPlayer()->pause();
        this->playFuncView()->setStartView();
        return true;
    }
    return false;
}

void PlayFuncController::addMusicToCurMusicSheet(Music &music)
{
    this->_playFuncModel->addMusicToCurMusicSheet(music);
    //刷新界面
    this->_playFuncModel->playSheetCtrl()->updatePlaySheet(this->_playFuncModel->_curMusicSheet);

}

bool PlayFuncController::setCurrentMusicSheet(MusicSheet musicSheet)
{

    this->playFuncModel()->setCurMusicSheet(musicSheet);
    this->__setCurrentMusicList(this->playFuncModel()->curMusicSheet().musics());
    PlaySheetController* psc =  this->playFuncModel()->playSheetCtrl();
    //psc->updatePlaySheet(this->playFuncModel()->getCurMusicSheet());
    qDebug()<<"updateplaysheetView"<<endl;
    psc->updatePlaySheetView(this->playFuncModel()->getCurMusicSheet());

}

void PlayFuncController::updateRecentMusicSheet(Music music)
{

}

void PlayFuncController::setCurrentMusic(Music music)
{
    this->pause();
    if(!music.musicPath().isEmpty()){
        this->playFuncModel()->setMusic(music);
        this->playFuncModel()->mediaPlayer()->setMedia(QUrl::fromLocalFile(music.musicPath()));
    }

    //this->playFuncModel()->mediaPlayer()->play();

}

void PlayFuncController::setCurrentMusic(int index)
{

    this->pause();
    QMediaPlaylist*  mediaList=  this->_playFuncModel->mediaPlayList();

    if(index >=0 && index <this->_playFuncModel->mediaPlayList()->mediaCount()){
        mediaList->setCurrentIndex(index);
    }

    this->init_Music_View();

}

void PlayFuncController::init_Music_View()
{
    this->connectAllTime();
    this->connectCurTime();
    this->connectTimeSlider();
    this->connectVolumeSlider();
}

void PlayFuncController::__setCurrentMusicList(QList<Music> musics)
{
    if(musics.empty())
        return;
    this->playFuncModel()->setMusics(musics);

    QMediaPlaylist* qmpl = this->playFuncModel()->mediaPlayList();
    qmpl->clear();

    for(int i=0;i<musics.size();i++){
        qmpl->addMedia(QMediaContent(QUrl::fromLocalFile(musics.at(i).musicPath())));
    }
    //设置播放模式
    this->setMusicListMode(QMediaPlaylist::Sequential);

    this->_playFuncModel->mediaPlayer()->setPlaylist(qmpl);
    //qmpl->setMediaObject(this->playFuncModel()->mediaPlayer());
}

void PlayFuncController::playMusic(Music &music)
{
    this->pause();
    this->setCurrentMusic(music);
    this->playOrPause();

}

void PlayFuncController::playMusic(QModelIndex index)
{
    this->pause();
    this->setCurrentMusic(index.row());
    this->playOrPause();
}

void PlayFuncController::setMusicListMode(int mode)
{
    //未完成
    this->playFuncModel()->mediaPlayList()->setPlaybackMode(QMediaPlaylist::Sequential );
}

void PlayFuncController::connectCurTime()
{
    QMediaPlayer* mp = this->playFuncModel()->mediaPlayer();
    QObject::connect(mp,&QMediaPlayer::positionChanged,this->playFuncView(),&PlayFuncView::showCurPosition);
}

void PlayFuncController::connectTimeSlider()
{
    QMediaPlayer* mp = this->playFuncModel()->mediaPlayer();
    //1.将总时间连接到滑动条
    //2.将滑动条事件连接到数据播放器
    QSlider* timeSlider = this->playFuncView()->getTimeSlider();
    QObject::connect(mp,&QMediaPlayer::durationChanged,this->playFuncView(),&PlayFuncView::setTimeSLiderRange);

    //QObject::connect(timeSlider,&QSlider::valueChanged,mp,&QMediaPlayer::setPosition);

    QObject::connect(mp,&QMediaPlayer::positionChanged,this->playFuncView(),&PlayFuncView::setTimeSliderPosition);

    QObject::connect(this->_playFuncView,&PlayFuncView::customSliderMoved,mp,&QMediaPlayer::setPosition);
}

void PlayFuncController::connectVolumeSlider()
{

    QMediaPlayer* mp = this->playFuncModel()->mediaPlayer();
    this->_playFuncView->setVolume(mp->volume());
    QSlider* volumeSlider = this->playFuncView()->getVolumeSlider();
    QObject::connect(volumeSlider,&QSlider::valueChanged,mp,&QMediaPlayer::setVolume);
}

PlaySheetView *PlayFuncController::getPlaySheetView()
{
    return this->_playFuncModel->playSheetView();
}

void PlayFuncController::connectAllTime()
{
    QMediaPlayer* mp = this->playFuncModel()->mediaPlayer();

    QObject::connect(mp,&QMediaPlayer::durationChanged,this->playFuncView(),&PlayFuncView::showCurDuration);
}

#include "playfunccontroller.h"

PlayFuncController::PlayFuncController()
{
    this->init();
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
    this->_playFuncModel = new PlayFuncModel;
    this->_playFuncView = new PlayFuncView(this);
    Music m;
    setCurrentMusic(m);
}

void PlayFuncController::init_view()
{

}

void PlayFuncController::show()
{

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

void PlayFuncController::setCurrentMusicList(QVector<Music> vecMusic)
{
    if(vecMusic.empty())
        return;
    this->playFuncModel()->setVecMusic(vecMusic);

    QMediaPlaylist* qmpl = this->playFuncModel()->mediaPlayList();
    qmpl->clear();

    for(int i=0;i<vecMusic.size();i++){
        qmpl->addMedia(QMediaContent(QUrl::fromLocalFile(vecMusic.at(i).musicPath())));
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

    QObject::connect(timeSlider,&QSlider::valueChanged,mp,&QMediaPlayer::setPosition);

    QObject::connect(mp,&QMediaPlayer::positionChanged,this->playFuncView(),&PlayFuncView::setTimeSliderPosition);

}

void PlayFuncController::connectVolumeSlider()
{
    QMediaPlayer* mp = this->playFuncModel()->mediaPlayer();
    QSlider* volumeSlider = this->playFuncView()->getVolumeSlider();
    QObject::connect(volumeSlider,&QSlider::valueChanged,mp,&QMediaPlayer::setVolume);
}

void PlayFuncController::connectAllTime()
{
    QMediaPlayer* mp = this->playFuncModel()->mediaPlayer();

    QObject::connect(mp,&QMediaPlayer::durationChanged,this->playFuncView(),&PlayFuncView::showCurDuration);
}

#include "playfuncmodel.h"

PlayFuncModel::PlayFuncModel()
{
    this->init();
}

PlayFuncModel::PlayFuncModel(PlayFuncController *pfc)
{
    this->_pfc = pfc;
    this->init();

}

MusicSheet PlayFuncModel::getLastMusicSheet() const
{
    return _lastMusicSheet;
}

void PlayFuncModel::setLastMusicSheet(const MusicSheet &lastMusicSheet)
{
    _lastMusicSheet = lastMusicSheet;
}

PlayMusicDetialController *PlayFuncModel::getPlayMusicDetialCtrl() const
{
    return __playMusicDetialCtrl;
}

void PlayFuncModel::setPlayMusicDetialCtrl(PlayMusicDetialController *playMusicDetialCtrl)
{
    __playMusicDetialCtrl = playMusicDetialCtrl;
}

MusicSheet PlayFuncModel::getCurMusicSheet() const
{
    return _curMusicSheet;
}

MusicPlayerController *PlayFuncModel::musicPlayerCtrl() const
{
    return _musicPlayerCtrl;
}

void PlayFuncModel::setMusicPlayerCtrl(MusicPlayerController *musicPlayerCtrl)
{
    _musicPlayerCtrl = musicPlayerCtrl;
}

PlaySheetController *PlayFuncModel::playSheetCtrl() const
{
    return _playSheetCtrl;
}

void PlayFuncModel::setPlaySheetCtrl(PlaySheetController *playSheetCtrl)
{
    _playSheetCtrl = playSheetCtrl;
}

PlaySheetView *PlayFuncModel::playSheetView() const
{
    return _playSheetView;
}

void PlayFuncModel::setPlaySheetView(PlaySheetView *playSheetView)
{
    _playSheetView = playSheetView;
}



QList<Music> PlayFuncModel::musics() const
{
    return _musics;
}

void PlayFuncModel::setMusics(const QList<Music> &musics)
{
    _musics = musics;
}

MusicSheet PlayFuncModel::curMusicSheet() const
{
    return _curMusicSheet;
}

void PlayFuncModel::setCurMusicSheet(const MusicSheet &curMusicSheet)
{
    _curMusicSheet = curMusicSheet;
}



QMediaPlaylist *PlayFuncModel::mediaPlayList() const
{
    return _mediaPlayList;
}

void PlayFuncModel::setMediaPlayList(QMediaPlaylist *mediaPlayList)
{
    _mediaPlayList = mediaPlayList;
}

void PlayFuncModel::init()
{
    this->_mediaPlayer = new QMediaPlayer;
    this->_mediaPlayList = new QMediaPlaylist;
    this->_mediaPlayer->setPlaylist(this->_mediaPlayList);

    //播放列表的控制器
    _playSheetCtrl = new PlaySheetController(this->_pfc);
    this->_playSheetView = _playSheetCtrl->playSheetView();

    //音乐详细界面控制器
    //this->__playMusicDetialCtrl = PlayMusicDetialController::newInstance()

}

MusicPlayerView* PlayFuncModel::getMusicPlayerView()
{
    return this->_musicPlayerCtrl->getMusicPlayerView();

}

void PlayFuncModel::addMusicToCurMusicSheet(Music &music)
{
    this->_curMusicSheet.musics().append(music);
}

void PlayFuncModel::changeMediaPlaySheet(MusicSheet &musicSheet)
{

}

QMediaPlayer *PlayFuncModel::mediaPlayer() const
{
    return _mediaPlayer;
}

void PlayFuncModel::setMediaPlayer(QMediaPlayer *mediaPlayer)
{
    _mediaPlayer = mediaPlayer;
}

Music PlayFuncModel::music() const
{
    return _music;
}

void PlayFuncModel::setMusic(const Music& music)
{
    _music = music;
}

#include "playfuncmodel.h"

PlayFuncModel::PlayFuncModel()
{
    this->init();
}

QVector<Music> PlayFuncModel::vecMusic() const
{
    return _vecMusic;
}

void PlayFuncModel::setVecMusic(const QVector<Music> &vecMusic)
{
    _vecMusic = vecMusic;
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

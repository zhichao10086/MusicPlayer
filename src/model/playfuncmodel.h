#ifndef PLAYFUNCMODEL_H
#define PLAYFUNCMODEL_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "music.h"
#include <QVector>

class PlayFuncModel
{
public:
    PlayFuncModel();

    Music _music;
    QVector<Music> _vecMusic;

    QMediaPlayer* _mediaPlayer;
    QMediaPlaylist* _mediaPlayList;

    void init();

    void changeMediaPlayList();


    Music music() const;
    void setMusic(const Music &music);
    QMediaPlayer *mediaPlayer() const;
    void setMediaPlayer(QMediaPlayer *mediaPlayer);
    QMediaPlaylist *mediaPlayList() const;
    void setMediaPlayList(QMediaPlaylist *mediaPlayList);
    QVector<Music> vecMusic() const;
    void setVecMusic(const QVector<Music> &vecMusic);
};

#endif // PLAYFUNCMODEL_H

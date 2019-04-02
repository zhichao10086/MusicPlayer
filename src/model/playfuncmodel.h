#ifndef PLAYFUNCMODEL_H
#define PLAYFUNCMODEL_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "music.h"
#include <QVector>
#include "musicsheet.h"

class PlayFuncModel
{
public:
    PlayFuncModel();

    /*
     * 播放功能界面里应该记录一个播放列表  即当前的播放歌单
     */

    Music _music;
    QVector<Music> _vecMusic;
    MusicSheet _curMusicSheet;



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

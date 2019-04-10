#ifndef PLAYFUNCMODEL_H
#define PLAYFUNCMODEL_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "music.h"
#include <QList>
#include "musicsheet.h"
#include <QObject>
#include "playfunccontroller.h"

#include "playsheetcontroller.h"
#include "playsheetview.h"
#include "musicplayerview.h"
#include "musicplayercontroller.h"
#include "playmusicdetialcontroller.h"

class PlayFuncController;
class PlaySheetView;
class PlaySheetController;
class MusicPlayerController;
class MusicPlayerView;
class PlayMusicDetialController;

class PlayFuncModel
{
public:
    PlayFuncModel();

    PlayFuncModel(PlayFuncController* pfc);
    /*
     * 播放功能界面里应该记录一个播放列表  即当前的播放歌单
     */


    MusicPlayerController* _musicPlayerCtrl;

    PlayFuncController* _pfc;

    PlaySheetController* _playSheetCtrl;
    PlaySheetView* _playSheetView;


    //当前播放音乐
    Music _music;
    //音乐列表   //废弃使用
    QList<Music> _musics;
    //当前播放列表   暂用
    MusicSheet _curMusicSheet;
    //历史播放记录
    MusicSheet _lastMusicSheet;


    QMediaPlayer* _mediaPlayer;
    QMediaPlaylist* _mediaPlayList;


    /*
     * 初始化
     */
    void init();

    MusicPlayerView* getMusicPlayerView();


    /*
     * 添加歌曲至当前播放列表
     */
    void addMusicToCurMusicSheet(Music& music);

    //改变当前播放列表
    void changeMediaPlaySheet(MusicSheet& musicSheet);


    Music music() const;
    void setMusic(const Music &music);
    QMediaPlayer *mediaPlayer() const;
    void setMediaPlayer(QMediaPlayer *mediaPlayer);
    QMediaPlaylist *mediaPlayList() const;
    void setMediaPlayList(QMediaPlaylist *mediaPlayList);

    MusicSheet curMusicSheet() const;
    void setCurMusicSheet(const MusicSheet &curMusicSheet);
    QList<Music> musics() const;
    void setMusics(const QList<Music> &musics);




    PlaySheetView *playSheetView() const;
    void setPlaySheetView(PlaySheetView *playSheetView);

    PlaySheetController *playSheetCtrl() const;
    void setPlaySheetCtrl(PlaySheetController *playSheetCtrl);

    MusicPlayerController *musicPlayerCtrl() const;
    void setMusicPlayerCtrl(MusicPlayerController *musicPlayerCtrl);

    MusicSheet getCurMusicSheet() const;

    MusicSheet getLastMusicSheet() const;
    void setLastMusicSheet(const MusicSheet &lastMusicSheet);

    PlayMusicDetialController *getPlayMusicDetialCtrl() const;
    void setPlayMusicDetialCtrl(PlayMusicDetialController *playMusicDetialCtrl);

private:
    PlayMusicDetialController* __playMusicDetialCtrl;
};

#endif // PLAYFUNCMODEL_H

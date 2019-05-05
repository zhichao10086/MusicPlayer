#ifndef PLAYFUNCCONTROLLER_H
#define PLAYFUNCCONTROLLER_H


#include <playfuncmodel.h>
#include <playfuncview.h>
#include <QList>
#include <QMediaContent>
#include <iostream>
#include <QObject>
#include "musicsheet.h"
#include "playsheetview.h"
#include "musicplayercontroller.h"
#include "musicplayerview.h"
#include <QDebug>
#include <QModelIndex>
#include "playmusicdetialcontroller.h"

class PlayMusicDetialController;
class PlayFuncModel;
class PlayFuncView;
class MusicPlayerView;

using namespace std;

class PlaySheetView;
class MusicPlayerController;

class PlayFuncController:public QObject
{

    Q_OBJECT
public:

    static PlayFuncController* global_PlayFuncCtrl;

    PlayFuncController();
    PlayFuncController(MusicPlayerController* mpc);

    static PlayFuncController* newInstance();


    PlayFuncModel* _playFuncModel;
    PlayFuncView*  _playFuncView;

    void init();

    void init_view();

    MusicPlayerView* getMusicPlayerView();

    QPoint getMusicPlayerViewPos();

    QMediaPlayer *getMediaPlayer();




    //未用
    void show();



    /*
     * <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
     * 已下是播放功能函数
     */

    /*
     *播放
     */
    void play();


    /*
     * 播放歌曲
     */
    bool playOrPause();


    /*
     * 下一首
     */
    bool next();

    /*
     * 上一首
     */
    bool pre();

    /*
     * 暂停
     */
    bool pause();


    /*
     *只添加歌曲时，调用一次
     * 添加歌曲至当前列表
     */
    int addMusicToCurMusicSheet(Music music);


    /*
     *设置当前播放列表
     *
     */
    bool setCurrentMusicSheet(MusicSheet musicSheet);

    void updateRecentMusicSheet(Music music);

    /*
     * 当前播放歌曲
     */
    Music currentPlayMusic();


    /*
     *当前歌单
     *
     */
    MusicSheet currentMusicSheet();

    /*
     * playmusic播放当前歌曲的时候会调用setcurrentMusic
     *
     */

    /*
     * 设置当前歌曲
     */
    void setCurrentMusic(const Music& music);

    /*
     * 在当前播放列表设置当前歌曲
     */
    void setCurrentMusic(int index);

    /*
     * 准备一首歌的初始设置
     */
    void init_Music_View();

    /*
     * 播放歌曲
     */
    void playMusic(const Music& music);

    /*
     * 播放当前列表歌曲
     */
    void playMusic(int index);


    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //连接信号槽

    /*
     * 连接时间显示
     */
    void connectAllTime();

    /*
     * 连接当前时间显示
     */
    void connectCurTime();

    /*
     * 连接滑动条
     */
    void connectTimeSlider();

    /*
     * 连接音量
     */
    void connectVolumeSlider();


    /*
     *连接当前音乐与详细音乐界面刷新的事件
     */
    void connectCurMusicToDetialView();

    PlaySheetView *getPlaySheetView();

    PlayFuncModel *playFuncModel() const;
    void setPlayFuncModel(PlayFuncModel *playFuncModel);
    PlayFuncView *playFuncView() const;
    void setPlayFuncView(PlayFuncView *playFuncView);



signals:
    /*
     * 下一首
     */
    nextSignal(int);

    /*
     * 上一首
     */
    preSignal(int);

public slots:
    //显示详细播放音乐界面
    void showDetialMusicView();

    /*
     * 刷新详细播放音乐界面
     */
    void updateDetialMusicView();

    /*
     * 刷新详细页面的歌词
     */
    void updateDetialMusicLyricsView(qint64);

    /*
     * 添加当前音乐到最近播放列表
     */
    void addMusicToRecentPlaySheet(int index);

    /*
     * 设置歌词
     */
    void setLyricsInMusic();

    /*
     * 设置播放模式
     */
    void setMusicListMode(QMediaPlaylist::PlaybackMode mode);


    /*
     * 设置缩略图
     */

private:
    /*
     * 设置当前播放列表
     */
    void __setCurrentMusicList(QList<Music> musics);


};

#endif // PLAYFUNCCONTROLLER_H

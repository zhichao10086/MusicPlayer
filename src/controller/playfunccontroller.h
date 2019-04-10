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

    PlayFuncController();
    PlayFuncController(MusicPlayerController* mpc);


    PlayFuncModel* _playFuncModel;
    PlayFuncView*  _playFuncView;

    void init();

    void init_view();

    MusicPlayerView* getMusicPlayerView();

    QPoint getMusicPlayerViewPos();

    //未用
    void show();

    //显示详细播放音乐界面
    void showDetialMusicView();

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
    void addMusicToCurMusicSheet(Music& music);


    /*
     *设置当前播放列表
     *
     */
    bool setCurrentMusicSheet(MusicSheet musicSheet);

    void updateRecentMusicSheet(Music music);


    /*
     * 设置当前歌曲
     */
    void setCurrentMusic(Music music);

    /*
     * 根据播放列表设置当前歌曲
     */
    void setCurrentMusic(int index);

    /*
     * 准备一首歌的初始设置
     */
    void init_Music_View();

    /*
     * 播放歌曲
     */
    void playMusic(Music& music);

    /*
     * 播放当前列表歌曲
     */
    void playMusic(QModelIndex index);

    /*
     * 设置播放模式
     */
    void setMusicListMode(int mode);

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

private:
    /*
     * 设置当前播放列表
     */
    void __setCurrentMusicList(QList<Music> musics);

};

#endif // PLAYFUNCCONTROLLER_H

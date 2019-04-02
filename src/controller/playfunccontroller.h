#ifndef PLAYFUNCCONTROLLER_H
#define PLAYFUNCCONTROLLER_H


#include <playfuncmodel.h>
#include <playfuncview.h>
#include <QVector>
#include <QMediaContent>
#include <iostream>
#include <QObject>


class PlayFuncModel;
class PlayFuncView;

using namespace std;


class PlayFuncController:public QObject
{

    Q_OBJECT
public:


    PlayFuncController();


    PlayFuncModel* _playFuncModel;
    PlayFuncView*  _playFuncView;

    void init();

    void init_view();

    void show();

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
     * 设置当前播放列表
     */
    void setCurrentMusicList(QVector<Music> vecMusic);

    /*
     * 播放歌曲
     */
    void playMusic(Music& music);

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

};

#endif // PLAYFUNCCONTROLLER_H

#ifndef PLAYFUNCCONTROLLER_H
#define PLAYFUNCCONTROLLER_H


#include <playfuncmodel.h>
#include <playfuncview.h>
#include <QVector>
#include <QMediaContent>
#include <iostream>


class PlayFuncModel;
class PlayFuncView;

using namespace std;


class PlayFuncController
{
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
     * 设置当前播放列表
     */
    void setCurrentMusicList(QVector<Music> vecMusic);

    /*
     * 播放歌曲
     */
    void playMusic(Music& music);

    void setMusicListMode(int mode);


    PlayFuncModel *playFuncModel() const;
    void setPlayFuncModel(PlayFuncModel *playFuncModel);
    PlayFuncView *playFuncView() const;
    void setPlayFuncView(PlayFuncView *playFuncView);
};

#endif // PLAYFUNCCONTROLLER_H

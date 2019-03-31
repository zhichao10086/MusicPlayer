#ifndef LOCALMUSICCONTROLLER_H
#define LOCALMUSICCONTROLLER_H

#include "localmusicmodel.h"
#include "localmusicview.h"
#include <QVector>
#include <QUrl>
#include <iostream>
#include "music.h"
#include <QModelIndex>
#include "playfunccontroller.h"

class LocalMusicModel;
class LocalMusicView;
class PlayFuncController;


using namespace std;

class LocalMusicController
{
public:
    LocalMusicController();

    LocalMusicController(PlayFuncController* pfc);

    /*
     * 初始化
     */
    void init();

    /*
     *显示选择文件夹对话框
     */
    void showChooseDirsDialog();

    /*
     * 搜索本地音乐从给定文件夹
     */
    QVector<Music> searchMusics(QStringList paths);


    Music getMusic(int index);

    /*
     * 播放音乐
     *
     */
    void playMusic(const QModelIndex& index);


    /*
     * 添加歌曲至播放器  //在此之前必须先searchMusics 保证
     * model中有数据
     */
    void addMusicsToMedia();


    LocalMusicModel* _localMusicModel;
    LocalMusicView* _localMusicView;

    LocalMusicModel *localMusicModel() const;
    void setLocalMusicModel(LocalMusicModel *localMusicModel);
    LocalMusicView *localMusicView() const;
    void setLocalMusicView(LocalMusicView *localMusicView);
};

#endif // LOCALMUSICCONTROLLER_H

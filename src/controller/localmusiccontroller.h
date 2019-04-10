#ifndef LOCALMUSICCONTROLLER_H
#define LOCALMUSICCONTROLLER_H

#include "localmusicmodel.h"
#include "localmusicview.h"
#include <QList>
#include <QUrl>
#include <iostream>
#include "music.h"
#include <QModelIndex>
#include "playfunccontroller.h"

class LocalMusicModel;
class LocalMusicView;
class PlayFuncController;


using namespace std;

class LocalMusicController:public QObject

{
    Q_OBJECT
public:
    LocalMusicController();

    LocalMusicController(PlayFuncController* pfc);


    void init();

    /*
     * 初始化
     */
    void init(PlayFuncController *pfc);

    /*
     *显示选择文件夹对话框
     */
    void showChooseDirsDialog();

    /*
     * 搜索本地音乐从给定文件夹
     */
    QList<Music> searchMusics(QStringList paths);


    Music getMusic(int index);

    /*
     * 播放音乐
     *
     */
    void playMusic(const QModelIndex& index);



    /*
     *添加歌曲至当前歌单
     */
    void addMusicToCurSheet(const QModelIndex& index);

    /*
     * 添加歌曲至播放器  //在此之前必须先searchMusics 保证
     * model中有数据
     */
    void addMusicsToMedia();

    /*
     *
     * 添加歌单至播放器
     */
    void addSheetToMedia();


    LocalMusicModel* _localMusicModel;
    LocalMusicView* _localMusicView;

    LocalMusicModel *localMusicModel() const;
    void setLocalMusicModel(LocalMusicModel *localMusicModel);
    LocalMusicView *localMusicView() const;
    void setLocalMusicView(LocalMusicView *localMusicView);

public slots:
    /*
     * 将选中状态放置在当前播放歌曲所在的行
     *
     */
    void setCurIndexOnMusicList(int);
};

#endif // LOCALMUSICCONTROLLER_H

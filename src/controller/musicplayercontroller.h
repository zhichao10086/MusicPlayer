#ifndef MUSICPLAYERCONTROLLER_H
#define MUSICPLAYERCONTROLLER_H

#include <QObject>
#include "musicplayermodel.h"
#include <musicplayerview.h>
#include "playfunccontroller.h"
#include "playfuncview.h"
#include "localmusicview.h"
#include <QWidget>
#include <iostream>
#include "mainwindowcontroller.h"
#include "mainwindow.h"
#include <QApplication>
#include <QMainWindow>
#include <QDesktopWidget>
#include "playmusicdetialview.h"
#include "globalvariable.h"
#include "filefunccontroller.h"
#include <QDir>
#include <QFile>
#include "filefunccontroller.h"
#include "user.h"
#include "globalconstant.h"
#include "musicsheetdetialcontroller.h"
#include "musicsheetdetialview.h"



using namespace std;

class MusicPlayerModel;
class MusicPlayerView;
class MainWindowController;
class PlayMusicDetialView;
class MusicSheetDetialView;



class MusicPlayerController
{
public:



    MusicPlayerController();

    MusicPlayerController(MainWindowController* mwc);

    enum{
        LOCAL_FILE_WINDOW = 1,
        DOWNLOAD_FILE_WINDOW = 2
    };


    /*
     * 全局单例
     * <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
     *
     *
     */

    static PlayFuncController* single_playfuncCtrl;

    static PlayFuncController* getSinglePlayFuncCtrl();

    /*
     * 获取歌单列表界面
     *
     */
    MusicSheetDetialView* getMusicSheetDetialView();

    /*
     * 获取播放控制的界面
     */
    PlayFuncView* getPlayFuncView() const;

    MusicPlayerView* musicPlayerView() const;
    void setMusicPlayerView(MusicPlayerView *musicPlayerView);

    MusicPlayerModel* _musicPlayerModel;
    MusicPlayerView* _musicPlayerView;

    /*
     * 获取数据区域
     * <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
     */
    QList<MusicSheet> getCollectSheet();


    QList<MusicSheet> getCreatedSheet();




    //初始化controller
    void init();

    /*
     * 初始化环境
     */
    void initEnv();

    //初始化界面
    void init_view();

    /*
     * 关闭程序
     */
    void closeApp();

    /*
     * 最小化
     */
    void minApp();

    /*
     * 最大化
     */
    void maxApp();


    /*
     *新建歌单
     */
    void createMusicSheet(MusicSheet ms);


    void show();

    /*
     * 显示正在播放详情页
     */
    void showMusicDetialView(PlayMusicDetialView* pmdv);


    /*
     *显示歌单详情页
     */
    void showMusicSheetDetiaView(int index);

    /*
     * 显示歌单详情页
     */
    void showMusicSheetDetialView(MusicSheet& musicSheet);

    /*
     * 设置主窗口界面
     */
    void setMainWindowWidget(int mode);

    /*
     *移除当前widget
     */
    void removeMainWindowWidget(int mode);

    /*
     * 获得本地音乐的界面
     */
    LocalMusicView* getLocalMusicView();


    /*
     * 更新自己创建的音乐歌单
     */
    void updateCreatedMusicSheetView(QList<MusicSheet> msList);

    /*
     * 更新收藏的音乐歌单
     */
    void updateCollectedMusicSheetView(QList<MusicSheet> msList);


    /*
     * 将本地音乐的list控件和音乐控制联系起来
     */
    void connectLocalMusicListAndPlayFunc();

    /*
     * 取消将本地音乐的list控件和音乐控制联系
     */
    void disconnectLocalMusicListAndPlayFunc();

    void hiddenWidgetToDo(QWidget* );


    //窗口坐标
    QPoint getMusicPlayerViewPos();


    MusicPlayerView *getMusicPlayerView() const;
};

#endif // MUSICPLAYERCONTROLLER_H

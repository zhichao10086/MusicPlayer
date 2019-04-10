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


using namespace std;

class MusicPlayerModel;
class MusicPlayerView;
class MainWindowController;
class PlayMusicDetialView;



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
     * 获取播放控制的界面
     */
    PlayFuncView* getPlayFuncView() const;

    MusicPlayerView* musicPlayerView() const;
    void setMusicPlayerView(MusicPlayerView *musicPlayerView);

    MusicPlayerModel* _musicPlayerModel;
    MusicPlayerView* _musicPlayerView;


    //初始化controller
    void init();

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

    void show();


    void showMusicDetialView(PlayMusicDetialView* pmdv);


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

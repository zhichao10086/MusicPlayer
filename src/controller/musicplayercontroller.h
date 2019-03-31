#ifndef MUSICPLAYERCONTROLLER_H
#define MUSICPLAYERCONTROLLER_H

#include "musicplayermodel.h"
#include <musicplayerview.h>
#include "playfunccontroller.h"
#include "playfuncview.h"
#include "localmusicview.h"
#include <QWidget>


class MusicPlayerModel;
class MusicPlayerView;



class MusicPlayerController
{
public:

    enum{
        LOCAL_FILE_WINDOW = 1,
        DOWNLOAD_FILE_WINDOW = 2
    };


    MusicPlayerController();


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


    void show();

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


};

#endif // MUSICPLAYERCONTROLLER_H

#ifndef PLAYFUNCVIEW_H
#define PLAYFUNCVIEW_H

#include <QWidget>
#include <playfunccontroller.h>
#include <QLabel>
#include <QSlider>
#include "util.h"
#include <QDebug>
#include <QMouseEvent>
#include <QPoint>
#include <QDesktopWidget>
#include <qmenubutton.h>
#include <QMenu>
#include <QAction>

class PlayFuncController;

namespace Ui {
class PlayFuncView;
}

class PlayFuncView : public QWidget
{
    Q_OBJECT

public:
    explicit PlayFuncView(QWidget *parent = 0);

    PlayFuncView(PlayFuncController* pfc, QWidget *parent = 0);

    ~PlayFuncView();

    PlayFuncController* _playFuncController;

    //重写
    bool eventFilter(QObject *watched, QEvent *event);

    //初始化数据
    void init();

    void init_view();

    //设置开始图案
    void setStartView();

    //设置停止图案
    void setPauseView();

    //设置背景图片
    void setBackgroundImage(QPixmap& p);

    //设置音量滑动条
    void setVolume(int);

    QLabel* getLabelTime();

    QSlider* getTimeSlider();

    QSlider* getVolumeSlider();


    //连接进度与滑动条
    void connectTimeAndSlider(QMediaPlayer* mp);

Q_SIGNALS:
    //自定义滑动条拖动事件
    void customSliderMoved(qint64);

public slots:
    void showCurDuration(qint64 );
    void showCurPosition(qint64);
    void setTimeSLiderRange(qint64);
    void setTimeSliderPosition(qint64);




private slots:
    //播放或暂停
    void on_btnStartOrPause_clicked();

    //下一首
    void on_btnNext_clicked();

    //上一首按钮点击
    void on_btnPre_clicked();

    //播放列表
    void on_btnPlaySheet_clicked();




    void on_btnMusicDetial_clicked();

    void on_btnPlayMode_clicked();

private:
    Ui::PlayFuncView *ui;

    bool isPlaySheetViewShow = false;
};

#endif // PLAYFUNCVIEW_H

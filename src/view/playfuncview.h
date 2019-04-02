#ifndef PLAYFUNCVIEW_H
#define PLAYFUNCVIEW_H

#include <QWidget>
#include <playfunccontroller.h>
#include <QLabel>
#include <QSlider>
#include "util.h"

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

    void init();

    void init_view();

    void setStartView();

    void setPauseView();

    void setBackgroundImage(QPixmap& p);




    QLabel* getLabelTime();

    QSlider* getTimeSlider();

    QSlider* getVolumeSlider();


    void connectTimeAndSlider(QMediaPlayer* mp);

public slots:
    void showCurDuration(qint64 );
    void showCurPosition(qint64);
    void setTimeSLiderRange(qint64);
    void setTimeSliderPosition(qint64);

private slots:
    void on_btnStartOrPause_clicked();

    void on_btnNext_clicked();

    void on_btnPre_clicked();

private:
    Ui::PlayFuncView *ui;
};

#endif // PLAYFUNCVIEW_H

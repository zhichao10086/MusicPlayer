#ifndef PLAYMUSICDETIALVIEW_H
#define PLAYMUSICDETIALVIEW_H

#include <QWidget>
#include "playmusicdetialcontroller.h"
#include <QPixmap>
#include "lyrics.h"
#include <QIcon>

class PlayMusicDetialController;

namespace Ui {
class PlayMusicDetialView;
}

class PlayMusicDetialView : public QWidget
{
    Q_OBJECT

public:
    explicit PlayMusicDetialView(QWidget *parent = 0);
    PlayMusicDetialView(PlayMusicDetialController* pmdc, QWidget *parent = 0);
    ~PlayMusicDetialView();


    void updateView(Music music);

    // QObject interface
    bool event(QEvent *event);

private:
    Ui::PlayMusicDetialView *ui;
    PlayMusicDetialController* __playMusicDetialCtrl;


    void __initView();


    Music __music;

public slots:
    void updateLyrics(qint64 position);

private slots:
    void on_btnMin_clicked();
};

#endif // PLAYMUSICDETIALVIEW_H

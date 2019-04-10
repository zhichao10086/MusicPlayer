#ifndef PLAYMUSICDETIALVIEW_H
#define PLAYMUSICDETIALVIEW_H

#include <QWidget>
#include "playmusicdetialcontroller.h"

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

private:
    Ui::PlayMusicDetialView *ui;
    PlayMusicDetialController* __playMusicDetialCtrl;


    void __initView();
};

#endif // PLAYMUSICDETIALVIEW_H

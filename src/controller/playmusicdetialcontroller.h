#ifndef PLAYMUSICDETIALCONTROLLER_H
#define PLAYMUSICDETIALCONTROLLER_H

#include <QObject>
#include "globalvariable.h"
#include "playfunccontroller.h"
#include "playmusicdetialmodel.h"
#include "playmusicdetialview.h"

class PlayFuncController;
class PlayMusicDetialModel;
class PlayMusicDetialView;


class PlayMusicDetialController : public QObject
{
    Q_OBJECT
public:
    static PlayMusicDetialController* Global_playMusicDetialCtrl ;
    explicit PlayMusicDetialController(QObject *parent = nullptr);
    static PlayMusicDetialController* newInstance(PlayFuncController* pfc, QObject *parent = nullptr);

    PlayMusicDetialController(PlayFuncController* pfc, QObject *parent = nullptr);




    PlayMusicDetialView *playMusicDetialView() const;
    //void setPlayMusicDetialView(PlayMusicDetialView *playMusicDetialView);

private:

    void __init(PlayFuncController *pfc);

    PlayMusicDetialView* __playMusicDetialView;
    PlayMusicDetialModel* __playMusicDetialModel;

signals:

public slots:
};



#endif // PLAYMUSICDETIALCONTROLLER_H

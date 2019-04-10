#ifndef PLAYMUSICDETIALMODEL_H
#define PLAYMUSICDETIALMODEL_H

#include <QObject>
#include "playfunccontroller.h"
#include "playmusicdetialcontroller.h"

class PlayMusicDetialController;
class PlayFuncController;

class PlayMusicDetialModel : public QObject
{
    Q_OBJECT
public:
    explicit PlayMusicDetialModel(QObject *parent = nullptr);
    PlayMusicDetialModel(PlayFuncController* pfc, QObject *parent = nullptr);

    PlayFuncController *playFuncCtrl() const;
    void setPlayFuncCtrl(PlayFuncController *playFuncCtrl);

signals:

public slots:

private:

    PlayFuncController* __playFuncCtrl;

    void __init(PlayFuncController* pfc);
};

#endif // PLAYMUSICDETIALMODEL_H

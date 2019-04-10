#include "playmusicdetialmodel.h"

PlayMusicDetialModel::PlayMusicDetialModel(QObject *parent) : QObject(parent)
{

}

PlayMusicDetialModel::PlayMusicDetialModel(PlayFuncController *pfc, QObject *parent): QObject(parent)
{
    this->__init(pfc);
}

PlayFuncController *PlayMusicDetialModel::playFuncCtrl() const
{
    return __playFuncCtrl;
}

void PlayMusicDetialModel::setPlayFuncCtrl(PlayFuncController *playFuncCtrl)
{
    __playFuncCtrl = playFuncCtrl;
}

void PlayMusicDetialModel::__init(PlayFuncController *pfc)
{
    this->__playFuncCtrl = pfc;
}

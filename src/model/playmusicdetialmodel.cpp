#include "playmusicdetialmodel.h"

PlayMusicDetialModel::PlayMusicDetialModel(QObject *parent) : QObject(parent)
{

}

PlayMusicDetialModel::PlayMusicDetialModel(PlayFuncController *pfc, QObject *parent): QObject(parent)
{
    this->__init(pfc);
}

Music PlayMusicDetialModel::getMusic() const
{
    return music;
}

void PlayMusicDetialModel::setMusic(const Music &value)
{
    music = value;
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

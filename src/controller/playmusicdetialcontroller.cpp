#include "playmusicdetialcontroller.h"

PlayMusicDetialController* PlayMusicDetialController::Global_playMusicDetialCtrl = nullptr;

PlayMusicDetialController::PlayMusicDetialController(QObject *parent) : QObject(parent)
{

}

PlayMusicDetialController *PlayMusicDetialController::newInstance(PlayFuncController *pfc, QObject *parent)
{
    /*
    if(GLOBAL_PlayMusicDetialCtrl != nullptr){
        return GLOBAL_PlayMusicDetialCtrl;

    }

    GLOBAL_PlayMusicDetialCtrl = new PlayMusicDetialController(pfc,parent);

    return GLOBAL_PlayMusicDetialCtrl;
    */
    if(Global_playMusicDetialCtrl != nullptr){
        return Global_playMusicDetialCtrl;
    }
    Global_playMusicDetialCtrl = new PlayMusicDetialController(pfc);

    return Global_playMusicDetialCtrl;


}

PlayMusicDetialController::PlayMusicDetialController(PlayFuncController *pfc, QObject *parent):QObject(parent)
{
    this->__init(pfc);
}

void PlayMusicDetialController::__init(PlayFuncController *pfc)
{
    this->__playMusicDetialModel = new PlayMusicDetialModel(pfc);
    this->__playMusicDetialView = new PlayMusicDetialView(this);
}

PlayMusicDetialView *PlayMusicDetialController::playMusicDetialView() const
{
    return __playMusicDetialView;
}


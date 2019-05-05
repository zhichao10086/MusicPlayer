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

void PlayMusicDetialController::connectPlayer()
{
    PlayFuncController* pfc =  this->getPlayMusicDetialModel()->playFuncCtrl();

    //播放的进度与歌词联系起来
    //QObject::connect()

}

void PlayMusicDetialController::disconnectPlayer()
{

}

PlayMusicDetialController::PlayMusicDetialController(PlayFuncController *pfc, QObject *parent):QObject(parent)
{
    this->__init(pfc);
}

Music PlayMusicDetialController::getCurPlayMusic()
{
    return this->__playMusicDetialModel->getMusic();
}

void PlayMusicDetialController::setCurPlayMusic(Music value)
{
    this->__playMusicDetialModel->setMusic(value);
}

void PlayMusicDetialController::updateView(Music music)
{
    if(this->__playMusicDetialModel->getMusic() == music){
        return;
    }
    this->__playMusicDetialModel->setMusic(music);

    this->__playMusicDetialView->updateView(music);
}

void PlayMusicDetialController::updateLyricsView(qint64 position)
{
    this->__playMusicDetialView->updateLyrics(position);
}



void PlayMusicDetialController::CreateDetialView(Music &value)
{

}

void PlayMusicDetialController::__init(PlayFuncController *pfc)
{
    //在这里新建了详细页面
    this->__playMusicDetialModel = new PlayMusicDetialModel(pfc);
    this->__playMusicDetialView = new PlayMusicDetialView(this);
    this->__playMusicDetialView->updateView(this->__playMusicDetialModel->getMusic());
}

PlayMusicDetialModel *PlayMusicDetialController::getPlayMusicDetialModel() const
{
    return __playMusicDetialModel;
}

PlayMusicDetialView *PlayMusicDetialController::playMusicDetialView() const
{
    return __playMusicDetialView;
}


#include "musicsheetdetialcontroller.h"

MusicSheetDetialController* MusicSheetDetialController:: single_musicSheetDetialCtrl = nullptr;

MusicSheetDetialController::MusicSheetDetialController(QObject *parent) : QObject(parent)
{
    this->init();
}

MusicSheetDetialController::MusicSheetDetialController(PlayFuncController *pfc, QObject *parent):QObject(parent)
{
    this->__playFuncCtrl = pfc;
    this->init();
}

MusicSheetDetialController *MusicSheetDetialController::newInstance()
{
    if(MusicSheetDetialController::single_musicSheetDetialCtrl != nullptr)
        return MusicSheetDetialController::single_musicSheetDetialCtrl;

    MusicSheetDetialController::single_musicSheetDetialCtrl = new MusicSheetDetialController(MusicPlayerController::getSinglePlayFuncCtrl());
    return MusicSheetDetialController:: single_musicSheetDetialCtrl;

}




void MusicSheetDetialController::init()
{
    this->__msdModel = new MusicSheetDetialModel(this);

    this->__msdView = new MusicSheetDetialView(this);
}

void MusicSheetDetialController::setMusicSheet(const MusicSheet &sheet)
{
    this->__msdModel->setMusicSheet(sheet);
}

void MusicSheetDetialController::updateLocalImageUrl(QString url)
{
    this->__msdModel->updateLocalImageUrl(url);
}

void MusicSheetDetialController::updateMusicSheetView(MusicSheet &sheet)
{
    if(sheet == this->__msdModel->musicSheet()){
        return;
    }

    this->__msdView->updateView(sheet);
}

MusicSheetDetialModel *MusicSheetDetialController::msdModel() const
{
    return __msdModel;
}

void MusicSheetDetialController::setMsdModel(MusicSheetDetialModel *msdModel)
{
    __msdModel = msdModel;
}

MusicSheetDetialView *MusicSheetDetialController::msdView() const
{
    return __msdView;
}

void MusicSheetDetialController::setMsdView(MusicSheetDetialView *msdView)
{
    __msdView = msdView;
}



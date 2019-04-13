#include "playsheetcontroller.h"

PlaySheetController::PlaySheetController(QObject *parent) : QObject(parent)
{

}

PlaySheetController::PlaySheetController(PlayFuncController *pfc, QObject *parent)
    : QObject(parent)
{
    this->init(pfc);
}

void PlaySheetController::init(PlayFuncController *pfc)
{
    this->_pfCtrl = pfc;
    this->_playSheetModel = new PlaySheetModel(pfc);

    this->_playSheetView = new PlaySheetView(this);
    this->updateView();

}

void PlaySheetController::playMusic(QModelIndex index)
{
    //Music music = this->_playSheetModel->curMusicSheet().musics().at(index.row());
    this->_pfCtrl->playMusic(index.row());
}

void PlaySheetController::updateView()
{

    const MusicSheet& ms = this->playSheetModel()->curMusicSheet();
    this->updatePlaySheetView(ms);
    const MusicSheet& rms = this->playSheetModel()->recentMusicSheet();
    this->updateRecentPlaySheetView(rms);
}

void PlaySheetController::updatePlaySheet(const MusicSheet &musicSheet)
{
    this->playSheetModel()->setCurMusicSheet(musicSheet);
}

void PlaySheetController::updateRecentPlaySheet(const MusicSheet &musicSheet)
{
    this->playSheetModel()->setRecentMusicSheet(musicSheet);
}

void PlaySheetController::updatePlaySheetView(const MusicSheet &musicSheet)
{
    this->playSheetView()->updateListWidgetPlaySheet(musicSheet);
}

void PlaySheetController::updateRecentPlaySheetView(const MusicSheet &musicSheet)
{
    this->playSheetView()->updateListWidgetRecentPlaySheet(musicSheet);
}

const MusicSheet& PlaySheetController::getPlaySheet()
{
    const MusicSheet& ms = this->playSheetModel()->curMusicSheet();
    return ms;
}

PlaySheetModel *PlaySheetController::playSheetModel() const
{
    return _playSheetModel;
}

void PlaySheetController::setPlaySheetModel(PlaySheetModel *playSheetModel)
{
    _playSheetModel = playSheetModel;
}

PlaySheetView *PlaySheetController::playSheetView() const
{
    return _playSheetView;
}

void PlaySheetController::setPlaySheetView(PlaySheetView *playSheetView)
{
    _playSheetView = playSheetView;
}

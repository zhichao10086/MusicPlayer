#include "playsheetmodel.h"

PlaySheetModel::PlaySheetModel(QObject *parent) : QObject(parent)
{

}

PlaySheetModel::PlaySheetModel(PlayFuncController *pfc, QObject *parent): QObject(parent)
{
    this->__pfCtrl = pfc;
}

void PlaySheetModel::init()
{

}

MusicSheet PlaySheetModel::recentMusicSheet() const
{
    return __recentMusicSheet;
}

void PlaySheetModel::setRecentMusicSheet(const MusicSheet &recentMusicSheet)
{
    __recentMusicSheet = recentMusicSheet;
}

MusicSheet PlaySheetModel::curMusicSheet() const
{
    return __curMusicSheet;
}

void PlaySheetModel::setCurMusicSheet(const MusicSheet &curMusicSheet)
{
    __curMusicSheet = curMusicSheet;
}

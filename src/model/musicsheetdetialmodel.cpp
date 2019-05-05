#include "musicsheetdetialmodel.h"

MusicSheetDetialModel::MusicSheetDetialModel(QObject *parent) : QObject(parent)
{

}

MusicSheetDetialModel::MusicSheetDetialModel(MusicSheetDetialController *msdCtrl, QObject *parent)
{
    this->__msdCtrl = msdCtrl;
}

MusicSheetDetialController *MusicSheetDetialModel::msdCtrl() const
{
    return __msdCtrl;
}

void MusicSheetDetialModel::setMsdCtrl(MusicSheetDetialController *msdCtrl)
{
    __msdCtrl = msdCtrl;
}

void MusicSheetDetialModel::updateLocalImageUrl(QString url)
{
    this->__musicSheet.setLocalSheetImageUrl(url);
}

MusicSheet MusicSheetDetialModel::musicSheet() const
{
    return __musicSheet;
}

void MusicSheetDetialModel::setMusicSheet(const MusicSheet &musicSheet)
{
    __musicSheet = musicSheet;
}


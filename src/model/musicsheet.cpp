#include "musicsheet.h"



MusicSheet::MusicSheet()
{

}



QString MusicSheet::sheetName() const
{
    return _sheetName;
}

void MusicSheet::setSheetName(const QString &sheetName)
{
    _sheetName = sheetName;
}

QList<Music> MusicSheet::musics() const
{
    return _musics;
}

void MusicSheet::setMusics(const QList<Music> &musics)
{
    _musics = musics;
}

QString MusicSheet::createTime() const
{
    return _createTime;
}

void MusicSheet::setCreateTime(const QString &createTime)
{
    _createTime = createTime;
}

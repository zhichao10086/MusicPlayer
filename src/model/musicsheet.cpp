#include "musicsheet.h"

MusicSheet::MusicSheet()
{

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

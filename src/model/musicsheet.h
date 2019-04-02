#ifndef MUSICSHEET_H
#define MUSICSHEET_H

#include <QObject>
#include <QList>
#include "music.h"

class MusicSheet
{
public:
    MusicSheet();

    //创建时间
    QString _createTime;

    //歌曲列表
    QList<Music> _musics;

    QString createTime() const;
    void setCreateTime(const QString &createTime);
    QList<Music> musics() const;
    void setMusics(const QList<Music> &musics);
};

#endif // MUSICSHEET_H

#ifndef MUSICSHEET_H
#define MUSICSHEET_H


#include <QList>
#include "music.h"

class MusicSheet
{


public:


    MusicSheet();

    //名称
    QString _sheetName;

    //创建时间
    QString _createTime;

    //歌曲列表
    QList<Music> _musics;

    QString createTime() const;
    void setCreateTime(const QString &createTime);
    QList<Music> musics() const;
    void setMusics(const QList<Music> &musics);
    QString sheetName() const;
    void setSheetName(const QString &sheetName);


};

Q_DECLARE_METATYPE(MusicSheet)
#endif // MUSICSHEET_H

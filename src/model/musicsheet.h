#ifndef MUSICSHEET_H
#define MUSICSHEET_H


#include <QList>
#include "music.h"
#include <QJsonArray>
#include <QJsonObject>

class MusicSheet
{


public:


    MusicSheet();


    static MusicSheet fromJsonObj2MusicSheet(QJsonObject& obj);


    QJsonObject toJsonObj() const;



    int addMusic(const Music& music);


    void removeMusic(int index);

    void insertMusic(int index,Music music);

    //名称
    QString _sheetName;

    //创建时间
    QString _createTime;

    //歌曲列表
    QList<Music> _musics;

    QString createTime() const;
    void setCreateTime(const QString createTime);
    QList<Music> musics() const;
    void setMusics(const QList<Music> musics);
    QString sheetName() const;
    void setSheetName(const QString sheetName);


};

Q_DECLARE_METATYPE(MusicSheet)
#endif // MUSICSHEET_H

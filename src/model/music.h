#ifndef MUSIC_H
#define MUSIC_H

#include <QString>
#include <QFile>
#include <QUrl>


class Music
{
public:
    Music();

    Music(QString path);

    Music(QString name,QString singer,QString time);


    //歌名
    QString _musicName;
    //歌手
    QString _singer;
    //时间
    QString _time;
    //歌路径
    QString _musicPath;


    QString musicName() const;
    void setMusicName(const QString &musicName);

    QString musicPath() const;
    void setMusicPath(const QString &musicPath);
};

#endif // MUSIC_H

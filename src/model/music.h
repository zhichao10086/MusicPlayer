#ifndef MUSIC_H
#define MUSIC_H

#include <QString>
#include <QFile>
#include <QUrl>
#include <QMediaContent>
#include <QMediaObject>
#include <QMediaMetaData>
#include <QMediaPlayer>
#include <QObject>

class Music
{

public:
    Music();


    Music(QString path);

    Music(QString name,QString singer,QString time);


    void init();

    //歌名
    QString _musicName;
    //歌手
    QString _singer;
    //时间
    QString _time;

    //专辑
    QString _album;

    //歌路径
    QString _musicPath;

    //网络路径
    QString _musicNetPath;

    double _musicHot;

    int _fileSize;


    QString musicName() const;
    void setMusicName(const QString &musicName);

    QString musicPath() const;
    void setMusicPath(const QString &musicPath);
    QString time() const;
    void setTime(const QString &time);
    QString singer() const;
    void setSinger(const QString &singer);
    QString album() const;
    void setAlbum(const QString &album);
    double musicHot() const;
    void setMusicHot(double musicHot);
    int fileSize() const;
    void setFileSize(int fileSize);


};

Q_DECLARE_METATYPE(Music)
#endif // MUSIC_H

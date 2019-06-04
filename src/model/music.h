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
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>
#include <QImage>
#include <lyrics.h>
#include <QList>
#include "globalconstant.h"
#include <QUuid>
#include <QStringList>

class Music
{

public:
    Music();


    Music(QString path);

    static QStringList memberKeys;

    static Music fromJsonObj2Music(QJsonObject& obj);
    static QList<Music> fromJsonObj2Musics(QJsonArray& array);

    QJsonObject toJsonObj() const;

    void init();


    bool isEmpty();

    //相等
    bool operator==(const Music& a);

    QString _musicID;

    QString _title;

    QString _album;

    QString _artist;

    QString _publishDate;

    int _disc;
    int _track;

    QString _encoder;

    //时间
    QString _time;

    //歌本地路径
    QString _musicPath;

    //网络路径
    QString _musicNetPath;

    double _musicHot;

    int _fileSize;

    QString _musicLyrics;

    QList<QImage> _images;

    QString _imageUrl;

    QString _comment;

    QString _lyricsPath;

    Lyrics _lyrics;


    QString musicPath() const;
    void setMusicPath(const QString &musicPath);
    QString time() const;
    void setTime(const QString &time);

    double musicHot() const;
    void setMusicHot(double musicHot);
    int fileSize() const;
    void setFileSize(int fileSize);


    QString musicNetPath() const;
    void setMusicNetPath(const QString &musicNetPath);
    QString musicLyrics() const;
    void setMusicLyrics(const QString &musicLyrics);
    QString title() const;
    void setTitle(const QString &title);
    QString artist() const;
    void setArtist(const QString &artist);
    QString publishDate() const;
    void setPublishDate(const QString &publishDate);
    int disc() const;
    void setDisc(int disc);
    int track() const;
    void setTrack(int track);
    QString album() const;
    void setAlbum(const QString &album);
    QString imageUrl() const;
    void setImageUrl(const QString &imageUrl);
    QString encoder() const;
    void setEncoder(const QString &encoder);
    QString comment() const;
    void setComment(const QString &comment);

    QList<QImage> images() const;
    void setImages(const QList<QImage> &images);
    Lyrics lyrics() const;
    void setLyrics(const Lyrics &lyrics);
    QString lyricsPath() const;
    void setLyricsPath(const QString &lyricsPath);
    QString musicID() const;
    void setMusicID(const QString &musicID);
};



Q_DECLARE_METATYPE(Music)
#endif // MUSIC_H

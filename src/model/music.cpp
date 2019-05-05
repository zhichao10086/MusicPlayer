#include "music.h"

Music::Music()
{
    init();
}


Music::Music(QString path):
    _musicPath(path)
{
    init();
}


Music Music::fromJsonObj2Music(QJsonObject &obj)
{
    Music music;
    if(obj.empty())
        return music;
    music.setTitle(obj.value("title").toString());
    music.setAlbum(obj.value("album").toString());
    music.setFileSize(obj.value("fileSize").toInt());
    music.setMusicPath(obj.value("musicPath").toString());
    music.setMusicNetPath(obj.value("musicNetPath").toString());
    music.setArtist(obj.value("artist").toString());
    music.setTime(obj.value("time").toString());
    music.setMusicHot(obj.value("musicHot").toInt());


    return music;
}

QJsonObject Music::toJsonObj() const
{
    QJsonObject obj;
    obj.insert(QString("title"),this->title());
    obj.insert(QString("artist"),this->artist());
    obj.insert(QString("album"),this->album());
    obj.insert(QString("time"),this->time());
    obj.insert(QString("musicPath"),this->musicPath());
    obj.insert(QString("musicNetPath"),this->musicNetPath());
    obj.insert(QString("musicHot"),this->musicHot());
    obj.insert(QString("fileSize"),this->fileSize());


    return obj;
}


void Music::init()
{
    _fileSize = 0;
    _musicHot = 0;
}

bool Music::isEmpty()
{
    if(this->_title.isEmpty()){
        return true;
    }
    return false;
}

bool Music::operator==(const Music &a)
{
    if(a.musicPath() == this->musicPath()){
        return true;
    }
    return false;
}

QString Music::lyricsPath() const
{
    return _lyricsPath;
}

void Music::setLyricsPath(const QString &lyricsPath)
{
    _lyricsPath = lyricsPath;
}

Lyrics Music::lyrics() const
{
    return _lyrics;
}

void Music::setLyrics(const Lyrics &lyrics)
{
    _lyrics = lyrics;
}

QList<QImage> Music::images() const
{
    return _images;
}

void Music::setImages(const QList<QImage> &images)
{
    _images = images;
}


QString Music::comment() const
{
    return _comment;
}

void Music::setComment(const QString &comment)
{
    _comment = comment;
}

QString Music::encoder() const
{
    return _encoder;
}

void Music::setEncoder(const QString &encoder)
{
    _encoder = encoder;
}

QString Music::imageUrl() const
{
    return _imageUrl;
}

void Music::setImageUrl(const QString &imageUrl)
{
    _imageUrl = imageUrl;
}


int Music::track() const
{
    return _track;
}

void Music::setTrack(int track)
{
    _track = track;
}

int Music::disc() const
{
    return _disc;
}

void Music::setDisc(int disc)
{
    _disc = disc;
}

QString Music::publishDate() const
{
    return _publishDate;
}

void Music::setPublishDate(const QString &publishDate)
{
    _publishDate = publishDate;
}

QString Music::artist() const
{
    return _artist;
}

void Music::setArtist(const QString &artist)
{
    _artist = artist;
}

QString Music::title() const
{
    return _title;
}

void Music::setTitle(const QString &title)
{
    _title = title;
}



QString Music::musicLyrics() const
{
    return _musicLyrics;
}

void Music::setMusicLyrics(const QString &musicLyrics)
{
    _musicLyrics = musicLyrics;
}

QString Music::musicNetPath() const
{
    return _musicNetPath;
}

void Music::setMusicNetPath(const QString &musicNetPath)
{
    _musicNetPath = musicNetPath;
}

int Music::fileSize() const
{
    return _fileSize;
}

void Music::setFileSize(int fileSize)
{
    _fileSize = fileSize;
}

double Music::musicHot() const
{
    return _musicHot;
}

void Music::setMusicHot(double musicHot)
{
    _musicHot = musicHot;
}

QString Music::album() const
{
    return _album;
}

void Music::setAlbum(const QString &album)
{
    _album = album;
}


QString Music::time() const
{
    return _time;
}

void Music::setTime(const QString &time)
{
    _time = time;
}

QString Music::musicPath() const
{
    return _musicPath;
}

void Music::setMusicPath(const QString &musicPath)
{
    _musicPath = musicPath;
}


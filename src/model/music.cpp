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

Music::Music(QString name, QString singer, QString time):
    _musicName(name),_singer(singer),_time(time)
{
    init();
}

Music Music::fromJsonObj2Music(QJsonObject &obj)
{
    Music music;
    if(obj.empty())
        return music;
    music.setMusicName(obj.value("musicName").toString());
    music.setAlbum(obj.value("album").toString());
    music.setFileSize(obj.value("fileSize").toInt());
    music.setMusicPath(obj.value("musicPath").toString());
    music.setMusicNetPath(obj.value("musicNetPath").toString());
    music.setSinger(obj.value("singer").toString());
    music.setTime(obj.value("time").toString());
    music.setMusicHot(obj.value("musicHot").toInt());


    return music;
}

QJsonObject Music::toJsonObj() const
{
    QJsonObject obj;
    obj.insert(QString("musicName"),this->musicName());
    obj.insert(QString("singer"),this->singer());
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
    if(this->_musicName.isEmpty()){
        return true;
    }
}

bool Music::operator==(const Music &a)
{
    if(a.musicPath() == this->musicPath()){
        return true;
    }
    return false;
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

QString Music::singer() const
{
    return _singer;
}

void Music::setSinger(const QString &singer)
{
    _singer = singer;
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



QString Music::musicName() const
{
    return _musicName;
}

void Music::setMusicName(const QString &musicName)
{
    _musicName = musicName;
}

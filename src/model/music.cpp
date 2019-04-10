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

void Music::init()
{
    _fileSize = 0;
    _musicHot = 0;
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

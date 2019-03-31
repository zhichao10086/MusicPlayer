#include "music.h"

Music::Music()
{

}

Music::Music(QString path):
    _musicPath(path)
{

}

Music::Music(QString name, QString singer, QString time):
    _musicName(name),_singer(singer),_time(time)
{

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

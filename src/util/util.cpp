#include "util.h"

Util::Util()
{

}

QStringList Util::getFileNames(const QString &path)
{
    QDir dir(path);
    QStringList nameFilters;
    nameFilters << "*.mp3" << "*.wav"<<".ape"<<"flac"<<".ogg"<<".wv"<<".wma";
    QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);


    return files;

}

QStringList Util::getAbsoluteFileNames(const QString &path)
{
    cout<<path.toStdString()<<endl;
    QDir dir(path);
    QStringList nameFilters;
    nameFilters << "*.mp3" << "*.wav"<<".ape"<<"flac"<<".ogg"<<".wv"<<".wma";
    QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);

    for(int i=0;i<files.size();i++){
        files.replace(i,path + "/" + files.at(i) );

    }

    return files;
}

bool Util::hasDuplicate(QStringList &list, QString &s)
{

    for(int i=0;i<list.size();i++){
        if(s == list.at(i))
            return true;
    }
    return false;

}

QString Util::qint642QStringMinSec(qint64 playtime)
{
    int h,m,s;
    playtime /= 1000;  //获得的时间是以毫秒为单位的
    //h = playtime/3600;
    m = (playtime)/60;
    s = playtime-m*60;

    return QString("%1:%2").arg(m).arg(s);
}

QString Util::qint642QString(qint64 playtime)
{
    int h,m,s;
    playtime /= 1000;  //获得的时间是以毫秒为单位的
    h = playtime/3600;
    m = (playtime-h*3600)/60;
    s = playtime-h*3600-m*60;

    return QString("%1:%2:%3").arg(h).arg(m).arg(s);
}

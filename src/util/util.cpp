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

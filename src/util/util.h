#ifndef UTIL_H
#define UTIL_H

#include <QStringList>
#include <QDir>
#include <iostream>
#include <QTextCodec>

using namespace std;

class Util
{
public:
    Util();


    static QStringList getFileNames(const QString &path);

    static QStringList getAbsoluteFileNames(const QString &path);

    static bool hasDuplicate(QStringList& list,QString& s);

    static QString qint642QString(qint64);

    static QString qint642QStringMinSec(qint64);

    static QString GetCorrectUnicode(const QByteArray &ba);

    static bool time2double(QString time,double& ret);


};

#endif // UTIL_H

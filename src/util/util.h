#ifndef UTIL_H
#define UTIL_H

#include <QStringList>
#include <QDir>
#include <iostream>

using namespace std;

class Util
{
public:
    Util();


    static QStringList getFileNames(const QString &path);

    static QStringList getAbsoluteFileNames(const QString &path);

    static bool hasDuplicate(QStringList& list,QString& s);
};

#endif // UTIL_H

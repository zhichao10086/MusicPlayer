#ifndef USER_H
#define USER_H


#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QList>
#include "musicsheet.h"


class User
{

public:
    User();


    QString name() const;
    void setName(const QString &name);

    int age() const;
    void setAge(int age);

    QVariant createdMusicSheets() const;
    void setCreatedMusicSheets(const QVariant &createdMusicSheets);

    QVariant collectedMusicSheets() const;
    void setCollectedMusicSheets(const QVariant &collectedMusicSheets);

private:
    QString __name;
    int __age;

    //创建的歌单
    QVariant __createdMusicSheets;
    //收藏的歌单
    QVariant __collectedMusicSheets;






};

Q_DECLARE_METATYPE(User)

#endif // USER_H

#include "user.h"

User::User()
{

}

QString User::name() const
{
    return __name;
}

void User::setName(const QString &name)
{
    __name = name;
}

int User::age() const
{
    return __age;
}

void User::setAge(int age)
{
    __age = age;
}

QVariant User::createdMusicSheets() const
{
    return __createdMusicSheets;
}

void User::setCreatedMusicSheets(const QVariant &createdMusicSheets)
{
    __createdMusicSheets = createdMusicSheets;
}

QVariant User::collectedMusicSheets() const
{
    return __collectedMusicSheets;
}

void User::setCollectedMusicSheets(const QVariant &collectedMusicSheets)
{
    __collectedMusicSheets = collectedMusicSheets;
}

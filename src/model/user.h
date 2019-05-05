#ifndef USER_H
#define USER_H


#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QList>
#include "musicsheet.h"
#include <QDateTime>



class User
{

public:
    User();



    /*
     * json文件转换为user类
     */
    static User jsonObj2User(const QJsonObject& obj);

    /*
     * user类转为json
     */
    QJsonObject toJsonObj();


    QString name() const;
    void setName(const QString &name);


    int age() const;
    void setAge(int age);

    /*
     * 添加最近播放音乐
     */
    void addRecentPlayMusic(Music music);

    void addCreatedMusicSheet(MusicSheet musicSheet);


    QList<MusicSheet> createdMusicSheets() const;
    void setCreatedMusicSheets(const QList<MusicSheet> createdMusicSheets);

    QList<MusicSheet> collectedMusicSheets() const;
    void setCollectedMusicSheets(const QList<MusicSheet> collectedMusicSheets);


    MusicSheet playedMusicSheet() const;
    void setPlayedMusicSheet(const MusicSheet playedMusicSheet);

    QString getUserID() const;
    void setUserID(const QString &value);

private:
    QString __name;
    int __age;

    QString userID;

    //创建的歌单
    QList<MusicSheet> __createdMusicSheets;
    //收藏的歌单
    QList<MusicSheet> __collectedMusicSheets;
    //播放记录
    MusicSheet  __playedMusicSheet;


};

Q_DECLARE_METATYPE(User)

#endif // USER_H

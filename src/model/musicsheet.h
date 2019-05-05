#ifndef MUSICSHEET_H
#define MUSICSHEET_H


#include <QList>
#include "music.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QMap>
#include <QStringList>

class MusicSheet
{


public:


    MusicSheet();


    static MusicSheet fromJsonObj2MusicSheet(QJsonObject& obj);


    QJsonObject toJsonObj() const;

    //bool operator ==(MusicSheet& a);

    bool operator ==(MusicSheet a);

    //bool operator==(MusicSheet& a,MusicSheet& b);


    int addMusic(const Music& music);


    void removeMusic(int index);

    void insertMusic(int index,Music music);

    //名称
    QString _sheetName;

    //创建时间
    QString _createTime;

    //歌曲列表
    QList<Music> _musics;

    //播放数
    int _playCount;

    //收藏数
    int _collectCount;

    //本地图片路径
    QString _localSheetImageUrl;

    //网络图片路径
    QString _netSheetImageUrl;


    //介绍
    QString _introducement;


    //标签
    QStringList _tags;

    //用户
    QString _userID;

    //用户名称
    QString _userName;

    //用户头像
    QString _userHeadImageUrl;


    //未实现用户
    //User


    QString createTime() const;
    void setCreateTime(const QString createTime);
    QList<Music> musics() const;
    void setMusics(const QList<Music> musics);
    QString sheetName() const;
    void setSheetName(const QString sheetName);


    int playCount() const;
    void setPlayCount(int playCount);
    int collectCount() const;
    void setCollectCount(int collectCount);
    QString localSheetImageUrl() const;
    void setLocalSheetImageUrl(const QString &localSheetImageUrl);
    QString netSheetImageUrl() const;
    void setNetSheetImageUrl(const QString &netSheetImageUrl);
    QString userID() const;
    void setUserID(const QString &userID);
    QString userName() const;
    void setUserName(const QString &userName);
    QString introducement() const;
    void setIntroducement(const QString &introducement);
    QString userHeadImageUrl() const;
    void setUserHeadImageUrl(const QString &userHeadImageUrl);
};

Q_DECLARE_METATYPE(MusicSheet)
#endif // MUSICSHEET_H

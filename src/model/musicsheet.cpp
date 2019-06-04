#include "musicsheet.h"



MusicSheet::MusicSheet()
{
    this->_musicSheetID = QUuid::createUuid().toString();
    this->_collectCount = 0;
    this->_playCount = 0;
    this->_userID = "0";
    this->_userName = "本地用户";
}

MusicSheet MusicSheet::fromJsonObj2MusicSheet(QJsonObject &obj)
{
    MusicSheet ms;
    if(obj.empty())
        return ms;

    if(obj.contains("musicSheetID"))
        ms.setMusicSheetID(obj.value("musicSheetID").toString());
    if(obj.contains("createTime"))
        ms.setCreateTime(obj.value("createTime").toString());

    if(obj.contains("sheetName"))
        ms.setSheetName(obj.value("sheetName").toString());
    if(obj.contains("playCount"))
        ms.setPlayCount(obj.value("playCount").toInt());
    if(obj.contains("collectCount"))
        ms.setCollectCount(obj.value("collectCount").toInt());
    if(obj.contains("localImageUrl"))
        ms.setLocalSheetImageUrl(obj.value("localImageUrl").toString());
    if(obj.contains("netSheetImageUrl"))
        ms.setNetSheetImageUrl(obj.value("netSheetImageUrl").toString());

    QList<Music> musicList;

    //歌单中的音乐
    QJsonArray musicArray = obj.value("musics").toArray();

    for(int i=0;i<musicArray.size();i++){
        //变成musicobj
        QJsonObject msobj = musicArray.at(i).toObject();
        Music ms =  Music::fromJsonObj2Music(msobj);
        musicList.append(ms);
    }
    ms.setMusics(musicList);


    return ms;
}

QJsonObject MusicSheet::toJsonObj() const
{
    QJsonObject obj;
    obj.insert("musicSheetID",this->musicSheetID());
    obj.insert("sheetName",this->sheetName());
    obj.insert("createTime",this->createTime());
    obj.insert("playCount",this->playCount());
    obj.insert("collectCount",this->collectCount());
    obj.insert("localImageUrl",this->localSheetImageUrl());
    obj.insert("netSheetImageUrl",this->netSheetImageUrl());

    QJsonArray array;

    QList<Music> musics = this->musics();

    for(int i=0;i<musics.size();i++){
        QJsonObject o = musics.at(i).toJsonObj();
        array.append(o);
    }
    obj.insert("musics",array);
    return obj;
}

bool MusicSheet::operator ==(const MusicSheet& a)
{
    if(this->sheetName() == a.sheetName()){
        return true;
    }
    return false;
}

void MusicSheet::operator=(const MusicSheet &ms)
{
    this->_collectCount = ms._collectCount;
    this->_createTime = ms._createTime;
    this->_introducement= ms._introducement;
    this->_localSheetImageUrl = ms._localSheetImageUrl;
    this->_musics = ms._musics;
    this->_musicSheetID = ms._musicSheetID;
    this->_playCount = ms._playCount;
    this->_tags  = ms._tags;
    this->_netSheetImageUrl = ms._netSheetImageUrl;
    this->_userHeadImageUrl = ms._userHeadImageUrl;
    this->_userID = ms._userID;
    this->_userName = ms._userName;
    this->_sheetName  =ms._sheetName;
}


//bool MusicSheet::operator==(MusicSheet &a, MusicSheet &b)
//{
//    if(a.sheetName() == b.sheetName()){
//        return true;
//    }
//    return false;
//}


int MusicSheet::addMusic(const Music& music)
{
    for(int i=0;i<this->_musics.size();i++){
        Music t = this->_musics.at(i);
        if(t  == music){
            return i;
        }
    }
    qDebug()<<"添加音乐成功";
    this->_musics.append(music);
    return 0;
}

void MusicSheet::removeMusic(int index)
{
    if(index < this->_musics.size() && index >=0){
        this->_musics.removeAt(index);
    }
}

void MusicSheet::insertMusic(int index, Music music)
{

    for(int i=0;i<this->_musics.size();i++){
        Music t = this->_musics.at(i);
        if(t == music){
            return ;
        }
    }
    this->_musics.insert(index,music);

}

QString MusicSheet::musicSheetID() const
{
    return _musicSheetID;
}

void MusicSheet::setMusicSheetID(const QString &musicSheetID)
{
    _musicSheetID = musicSheetID;
}

QString MusicSheet::userHeadImageUrl() const
{
    return _userHeadImageUrl;
}

void MusicSheet::setUserHeadImageUrl(const QString &userHeadImageUrl)
{
    _userHeadImageUrl = userHeadImageUrl;
}

QString MusicSheet::introducement() const
{
    return _introducement;
}

void MusicSheet::setIntroducement(const QString &introducement)
{
    _introducement = introducement;
}

QString MusicSheet::userName() const
{
    return _userName;
}

void MusicSheet::setUserName(const QString &userName)
{
    _userName = userName;
}

QString MusicSheet::userID() const
{
    return _userID;
}

void MusicSheet::setUserID(const QString &userID)
{
    _userID = userID;
}

QString MusicSheet::netSheetImageUrl() const
{
    return _netSheetImageUrl;
}

void MusicSheet::setNetSheetImageUrl(const QString &netSheetImageUrl)
{
    _netSheetImageUrl = netSheetImageUrl;
}

QString MusicSheet::localSheetImageUrl() const
{
    return _localSheetImageUrl;
}

void MusicSheet::setLocalSheetImageUrl(const QString &localSheetImageUrl)
{
    _localSheetImageUrl = localSheetImageUrl;
}

int MusicSheet::collectCount() const
{
    return _collectCount;
}

void MusicSheet::setCollectCount(int collectCount)
{
    _collectCount = collectCount;
}

int MusicSheet::playCount() const
{
    return _playCount;
}

void MusicSheet::setPlayCount(int playCount)
{
    _playCount = playCount;
}




QString MusicSheet::sheetName() const
{
    return _sheetName;
}

void MusicSheet::setSheetName(const QString sheetName)
{
    _sheetName = sheetName;
}

QList<Music> MusicSheet::musics() const
{
    return _musics;
}

void MusicSheet::setMusics(const QList<Music> musics)
{
    _musics = musics;
}

QString MusicSheet::createTime() const
{
    return _createTime;
}

void MusicSheet::setCreateTime(const QString createTime)
{
    _createTime = createTime;
}

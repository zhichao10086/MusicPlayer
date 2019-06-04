#include "user.h"

User::User()
{
    this->__userID = QUuid::createUuid().toString();
    this->__age = 0;
    this->__name = "本地用户";
}

User User::jsonObj2User(const QJsonObject &obj)
{
    //json转换为user
    User user;

    if(obj.isEmpty())
        return user;
    if(obj.contains("userID"))
        user.setUserID(obj.value("userID").toString());

    user.setName(obj.value("name").toString());
    user.setAge(obj.value("age").toInt(18));
    user.setUserID(obj.value("userID").toString());

    //创建过的歌单列表
    QJsonArray cmsArray = obj.value("createdMusicSheets").toArray();
    QList<MusicSheet> cmsList;
    for(int i=0;i<cmsArray.size();i++){
        //变成歌单的obj
        QJsonObject msobj = cmsArray.at(i).toObject();
        MusicSheet ms =  MusicSheet::fromJsonObj2MusicSheet(msobj);
        cmsList.append(ms);
    }
    user.setCreatedMusicSheets(cmsList);

    //收藏过的歌单列表
    QJsonArray colmsArray = obj.value("collectedMusicSheets").toArray();
    QList<MusicSheet> colmsList;
    for(int i=0;i<colmsArray.size();i++){
        //变成歌单的obj
        QJsonObject msobj = colmsArray.at(i).toObject();
        MusicSheet ms =  MusicSheet::fromJsonObj2MusicSheet(msobj);
        colmsList.append(ms);
    }
    user.setCollectedMusicSheets(colmsList);


    QJsonObject playedMusicSheetObj = obj.value("playedMusicSheet").toObject();
    if(playedMusicSheetObj.empty()){
        MusicSheet ms;
        ms.setCreateTime(QDateTime::currentDateTime().toString());
        user.setPlayedMusicSheet(ms);
    }else{
        user.setPlayedMusicSheet(MusicSheet::fromJsonObj2MusicSheet(playedMusicSheetObj));
    }
    return user;


}

QJsonObject User::toJsonObj()
{
    QJsonObject obj;
    //obj.insert()

    obj.insert("name",this->name());
    obj.insert("age",this->age());
    obj.insert("userID",this->getUserID());

    QJsonArray createdSheetsArray;
    QList<MusicSheet> createdSheets = this->createdMusicSheets();
    for(int i=0;i<createdSheets.size();i++){
        createdSheetsArray.append(createdSheets.at(i).toJsonObj());
    }


    obj.insert("createdMusicSheets",createdSheetsArray);

    QJsonArray collectedSheetsArray;
    QList<MusicSheet> collectedSheets = this->collectedMusicSheets();
    for(int i=0;i<collectedSheets.size();i++){
        collectedSheetsArray.append(collectedSheets.at(i).toJsonObj());
    }

    obj.insert("collectedMusicSheets",collectedSheetsArray);


    //QJsonArray playedMusicsArray;
//    QList<Music> playedMusics = this->playedMusics();
//    for(int i=0;i<playedMusics.size();i++){
//        playedMusicsArray.append(playedMusics.at(i).toJsonObj());
//    }
    obj.insert("playedMusicSheet",this->playedMusicSheet().toJsonObj());

    return obj;

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

void User::addRecentPlayMusic(Music music)
{
    QList<Music> ms =this->__playedMusicSheet.musics();
    for(int i=0;i<ms.size();i++){
        Music t = ms.at(i);
        if(t == music){
            this->__playedMusicSheet.removeMusic(i);
            break;
        }

    }
    this->__playedMusicSheet.insertMusic(0,music);
}

void User::addCreatedMusicSheet(MusicSheet musicSheet)
{
    //不仅要把新建的歌单添加进来 而且要将这个转成json 最后存储
    this->__createdMusicSheets.append(musicSheet);
}

void User::addMusicToCreatedMusicSheet(const Music& music,int index, MusicSheet ms)
{
    if(this->__createdMusicSheets.value(index) == ms){
        qDebug()<<"准备添加音乐到歌单"<<ms.sheetName()<<this->__createdMusicSheets.at(index).musics().size();
        MusicSheet musicSheet = this->__createdMusicSheets.value(index);
        musicSheet.addMusic(music);
        this->__createdMusicSheets[index] = musicSheet;
        //this->__createdMusicSheets.removeAt(index);
        //this->__createdMusicSheets.insert(index,musicSheet);
        qDebug()<<this->__createdMusicSheets.at(index).musics().size();
    }
}



QList<MusicSheet> User::createdMusicSheets() const
{
    return __createdMusicSheets;
}

void User::setCreatedMusicSheets(const QList<MusicSheet> createdMusicSheets)
{
    __createdMusicSheets = createdMusicSheets;
}

QList<MusicSheet> User::collectedMusicSheets() const
{
    return __collectedMusicSheets;
}

void User::setCollectedMusicSheets(const QList<MusicSheet> collectedMusicSheets)
{
    __collectedMusicSheets = collectedMusicSheets;
}

MusicSheet User::playedMusicSheet() const
{
    return __playedMusicSheet;
}

void User::setPlayedMusicSheet(const MusicSheet playedMusicSheet)
{
    __playedMusicSheet = playedMusicSheet;
}

QString User::getUserID() const
{
    return __userID;
}

void User::setUserID(const QString &value)
{
    __userID = value;
}


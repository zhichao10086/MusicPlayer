#include "musicsheet.h"



MusicSheet::MusicSheet()
{

}

MusicSheet MusicSheet::fromJsonObj2MusicSheet(QJsonObject &obj)
{
    MusicSheet ms;
    if(obj.empty())
        return ms;
    ms.setCreateTime(obj.value("createTime").toString());
    ms.setSheetName(obj.value("sheetName").toString());

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
    obj.insert("sheetName",this->sheetName());
    obj.insert("createTime",this->createTime());
    QJsonArray array;

    QList<Music> musics = this->musics();

    for(int i=0;i<musics.size();i++){
        QJsonObject o = musics.at(i).toJsonObj();
        array.append(o);
    }
    obj.insert("musics",array);
    return obj;
}

int MusicSheet::addMusic(const Music& music)
{
    for(int i=0;i<this->_musics.size();i++){
        Music t = this->_musics.at(i);
        if(t  == music){
            return i;
        }
    }
    this->_musics.insert(0,music);
    return -1;
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

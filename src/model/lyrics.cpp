#include "lyrics.h"

Lyrics::Lyrics()
{

}

Lyrics::Lyrics(QString filename)
{

    this->__lyricsBeginIndex = -1;
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)){

        return;
    }

    QByteArray ba =  file.readAll();

    //this->__lyricsStr = Util::GetCorrectUnicode(ba);

    this->__lyricsStr = QString(ba);
    qDebug()<<"读取歌词:"<<filename;

    this->__init();
    file.close();
}

void Lyrics::operator =(const Lyrics &lyrics)
{
    this->__lyricsBeginIndex = lyrics.lyricsBeginIndex();
    this->__lyricsStr = lyrics.lyricsStr();
    this->__vecLyrics = lyrics.vecLyrics();
}

TagType Lyrics::tagType(QString& tag)
{
    //如果能够匹配正则表达式 则为时间标签
    //QString pattern("");
    //QRegularExpression regexp(pattern);

    QStringList resultList = tag.split(":");
    QString head = resultList.at(0).mid(1);
    bool* ok;
    head.toInt(ok,10);
    if(*ok){
        return TagType::TIMETAG;
    }

    return TagType::IDTAG;


}

bool Lyrics::isIDTag(QString tag)
{

}

bool Lyrics::isTimeTag(QString tag)
{

}

void Lyrics::setString(QString a)
{
//    QStringList resultList = a.split(":");
//    QString head = resultList.at(0).mid(1);
//    bool* ok;
//    head.toInt(ok,10);

//    qDebug()<<a;
    return;
}

QStringList Lyrics::allData()
{
    if(this->__lyricsStr.isEmpty())
        return QStringList();
    return this->__lyricsStr.split(QRegExp("\r*\n+"));

}

void Lyrics::__init()
{
    //this->__vecLyrics = QVector<LLData>(50);
    //QVector<LLData> a(100);
    //this->__vecLyrics =a;
    /*
     * 初始化vec
     */
    //QRegularExpression regExp()

    QStringList lyricsList = this->__lyricsStr.split(QRegExp("\r*\n+"));
    //qDebug()<<"lyrics size:"<<&lyricsList;
    //全部为字符串
    QString tempstr;
    QString timestr;
    for(int i=0;i<lyricsList.size();i++){
        LLData ldata ;
        //引用共享
        tempstr = lyricsList.value(i);
        //qDebug()<<"ldata size"<<sizeof(*ldata);
        //qDebug()<<&temp;
        //QString tempstr(lyricsList.value(i));
        //qDebug()<<ldata <<"  "<<&tempstr <<"  "<<i<<"  "<<tempstr;
        if(tempstr.isEmpty())
            break;

        int indexTag = tempstr.indexOf(']');
        ldata.index = i;
        //这里返回的string还是lyricsList的
        ldata.setTagStr(tempstr.mid(0,indexTag+1));
        //ldata.tagStr  = tempstr.mid(0,indexTag+1);
        //qDebug()<<"tagSTr:"<<&ldata.tagStr;
        //qDebug()<<indexTag<<"  "<<i<<"   "<<tempstr;
        ldata.setLineStr(tempstr.mid(indexTag+2));
        //ldata.lineStr = tempstr.mid(indexTag+2);
        ldata.tagtype = Lyrics::tagType(ldata.tagStr);

        this->setString(ldata.tagStr);
        //qDebug()<<"ldata tagstr size"<<sizeof(ldata.tagStr);
        if(ldata.tagtype == TagType::IDTAG){
            ldata.position = -1;
        }else if(ldata.tagtype == TagType::TIMETAG){
            //时间转换成position
            //QString timestr = ldata.tagStr.mid(1,ldata.tagStr.size()-2);
            //timestr.append('0');
            timestr = ldata.tagStr.mid(1,ldata.tagStr.size()-2);
            //QString timestrsub = timestr.mid(1,timestr.size()-2);
            //*timestrsub = timestr.mid(1,timestr.size()-1);
            //timestr.insert(timestr.size()-1,'0');
            timestr.append('0');
            QTime time = QTime::fromString(timestr,"mm:ss.zzz");

            int min = time.minute();
            int sec = time.second();
            int msec = time.msec();

            ldata.position = min* 60000 + sec*1000 + msec;
        }



        if(ldata.tagtype == TagType::TIMETAG && this->__lyricsBeginIndex == -1){
            this->__lyricsBeginIndex = i;
        }

        this->__vecLyrics.push_back(ldata);
    }

    qDebug()<<"歌词读取结束";

}

QString Lyrics::lyricsStr() const
{
    return __lyricsStr;
}

void Lyrics::setLyricsStr(const QString &lyricsStr)
{
    __lyricsStr = lyricsStr;
}

int Lyrics::lyricsBeginIndex() const
{
    return __lyricsBeginIndex;
}

void Lyrics::setLyricsBeginIndex(int lyricsBeginIndex)
{
    __lyricsBeginIndex = lyricsBeginIndex;
}

QVector<LLData> Lyrics::vecLyrics() const
{
    return __vecLyrics;
}

void Lyrics::setVecLyrics(const QVector<LLData> &vecLyrics)
{
    __vecLyrics = vecLyrics;
}


QString LyricsLineData::getLineStr() const
{
    return lineStr;
}

void LyricsLineData::setLineStr(const QString &value)
{
    lineStr = value;
}

QString LyricsLineData::getTagStr() const
{
    return tagStr;
}

void LyricsLineData::setTagStr(const QString &value)
{
    tagStr = value;
}

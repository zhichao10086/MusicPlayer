#ifndef LYRICS_H
#define LYRICS_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QFile>
#include <QByteArray>
#include <QRegularExpression>
#include <QStringList>
#include <QTime>
#include <QDebug>
#include "util.h"


enum TagType{
    IDTAG,
    TIMETAG
};

typedef class LyricsLineData{

public:
    int index;
    TagType tagtype;  //标签类型
    QString tagStr;  //标签数据
    QString lineStr;  //时间类型数据
    qint64 position;

    LyricsLineData(){
        index = -1;
        tagStr = "";
        lineStr = "";
        position = 0;
        cout<<"lldata goujian";
    }

    LyricsLineData(const LyricsLineData& data){
        this->index = data.index;
        QString* a = new QString;
        *a = data.tagStr;
        this->tagStr = *a;
        QString* b = new QString;
        *b = data.lineStr;
        this->lineStr = *b;
        position = data.position;
        tagtype = data.tagtype;
        cout<<"shenkaobeiwancheng";
    }

//    static qint64 tagStrToPosition(){

//    }

    QString getTagStr() const;
    void setTagStr(const QString &value);
    QString getLineStr() const;
    void setLineStr(const QString &value);
}LLData;

class Lyrics
{
public:
    Lyrics();

    /*
     * 通过文件名获得歌词文件
     *
     */
    Lyrics(QString filename);

    ~Lyrics(){
        qDebug()<<"xigou lyrics";
    }


    static TagType tagType(QString& tag);


    /*]
     *是否是IDtag
     */
    static bool isIDTag(QString tag);

    /*
     * 是否是时间标签
     */
    static bool isTimeTag(QString tag);


    void setString(QString a);

    /*
     * 返回所有数据
     */
    QStringList allData();


    QVector<LLData> vecLyrics() const;
    void setVecLyrics(const QVector<LLData> &vecLyrics);

    int lyricsBeginIndex() const;
    void setLyricsBeginIndex(int lyricsBeginIndex);

    QString lyricsStr() const;
    void setLyricsStr(const QString &lyricsStr);

private:

    /*
     *初始化歌词
     */
    void __init();


    int __lyricsBeginIndex;

    /*
     * 歌词的模型应该是一个队列形式
     */
    QVector<LLData> __vecLyrics;

    //应该有一个文本存储着全部歌词
    QString __lyricsStr;



};

#endif // LYRICS_H

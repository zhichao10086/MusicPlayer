#ifndef MP3HEADER_H
#define MP3HEADER_H

#include "stdlib.h"
#include "stdio.h"
#include <QDebug>
#include <QImage>
#include <QMap>
#include <QTextCodec>
#include <QString>
#include <QFile>
#include <QUrl>

using namespace std;
class MP3Header;

typedef struct ID3V2FrameH
{
   char frameID[4];               //存放标签格式，是否为id3v2
   unsigned char size[4];         //存放标签数据的大小
   char flags[2];
}ID3V2FH;

typedef struct MP3INFO
{
    QString Url;            //存放这首歌的详细地址
    QString Name;            //歌名  TIT2
    QString Album;           //专辑  TALB
    QString Singer;          //歌手  TPE1
    QString Picture_url;      //歌曲图片存放路径
    QString Picture_type;     //图片类型 jpg,png
    int     number;          //歌曲编号
    int     beginNum;         //图片起始位置
    int     lenth;            //图片数据长度
    bool     pic_flag;         //是否有图片


}MP3INFO;

typedef struct frameIDStruct
{
    int beginNum;
    int endNum;
    QString FrameId;

}frameIDStruct;


class MP3Header
{
public:
    MP3Header();
    FILE *fp;
    QString m_url;
    unsigned char Header[3];
    unsigned char FrameId[4];     //存放帧标识
    unsigned char Header_size[4];
    unsigned int mp3_TagSize;
    unsigned char frameSize[4];      //存放该帧内容的大小
    unsigned int framecount;          //计算出帧内容的大小
    //void GetMp3IDV2(const wchar_t *url);
    MP3INFO GetAllInfo(const wchar_t *url, int songNumber);
    //void GetPicture(MP3INFO *mp3info);
    //void GetFrameId();
    //QString GetInfo(QString fId);
    QMap<QString,frameIDStruct> m_IDmap;

};


#endif // MP3HEADER_H

#include "filefunccontroller.h"

FileFuncController::FileFuncController(QObject *parent) : QObject(parent)
{

}

QJsonObject FileFuncController::getJsonObjFromFile(QFile &file)
{
    if(!file.open(QIODevice::ReadOnly)){
        qDebug()<<"无法打开:"<<file.fileName();
        return QJsonObject();
    }

    QByteArray allData = file.readAll();
    file.close();
    QJsonParseError json_error;
    QString json(allData);
    //qDebug()<<json;

    QJsonDocument jsonDoc = QJsonDocument::fromJson(json.toUtf8(),&json_error);

    if(json_error.error != QJsonParseError::NoError){
        qDebug()<<"格式错误："<<file.fileName();
        return QJsonObject();
    }
    QJsonObject obj = jsonDoc.object();
    return obj;

}

bool FileFuncController::saveJsonObjToFile(QJsonObject obj, QString absoluteFileName)
{
    QFile file(absoluteFileName);
    if(!file.open(QIODevice::WriteOnly))
        return false;

    QJsonDocument doc(obj);
    QByteArray ba = doc.toJson();
    file.write(ba);
    file.close();
    return true;
}

Music FileFuncController::fromFileGetMusicTags(QString fileName)
{
    Music music;
    int ret;
    AVFormatContext* avformatContext = NULL;
    AVDictionaryEntry *tag = NULL;
    if( (ret = avformat_open_input(&avformatContext,fileName.toStdString().c_str(),NULL,NULL) )){
        qDebug()<<"failed to open file";
    }
    while ((tag = av_dict_get(avformatContext->metadata, "", tag, AV_DICT_IGNORE_SUFFIX))){
        //printf("%d %d",a,b);
        printf("Tag:%s,Value: %s",tag->key,tag->value);
    }

    avformat_close_input(&avformatContext);

    return music;

}

QList<Music> FileFuncController::fromFilesGetMusicTags(QStringList fileNames)
{
    QList<Music> musics;
    int ret;
    AVFormatContext* avformatContext = NULL;
    AVDictionaryEntry *tag = NULL;


    for(int i=0;i<fileNames.size();i++){
        if( (ret = avformat_open_input(&avformatContext,fileNames.at(i).toStdString().c_str(),NULL,NULL) )){
            qDebug()<<"failed to open file:"<<fileNames.at(i).toStdString().c_str();
        }
        QFileInfo fileInfo(fileNames.at(i));
        avformat_find_stream_info(avformatContext,NULL);
        Music music;
        music.setMusicPath(fileNames.at(i));
        music.setTime(Util::qint642QStringMinSec( (qint64)(avformatContext->duration/AV_TIME_BASE)*1000));
        music.setFileSize(fileInfo.size());
        qDebug()<<avformatContext->duration<<"  "<<AV_TIME_BASE;
        while ((tag = av_dict_get(avformatContext->metadata, "", tag, AV_DICT_IGNORE_SUFFIX))){
            if(QString(tag->key) == QString("title") )
                music.setTitle(QString(tag->value));
            else if(QString(tag->key) == QString("album"))
                music.setAlbum(QString(tag->value));
            else if(QString(tag->key) == QString("artist"))
                music.setArtist(QString(tag->value));
            else if(QString(tag->key) == QString("disc"))
                music.setDisc(QString(tag->value).toInt());
            else if(QString(tag->key) == QString("date"))
                music.setPublishDate(QString(tag->value));
            else if(QString(tag->key) == QString("track"))
                music.setTrack(QString(tag->value).toInt());
            else if(QString(tag->key) == QString("encoder"))
                music.setEncoder(QString(tag->value));
            else if(QString(tag->key) == QString("comment"))
                music.setComment(QString(tag->value));
        }

        //本地图片搞出来
        int sCount = avformatContext->nb_streams;
        QList<QImage> images;
        for(int j = 0;j<sCount;j++){
            if(avformatContext->streams[j]->disposition & AV_DISPOSITION_ATTACHED_PIC){
                AVPacket pkt = avformatContext->streams[j]->attached_pic;
                QImage img  = QImage::fromData((uchar*)pkt.data,pkt.size);
                images.append(img);
            }
        }
        music.setImages(images);

        //设置歌词
        QString lyricsFileName = fileNames.value(i);
        lyricsFileName =  lyricsFileName.mid(0,lyricsFileName.size()-4);
        lyricsFileName.append(".lrc");

        Lyrics lyrics(lyricsFileName);
        //qDebug()<<"lyrics地址"<<&lyrics;

        if(!lyrics.lyricsStr().isEmpty()){
            music.setLyricsPath(lyricsFileName);
            music.setLyrics(lyrics);
        }

        musics.append(music);
        avformat_close_input(&avformatContext);
    }

    return musics;

}




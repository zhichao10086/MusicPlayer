#ifndef FILEFUNCCONTROLLER_H
#define FILEFUNCCONTROLLER_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QFile>
#include <QByteArray>
#include <QDebug>
#include <QTextCodec>
#include "music.h"
#include "musicsheet.h"
#include <QList>
#include <QStringList>
#include <QImage>
#include <stdio.h>
#include <util.h>
#include <QFileInfo>
#ifdef __cplusplus
extern "C"
{
#endif
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
#include <libavutil/opt.h>
#include <libavutil/mathematics.h>
#include <libavutil/samplefmt.h>
#include <libavdevice/avdevice.h>
#ifdef __cplusplus
}
#endif
class FileFuncController : public QObject
{
    Q_OBJECT
public:
    explicit FileFuncController(QObject *parent = nullptr);


    static QJsonObject getJsonObjFromFile(QFile& file);

    static bool saveJsonObjToFile(QJsonObject obj,QString absoluteFileName);


    static Music fromFileGetMusicTags(QString fileName);

    static QList<Music> fromFilesGetMusicTags(QStringList fileNames);
signals:

public slots:
};

#endif // FILEFUNCCONTROLLER_H

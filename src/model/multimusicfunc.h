#ifndef MULTIMUSICFUNC_H
#define MULTIMUSICFUNC_H

#include <QObject>
#include <string>
#include <QDebug>
#include <QStringList>

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
#include <libavfilter/avfilter.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef __cplusplus
}
#endif

using namespace std;


typedef struct FilteringContext
{
    AVFilterContext *buffersink_ctx;
    AVFilterContext *buffersrc_ctx;
    AVFilterGraph *filter_graph;
} FilteringContext;



class MultiMusicFunc : public QObject
{
    Q_OBJECT
public:
    explicit MultiMusicFunc(QObject *parent = nullptr);
    enum RetMessage{
        error = -1,
        finish = 0,
    };

    //音乐剪辑
    static int musicCut(double start,double end,string inFilename,string outFileName);


    static int initRecordFilterGraph(AVFilterGraph **graph, AVFilterContext **src,
                         AVFilterContext **sink,AVCodecContext * pCodecCtx);


    static int initSWRFilterGraph(AVFilterGraph **graph, AVFilterContext **src,
                                  AVFilterContext **sink,AVCodecContext * pCodecCtx);

    static int swr();

    //录音
    static int audioRecord(QString outFilename,QString deviceName);

    //寻找录音设备
    static QStringList findAudioRecordDevice();

signals:

public slots:
};

#endif // MULTIMUSICFUNC_H

#ifndef FFMPEGPLAYER_H
#define FFMPEGPLAYER_H

#include <QObject>
#include "playthread.h"
#include <QList>
#include <QMediaPlayer>

#define __STDC_CONSTANT_MACROS

#ifdef __cplusplus
extern "C"
{
#endif
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
#include <libavutil/opt.h>
#include <libavutil/channel_layout.h>
#include <libavutil/mathematics.h>
#include <libavutil/samplefmt.h>
#include <libavdevice/avdevice.h>
#include <libavfilter/avfilter.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>

#include "libavutil/channel_layout.h"
#include "libavutil/md5.h"
#include "libavutil/mem.h"
#include "libavutil/opt.h"
#include "libavutil/samplefmt.h"
#include "libavfilter/avfilter.h"
#include "libavfilter/buffersink.h"
#include "libavfilter/buffersrc.h"
#include <libavutil/error.h>


#define INPUT_SAMPLERATE     44100
#define INPUT_FORMAT         AV_SAMPLE_FMT_FLTP
#define INPUT_CHANNEL_LAYOUT AV_CH_LAYOUT_5POINT0
#define VOLUME_VAL 100

#ifdef __cplusplus
}
#endif



/*
 * 用来记录playthread的一些上下文信息
 * 以及用户的一些配置信息 用于给playthread修改参数
 *
 *
 */
class FFmpegPlayer:public QObject
{
    Q_OBJECT
public:
    explicit FFmpegPlayer(QObject *parent = 0);

    //一些预设的场景
    enum Scene{
        toilet,//卫生间
        cave,//山洞
        outdoor,//室外
    };


    enum State
    {
        StoppedState,
        PlayingState,
        PausedState
    };
    //均衡器  人为设置好的一组参数
    bool isUseEqualizer = false;

    //用过滤器
    bool isUseFilter = false;


    /*
     * 初始化播放线程和配置信息
     */
    void init();



    /*
     * 初始化均衡器
     * 均衡器是带有场景以及不同频段的滤波器
     */
    void initFrequencyEqualizer();


    /*
     * 在init之前请先将usefilter 设置为tree
     * 如何将filter设置出来呢?
     */
    int initFilterGraph(AVFilterGraph **graph, AVFilterContext **src,
                         AVFilterContext **sink,AVCodecContext * pCodecCtx);


    /*
     * 初始化过滤器头和尾 src  dst
     */
    void initFilterSrcAndDst();

    /*
     * 初始化过滤器
     */
    void initFilters();

    /*
     * 设置filter
     */
    int addFilter(QString filterName,AVDictionary *options_dict = NULL);


public slots:
    void play();
    void pause();
    void stop();

    void play(QString url);
    void setPosition(qint64 position);
    void setVolume(int volume);


    void emitDurationChanged(qint64 duration);
    void emitPositionChanged(qint64 position);

signals:

    void stateChanged(State newState);

    void durationChanged(qint64 duration);
    void positionChanged(qint64 position);

    void volumeChanged(int volume);


private:
    //频率列表
    QList<int> __frequencyList;

    //过滤器列表
    QList<AVFilter*> __avfilterList;

    AVFilterGraph *__graph=NULL;
    AVFilterContext *__src=NULL, *__sink=NULL;

    PlayThread* __playThread;

};

#endif // FFMPEGPLAYER_H

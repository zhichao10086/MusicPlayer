#ifndef PLAYTHREAD_H
#define PLAYTHREAD_H

#include <QObject>
#include <QThread>
#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include <iostream>
#include <QDebug>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include <QList>
#include <functional>
#include <QJsonObject>
#include <QString>
#include <QMap>
#include <QJsonArray>
#include <QJsonValue>
#include "filterconstant.h"



#define MAX_AUDIO_FRAME_SIZE  192000
#define SDL_AUDIO_BUFFER_SIZE  1024
#define MAX_AUDIO_SIZE (25 * 16 * 1024)
#define MAX_VIDEO_SIZE (25 * 256 * 1024)
#define FLUSH_DATA "FLUSH"


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
#define VOLUME_VAL 5

#ifdef __cplusplus
}
#endif


using namespace std;
using namespace std::placeholders;

typedef std::function<void (void *userdata, Uint8 * stream,int len)> SDL_CallBack;


class PlayThread;

typedef struct PacketQueue {
    AVPacketList *first_pkt, *last_pkt;
    int nb_packets;
    int size;
    SDL_mutex *mutex;
    SDL_cond *cond;
} PacketQueue;







typedef struct{
    SwrContext* swr_ctx ;//  采样上下文
    AVFrame *wanted_frame;// 期待的帧结构
    uint8_t* audio_pkt_data;  //一个包的额数据
    int audio_pkt_size; //   一个包的大小
    AVFrame *frame; //     一个帧
    AVFormatContext* afct; //  文件上下文
    AVCodecContext *acct;//   编码上下文
    int curStreamIndex;

    unsigned int audio_buf_size; //始终是buf的大小   因为是回调 所以要记录
    unsigned int audio_buf_index; //标记发送到哪里了

    PacketQueue audioq; //    队列
    AVPacket pkt; //       包

    PlayThread* playThread;  //播放状况的封装
    AVFilterGraph *graph;
    AVFilterContext *src;
    AVFilterContext *sink;
}mediaState;

enum playerStatus
{
     playing,
     pausing,
     buffering,
     stopping
};


typedef struct EqualizerConfig{
       int freq;
       QString instance_name;
       int width;
       QString width_type;
       int gain;
       QString filter_name;
}EQConfig;



/*
 * 将一次播放封装成一个线程
 *
 */
class PlayThread : public QThread
{
    Q_OBJECT
public:



    bool isUseFilter = false;

    explicit PlayThread(QObject *parent = nullptr);

    void init();

    void initFilterConfigObj();

    void setMedia(const QString);


    int initMediaEnv(const QString);

    //清空缓存
    void clearCache();

    playerStatus getPlayerStatus();


    /*
     * 获得实例
     */
    QJsonObject getConfigObjByInstanceName(QString filtername,QString instanceName);


    int initFilterGraph();

    /*
     * 过滤图初始化
     */
    int initFilterGraph(AVFilterGraph **graph, AVFilterContext **src,
                         AVFilterContext **sink,AVCodecContext * pCodecCtx);


    void updateFilterGraph(const QJsonObject& obj);

    /*
     * 添加过滤器 需要一个名字和一个
     */
    int addFilters(QList<AVFilterContext*> filters);

    void FreeAllocSpace();

    //初始化过滤器
    AVFilterContext* initFilter(AVFilterGraph *graph,QString filtername,AVDictionary *options_dict);


    AVFilterContext* initEqualizerFilter(AVFilterGraph *graph,QString filtername,QJsonObject configObj,QString instanceName);

    //插入过滤器
    int insertFilter(AVFilterGraph *graph,QString filtername,AVDictionary *options_dict);

    qint64 getDuration() const;
    void setDuration(const qint64 &duration);

    qint64 getPosition() const;


    //void audio_callback(void* userdata, Uint8* stream, int len);


    int getVolume() const;

    QJsonObject getFiltersConfigs() const;
    void setFiltersConfigs(const QJsonObject &filtersConfigs);

protected:
    void run();

public slots:
    void stop();
    void pause();
    void play();

    void setPosition(qint64 position);
    void setVolume(int volume);

    //改变当前的位置
    void changeCurPosition(qint64 position);

signals:

    void durationChanged(qint64 duration);
    void positionChanged(qint64 position);

    void volumeChanged(int volume);
    void audioAvailableChanged(bool available);

private:
    //地址
    QString m_url;

    //音频播放的一些数据  上下文 解压格式等等
    mediaState m_MS;

    AVFilterGraph *__graph=NULL;
    AVFilterContext *__src=NULL, *__sink=NULL;


    SDL_AudioSpec __wanted_spec, __spec;

    //长度
    qint64 __duration;
    //位置
    qint64 __position;

    //音量
    int __volume;

    //有问题
    bool __hasTrouble;

    /*
     * {
     *  "abuffer":{},
     *  ""
     *  "volume":{},
     * }
     *
     */
    //filters 参数
    QJsonObject __filtersConfigs;

    QList<AVFilterContext*> __equalizerFilterCtxs;

    AVFilterContext* __volumeFilterCtx;


};

#endif // PLAYTHREAD_H

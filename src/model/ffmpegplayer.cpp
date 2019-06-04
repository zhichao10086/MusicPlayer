#include "ffmpegplayer.h"

FFmpegPlayer::FFmpegPlayer(QObject *parent) : QObject(parent)
{

}

void FFmpegPlayer::init()
{
    this->__playThread = new PlayThread;
}

void FFmpegPlayer::play()
{

}

void FFmpegPlayer::pause()
{

}

void FFmpegPlayer::stop()
{

}

void FFmpegPlayer::setPosition(qint64 position)
{

}

void FFmpegPlayer::setVolume(int volume)
{

}

void FFmpegPlayer::emitDurationChanged(qint64 duration)
{

}

void FFmpegPlayer::emitPositionChanged(qint64 position)
{

}

void FFmpegPlayer::play(QString url)
{

}

void FFmpegPlayer::initFrequencyEqualizer()
{

}

int FFmpegPlayer::initFilterGraph(AVFilterGraph **graph, AVFilterContext **src,
                                   AVFilterContext **sink,AVCodecContext * pCodecCtx)
{
    AVFilterGraph *filter_graph;

    AVFilterContext *abuffer_ctx;
    const AVFilter  *abuffer;
    AVFilterContext *bandPass_ctx;
    const AVFilter  *bandPass;
    AVFilterContext *volume_ctx;
    const AVFilter  *volume;
    AVFilterContext *abuffersink_ctx;
    const AVFilter  *abuffersink;
    uint8_t options_str[1024];
    uint8_t ch_layout[64];
    int err;
    AVDictionary *options_dict = NULL;

    filter_graph = avfilter_graph_alloc();

    //《《通过名字获得过滤器
    /* Create the abuffer filter;
     * it will be used for feeding the data into the graph. */
    abuffer = avfilter_get_by_name("abuffer");
    if (!abuffer) {
        fprintf(stderr, "Could not find the abuffer filter.\n");
        qDebug()<<stderr;
        return AVERROR_FILTER_NOT_FOUND;
    }
    //《《 并且为过滤器分配空间
    abuffer_ctx = avfilter_graph_alloc_filter(filter_graph, abuffer, "src");
    if (!abuffer_ctx) {
        qDebug()<<stderr;
        fprintf(stderr, "Could not allocate the abuffer instance.\n");
        return AVERROR(ENOMEM);
    }
    //《《通过这些函数来给过滤器设置参数
    /* Set the filter options through the AVOptions API. */
    av_get_channel_layout_string((char*)ch_layout, sizeof(ch_layout), 0, pCodecCtx->channel_layout);
    av_opt_set ( abuffer_ctx, "channel_layout", (const char *)ch_layout,  AV_OPT_SEARCH_CHILDREN);
    av_opt_set_sample_fmt(abuffer_ctx, "sample_fmt", pCodecCtx->sample_fmt, AV_OPT_SEARCH_CHILDREN);
//    //时间基数 这有些问题
    av_opt_set_q  (abuffer_ctx, "time_base",      pCodecCtx->time_base,  AV_OPT_SEARCH_CHILDREN);
    av_opt_set_int(abuffer_ctx, "sample_rate",   pCodecCtx->sample_rate,   AV_OPT_SEARCH_CHILDREN);
    av_opt_set_int(abuffer_ctx,"channels",pCodecCtx->channels,AV_OPT_SEARCH_CHILDREN);
    //    /* Now initialize the filter; we pass NULL options, since we have already
     /* set all the options above. */

    //《《现在初始化这个过滤器
    err = avfilter_init_str(abuffer_ctx, NULL);
    if (err < 0) {
        fprintf(stderr, "Could not initialize the abuffer filter.\n");
        return err;
    }


    //《《音量控制
    /* Create volume filter. */
    volume = avfilter_get_by_name("volume");
    if (!volume) {
        fprintf(stderr, "Could not find the volume filter.\n");
        return AVERROR_FILTER_NOT_FOUND;
    }
    //在图中创建一个实例
    volume_ctx = avfilter_graph_alloc_filter(filter_graph, volume, "volume");
    if (!volume_ctx) {
        fprintf(stderr, "Could not allocate the volume instance.\n");
        return AVERROR(ENOMEM);
    }
    /* A different way of passing the options is as key/value pairs in a
     * dictionary. */
    av_dict_set(&options_dict, "volume", AV_STRINGIFY(VOLUME_VAL), 0);
    err = avfilter_init_dict(volume_ctx, &options_dict);
    av_dict_free(&options_dict);
    if (err < 0) {
        fprintf(stderr, "Could not initialize the volume filter.\n");
        return err;
    }


    //《《带通滤波
    bandPass = avfilter_get_by_name("bandpass");
    if (!abuffer) {
        qDebug()<<"无法得到bandpass";
        return AVERROR_FILTER_NOT_FOUND;
    }
    //分配上下文
    bandPass_ctx = avfilter_graph_alloc_filter(filter_graph, bandPass, "bandPass");
    //参数设置  字典
    av_dict_set(&options_dict,"frequency",AV_STRINGIFY(30),0);
    av_dict_set(&options_dict,"csg",AV_STRINGIFY(1),0);
    av_dict_set(&options_dict,"width_type",AV_STRINGIFY(h),0);
    av_dict_set(&options_dict,"width",AV_STRINGIFY(20),0);
    err = avfilter_init_dict(bandPass_ctx,&options_dict);
    av_dict_free(&options_dict);
    if (err < 0) {
        fprintf(stderr, "Could not initialize the bandpass filter.\n");
        qDebug()<<"Could not initialize the bandpass filter.\n";
        return err;
    }


    /* Finally create the abuffersink filter;
     * it will be used to get the filtered data out of the graph. */
    abuffersink = avfilter_get_by_name("abuffersink");
    if (!abuffersink) {
        fprintf(stderr, "Could not find the abuffersink filter.\n");
        return AVERROR_FILTER_NOT_FOUND;
    }
    abuffersink_ctx = avfilter_graph_alloc_filter(filter_graph, abuffersink, "sink");
    if (!abuffersink_ctx) {
        fprintf(stderr, "Could not allocate the abuffersink instance.\n");
        return AVERROR(ENOMEM);
    }
    /* This filter takes no options. */
    err = avfilter_init_str(abuffersink_ctx, NULL);
    if (err < 0) {
        fprintf(stderr, "Could not initialize the abuffersink instance.\n");
        return err;
    }

    //连接过滤器
    /* Connect the filters;
     * in this simple case the filters just form a linear chain. */
    err = avfilter_link(abuffer_ctx, 0, volume_ctx, 0);
    if (err >= 0)
        err = avfilter_link(volume_ctx, 0, bandPass_ctx, 0);
    if (err >= 0)
        err = avfilter_link(bandPass_ctx, 0, abuffersink_ctx, 0);
    if (err < 0)
        fprintf(stderr, "Error connecting filters\n");

    err = avfilter_graph_config(filter_graph, NULL);

    *graph = filter_graph;
    *src   = abuffer_ctx;
    *sink  = abuffersink_ctx;
    return 0;
}

void FFmpegPlayer::initFilterSrcAndDst()
{

}

void FFmpegPlayer::initFilters()
{



    //avfilter_graph_free(&graph);
}

int FFmpegPlayer::addFilter(QString filterName, AVDictionary *options_dict)
{
    /*
     * ffmpeg 是用前驱结点带动整个图来运行
     */


}


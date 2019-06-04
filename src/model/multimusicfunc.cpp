#include "multimusicfunc.h"

MultiMusicFunc::MultiMusicFunc(QObject *parent) : QObject(parent)
{

}

int MultiMusicFunc::musicCut(double start, double end,string inFilename,string outFileName)
{
    //第一步 定义参数
    int ret;
    AVFormatContext *ifmt_ctx = NULL;
    AVFormatContext *ofmt_ctx = NULL;
    AVOutputFormat *ofmt = NULL;
    AVPacket pkt;

    double start_seconds = start; //开始时间
    double end_seconds = end;   //结束时间
    const char *in_filename=inFilename.c_str(); //输入文件
    const char *out_filename= outFileName.c_str();//输出文件
    //复制代码

//第二步 初始化上下文

    avformat_open_input(&ifmt_ctx, in_filename, 0, 0);

    //本质上调用了avformat_alloc_context、av_guess_format这两个函数，即创建了输出上下文，又根据输出文件后缀生成了最适合的输出容器
    avformat_alloc_output_context2(&ofmt_ctx, NULL, NULL, out_filename);
    ofmt = ofmt_ctx->oformat;


    //必须将流数据都出来。
    avformat_find_stream_info(ifmt_ctx,NULL);
//第三步 创建流及参数拷贝
    bool ok;

    for (int i = 0; i < ifmt_ctx->nb_streams; i++) {
            AVStream *in_stream = ifmt_ctx->streams[i];
            AVStream *out_stream = avformat_new_stream(ofmt_ctx, NULL);
            if (!out_stream) {
                fprintf(stderr, "Failed allocating output stream\n");
                ret = AVERROR_UNKNOWN;
                return error;
            }

            avcodec_parameters_copy(out_stream->codecpar, in_stream->codecpar);


            //avcodec_copy_context(out_stream->codec,in_stream->codec);
            //out_stream->codec in_stream->codec->sample_rate
            //out_stream->time_base = in_stream->time_base;
            out_stream->codecpar->codec_tag = 0;
        }
    //复制代码

    qDebug()<<"创建流及参数拷贝 完毕";
//第四步 打开输出文件

    avio_open(&ofmt_ctx->pb, out_filename, AVIO_FLAG_WRITE);
    //复制代码

    qDebug()<<"开始 处理、写入数据";
//第五步 处理、写入数据

    // 写头信息

    ret = avformat_write_header(ofmt_ctx,NULL);
    if (ret < 0) {
        fprintf(stderr, "Error occurred when opening output file\n");
        return error;
    }

    qDebug()<<"跳转";
    //跳转到指定帧
    ret = av_seek_frame(ifmt_ctx, -1, start_seconds * AV_TIME_BASE, AVSEEK_FLAG_ANY);
    if (ret < 0) {
            fprintf(stderr, "Error seek\n");
            return error;
    }

    // 根据流数量申请空间，并全部初始化为0
    int64_t *dts_start_from = (int64_t* )malloc(sizeof(int64_t) * ifmt_ctx->nb_streams);
    memset(dts_start_from, 0, sizeof(int64_t) * ifmt_ctx->nb_streams);

    int64_t *pts_start_from = (int64_t* )malloc(sizeof(int64_t) * ifmt_ctx->nb_streams);
    memset(pts_start_from, 0, sizeof(int64_t) * ifmt_ctx->nb_streams);

    while (1) {
            AVStream *in_stream, *out_stream;

            //读取数据
            ret = av_read_frame(ifmt_ctx, &pkt);
            if (ret < 0)
                break;

            in_stream = ifmt_ctx->streams[pkt.stream_index];
            out_stream = ofmt_ctx->streams[pkt.stream_index];

            // 时间超过要截取的时间，就退出循环
            if (av_q2d(in_stream->time_base) * pkt.pts > end_seconds) {
                av_packet_unref(&pkt);
                break;
            }

            // 将截取后的每个流的起始dts 、pts保存下来，作为开始时间，用来做后面的时间基转换
            if (dts_start_from[pkt.stream_index] == 0) {
                dts_start_from[pkt.stream_index] = pkt.dts;
            }
            if (pts_start_from[pkt.stream_index] == 0) {
                pts_start_from[pkt.stream_index] = pkt.pts;
            }

            // 时间基转换   计算 a*b/c
            pkt.pts = av_rescale_q_rnd(pkt.pts - pts_start_from[pkt.stream_index], in_stream->time_base, out_stream->time_base, AV_ROUND_NEAR_INF);
            pkt.dts = av_rescale_q_rnd(pkt.dts - dts_start_from[pkt.stream_index], in_stream->time_base,out_stream->time_base, AV_ROUND_NEAR_INF );

            if (pkt.pts < 0) {
                pkt.pts = 0;
            }
            if (pkt.dts < 0) {
                pkt.dts = 0;
            }

            pkt.duration = (int) av_rescale_q((int64_t) pkt.duration, in_stream->time_base, out_stream->time_base);
            pkt.pos = -1;

            //一帧视频播放时间必须在解码时间点之后，当出现pkt.pts < pkt.dts时会导致程序异常，所以我们丢掉有问题的帧，不会有太大影响。
            if (pkt.pts < pkt.dts) {
                continue;
            }
            //在有多个流的情况下要用av_interleaved_write_frame，只有单一流2个函数都可以用。
            ret = av_interleaved_write_frame(ofmt_ctx, &pkt);
            if (ret < 0) {
                fprintf(stderr, "Error write packet\n");
                break;
            }
            //保存数据
            av_packet_unref(&pkt);
        }

    //释放资源
    free(dts_start_from);
    free(pts_start_from);

    qDebug()<<"结束";

    //写文件尾信息
    av_write_trailer(ofmt_ctx);


    //avio_close(ofmt_ctx->pb);

    //avformat_close_input(&ifmt_ctx);

    //free(ifmt_ctx);
    //free(ofmt_ctx);

    //avformat_close_input(&ofmt_ctx);


    return finish;
}

int MultiMusicFunc::initRecordFilterGraph(AVFilterGraph **graph, AVFilterContext **src, AVFilterContext **sink, AVCodecContext *pCodecCtx)
{
    AVFilterGraph *filter_graph;

    AVFilterContext *abuffer_ctx;
    const AVFilter  *abuffer;
    AVFilterContext *swr_ctx;
    const AVFilter  *swr;
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
    volume_ctx = avfilter_graph_alloc_filter(filter_graph, volume, "volume");
    //this->__volumeFilterCtx = volume_ctx;
    if (!volume_ctx) {
        fprintf(stderr, "Could not allocate the volume instance.\n");
        return AVERROR(ENOMEM);
    }
    /* A different way of passing the options is as key/value pairs in a
     * dictionary. */
    av_dict_set_int(&options_dict, "volume", 100, 0);
    err = avfilter_init_dict(volume_ctx, &options_dict);
    av_dict_free(&options_dict);
    if (err < 0) {
        fprintf(stderr, "Could not initialize the volume filter.\n");
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
    qDebug()<<"volume link";
    AVFilterContext* pre = volume_ctx;

    /*
     * 连接
     */

    if (err >= 0)
        err = avfilter_link(pre, 0, abuffersink_ctx, 0);
    if (err < 0)
        fprintf(stderr, "Error connecting filters\n");

    err = avfilter_graph_config(filter_graph, NULL);

    *graph = filter_graph;
    *src   = abuffer_ctx;
    *sink  = abuffersink_ctx;
    return 0;

}

int MultiMusicFunc::initSWRFilterGraph(AVFilterGraph **graph, AVFilterContext **src, AVFilterContext **sink, AVCodecContext *pCodecCtx)
{
    AVFilterGraph *filter_graph;

    AVFilterContext *abuffer_ctx;
    const AVFilter  *abuffer;
    AVFilterContext *swr_ctx;
    const AVFilter  *swr;
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
    volume_ctx = avfilter_graph_alloc_filter(filter_graph, volume, "volume");
    //this->__volumeFilterCtx = volume_ctx;
    if (!volume_ctx) {
        fprintf(stderr, "Could not allocate the volume instance.\n");
        return AVERROR(ENOMEM);
    }
    /* A different way of passing the options is as key/value pairs in a
     * dictionary. */
    av_dict_set_int(&options_dict, "volume", 100, 0);
    err = avfilter_init_dict(volume_ctx, &options_dict);
    av_dict_free(&options_dict);
    if (err < 0) {
        fprintf(stderr, "Could not initialize the volume filter.\n");
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
    qDebug()<<"volume link";
    AVFilterContext* pre = volume_ctx;

    /*
     * 连接
     */

    if (err >= 0)
        err = avfilter_link(pre, 0, abuffersink_ctx, 0);
    if (err < 0)
        fprintf(stderr, "Error connecting filters\n");

    err = avfilter_graph_config(filter_graph, NULL);

    *graph = filter_graph;
    *src   = abuffer_ctx;
    *sink  = abuffersink_ctx;
    return 0;

}

int MultiMusicFunc::swr()
{
    //第一步 定义参数
    int ret;
    AVFormatContext *ifmt_ctx = NULL;
    AVFormatContext *ofmt_ctx = NULL;
    AVOutputFormat *ofmt = NULL;
    AVPacket pkt;
    AVFilterGraph *graph;
    AVFilterContext *src;
    AVFilterContext *sink;

    const char *in_filename="./record/record01.wav"; //输入文件
    const char *out_filename="./record/record01.mp3";//输出文件
    //复制代码

//第二步 初始化上下文

    avformat_open_input(&ifmt_ctx, in_filename, 0, 0);

    //本质上调用了avformat_alloc_context、av_guess_format这两个函数，即创建了输出上下文，又根据输出文件后缀生成了最适合的输出容器
    avformat_alloc_output_context2(&ofmt_ctx, NULL, NULL, out_filename);
    ofmt = ofmt_ctx->oformat;


    //必须将流数据都出来。
    avformat_find_stream_info(ifmt_ctx,NULL);
//第三步 创建流及参数拷贝
    bool ok;

    AVCodecContext* pCodeCtx = nullptr;
    for (int i = 0; i < ifmt_ctx->nb_streams; i++) {
        AVStream *in_stream = ifmt_ctx->streams[i];
        AVStream *out_stream = avformat_new_stream(ofmt_ctx, NULL);
        if (!out_stream) {
            fprintf(stderr, "Failed allocating output stream\n");
            ret = AVERROR_UNKNOWN;
            return error;
        }

        avcodec_parameters_copy(out_stream->codecpar, in_stream->codecpar);
        pCodeCtx = in_stream->codec;

        //avcodec_copy_context(out_stream->codec,in_stream->codec);
        //out_stream->codec in_stream->codec->sample_rate
        //out_stream->time_base = in_stream->time_base;
        out_stream->codecpar->codec_tag = 0;
    }
    //复制代码

    qDebug()<<"创建流及参数拷贝 完毕";
//第四步 打开输出文件

    avio_open(&ofmt_ctx->pb, out_filename, AVIO_FLAG_WRITE);
    //复制代码

    qDebug()<<"开始 处理、写入数据";
//第五步 处理、写入数据

    // 写头信息

    ret = avformat_write_header(ofmt_ctx,NULL);


    initSWRFilterGraph(&graph,&src,&sink,pCodeCtx);


    while(av_read_frame(ifmt_ctx,&pkt)){




        avcodec_send_packet(ofmt_ctx->,&packet);
        while(avcodec_receive_frame(m_MS.acct,m_MS.frame)==0) {
            int data_size = av_samples_get_buffer_size(NULL,
                                 m_MS.acct->channels,
                                 m_MS.frame->nb_samples,
                                 m_MS.acct->sample_fmt,
                                 1);

            qDebug()<<m_MS.frame->extended_data[0][0];

            //streamOut->write((const char*)m_MS.frame->extended_data[0],data_size);
        }

            //在有多个流的情况下要用av_interleaved_write_frame，只有单一流2个函数都可以用。
            ret = av_interleaved_write_frame(ofmt_ctx, &pkt);
            if (ret < 0) {
                fprintf(stderr, "Error write packet\n");
                break;
            }
            //保存数据
            av_packet_unref(&pkt);
    }

    //释放资源
    free(dts_start_from);
    free(pts_start_from);

    qDebug()<<"结束";

    //写文件尾信息
    av_write_trailer(ofmt_ctx);


    //avio_close(ofmt_ctx->pb);

    //avformat_close_input(&ifmt_ctx);

    //free(ifmt_ctx);
    //free(ofmt_ctx);

    //avformat_close_input(&ofmt_ctx);


    return finish;
}

int MultiMusicFunc::audioRecord(QString outFilename,QString deviceName)
{
    AVInputFormat* iFmt = nullptr;
    AVOutputFormat* oFmt = nullptr;
    AVFormatContext* iFmtCtx = nullptr;
    AVFormatContext* oFmtCtx = nullptr;

}


QStringList MultiMusicFunc::findAudioRecordDevice()
{
    //avdevice_register_all();
    av_register_all();
    avdevice_register_all();
    //avformat_open_input()
    qDebug()<<"查看设备";
    QStringList strList;
    AVInputFormat* inputFmt = nullptr;
    AVOutputFormat* outputFmt = nullptr;
    AVProbeData probeData;
    //inputFmt = av_input_audio_device_next(inputFmt);
    //qDebug()<<inputFmt->name<<"  name";
    //AVInputFormat* pInputFormat = nullptr;
    //pInputFormat = av_iformat_next(NULL);

    while((inputFmt = av_input_audio_device_next(inputFmt)) != NULL){

        AVDictionary* options = NULL;
        av_dict_set(&options,"list_devices","true",0);
        QString str(inputFmt->long_name);
        AVFormatContext *pFormatCtx = avformat_alloc_context();
        inputFmt = av_find_input_format(inputFmt->name);
        avformat_open_input(&pFormatCtx,QString("./local/123.mp3").toStdString().c_str(),NULL,NULL);
        //avdevice_list_devices()
        AVDeviceInfoList* list = new AVDeviceInfoList;
        avdevice_list_devices(pFormatCtx,&list);
        for(int i =0; i<list->nb_devices;i++){
            qDebug()<<(list->devices)[i]->device_name;
        }
        strList.append(str);
        qDebug()<<str;
    }





//    while(pInputFormat != NULL)
//    {
//        printf("%s ", pInputFormat->name);
//        pInputFormat = pInputFormat->next;
//    }
//    AVDictionary* options = NULL;
//    av_dict_set(&options,"list_devices","true",0);
//    AVFormatContext *pFormatCtx = avformat_alloc_context();
//    inputFmt = av_find_input_format("lavfi");
    //avformat_open_input(&pFormatCtx,"video=dummy",inputFmt,&options);

    //AVDeviceInfoList* list = new AVDeviceInfoList;

    //int ret = avdevice_list_input_sources(NULL,"dshow",NULL,&list);
    //qDebug()<<ret;
    return strList;
}

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

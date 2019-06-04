#include "playthread.h"

bool isquit = false;








// 包队列初始化
void packet_queue_init(PacketQueue* q)
{
    q->last_pkt = NULL;
    q->first_pkt = NULL;
    q->mutex = SDL_CreateMutex();
    q->cond = SDL_CreateCond();
}

// 放入packet到队列中，不带头指针的队列
static int packet_queue_put(PacketQueue*q, AVPacket *pkt)
{
    AVPacketList *pktl;
    if (av_dup_packet(pkt) < 0)
        return -1;

    pktl = (AVPacketList*)av_malloc(sizeof(AVPacketList));
    if (!pktl)
        return -1;

    pktl->pkt = *pkt;
    pktl->next = nullptr;

    SDL_LockMutex(q->mutex);

    if (!q->last_pkt) // 队列为空，新插入元素为第一个元素
        q->first_pkt = pktl;
    else // 插入队尾
        q->last_pkt->next = pktl;

    q->last_pkt = pktl;

    q->nb_packets++;
    q->size += pkt->size;

    SDL_CondSignal(q->cond);
    SDL_UnlockMutex(q->mutex);
    return 0;
}

// 从队列中取出packet
static int packet_queue_get(PacketQueue *q, AVPacket *pkt, int block) {
    AVPacketList *pkt1;
    int ret;

    SDL_LockMutex(q->mutex);

    for (;;)
    {
        if (isquit)
         return -1;
        pkt1 = q->first_pkt;
        if (pkt1) {
            q->first_pkt = pkt1->next;
            if (!q->first_pkt) {
                q->last_pkt = NULL;
            }
            q->nb_packets--;
            q->size -= pkt1->pkt.size;
            *pkt = pkt1->pkt;
            av_free(pkt1);
            ret = 1;
            break;
        } else if (!block) {
            ret = 0;
            break;
        } else {
            SDL_CondWait(q->cond, q->mutex);
        }
    }
    SDL_UnlockMutex(q->mutex);
    return ret;
}

static void packet_queue_flush(PacketQueue *q)
{
    SDL_LockMutex(q->mutex);
    AVPacketList *pkt, *pkt1;
    for(pkt = q->first_pkt; pkt != NULL; pkt = pkt1)
    {
        pkt1 = pkt->next;
        if(pkt1->pkt.data != (uint8_t *)"FLUSH")
        {

        }
        av_free_packet(&pkt->pkt);
        av_freep(&pkt);

    }
    q->last_pkt = NULL;
    q->first_pkt = NULL;
    q->nb_packets = 0;
    q->size = 0;
    SDL_UnlockMutex(q->mutex);
}


/*
 * 一个pakect里有多个frame返回的是解码的数据长度
 *
 */
int audio_decode_frame(mediaState* MS, uint8_t* audio_buf, int buf_size)
{

    int len1;
    int data_size = 0;
    if (isquit)
        return -1;
    int err;
    while (true)
    {
        //如果包的大小>0  则继续读取剩余解码的frame
        //否则从队列中取一个packet出来
        //audio_pkt_size 用来发现包是否读完
        while (MS->audio_pkt_size > 0)
        {
            if (isquit)
                return -1;
            qDebug()<<"开始解码";
            int got_frame = 0;
            //发送一个未解码的packet
            //len1 = avcodec_send_packet(MS->acct,&MS->pkt);

            len1 = avcodec_decode_audio4(MS->acct, MS->frame, &got_frame, &MS->pkt);

            //pts * time_base 表示时间流中的秒数
            //int msecond = qint64(1000*MS->frame->pts * av_q2d(MS->afct->streams[MS->curStreamIndex]->time_base));
            //int msecond =  av_rescale_q_rnd(MS->frame->pts,MS->acct->time_base,MS->afct->streams[MS->curStreamIndex]->time_base,AV_ROUND_NEAR_INF);
            //qDebug()<<"msecond:"<<msecond;

            //MS->playThread->setPosition(msecond);

            //通过frame判断
            //qDebug()<<"second";

            if(len1<0){
                qDebug()<<"发送错误";
                return -1;
            }
            av_buffersrc_add_frame(MS->src,MS->frame);
            /*
             //AV_BUFFERSRC_FLAG_KEEP_REF
            while(avcodec_receive_frame(MS->acct,MS->frame) >= 0){
                 err = av_buffersrc_add_frame(MS->src,MS->frame);
                 if(err <0){
                     qDebug()<<"发送发生错误";
                     av_frame_unref(MS->frame);
                     return -1;
                 }
                 qDebug()<<"收到解码后的frame :";
            }
            //获得了 frame之后 将frame送去过滤图
            */


            //获得过滤好的frame

            //while(av_buffersink_get_frame(MS->sink,MS->frame)>=0){
            //    break;
            //}

            err = av_buffersink_get_frame(MS->sink, MS->frame);

            if(err<0){
                qDebug()<<"过滤错误";
                return -1;
            }
            int second = qint64(1000*MS->frame->pts * av_q2d(MS->afct->streams[MS->curStreamIndex]->time_base));
            //int msecond =  av_rescale_q_rnd(MS->frame->pts,MS->acct->time_base,MS->afct->streams[MS->curStreamIndex]->time_base,AV_ROUND_NEAR_INF);
            qDebug()<<"msecond:"<<second;

            MS->playThread->setPosition(second);

            //通过frame判断

            //len1 = sizeof(MS->frame->extended_data);
            //qDebug()<<"len1:"<<len1;
            //got_frame = 1;

            //读到的数据大小

            //收到解码的frame
            /*
            while((err = avcodec_receive_frame(MS->acct,MS->frame) )>=0 ){

                //实现1   将所有全部读完
                //原来的data_size
                //这一帧的原本数据buffer的大小
                //av_
                //avcodec_decode_audio4()
                //data_size += av_samples_get_buffer_size(NULL, MS->acct->channels,MS-> frame->nb_samples, MS->acct->sample_fmt, 1);

                qDebug()<<av_get_sample_fmt_name((AVSampleFormat) MS->frame->format);
                //MS->wanted_frame->nb_samples =
                //实现2 一帧一帧读完
                //MS->audio_pkt_data += data_size;
                //MS->audio_pkt_size -= data_size;
                //qDebug()<<MS->audio_pkt_size;
                //data_size += MS->frame->linesize[0];
                //if (got_frame)

                //依据channel，nb_sample，sample_fmt 计算frame的数据块的大小


                if (MS->frame->channels > 0 && MS->frame->channel_layout == 0)
                    MS->frame->channel_layout = av_get_default_channel_layout(MS->frame->channels);
                else if (MS->frame->channels == 0 && MS->frame->channel_layout > 0)
                    MS->frame->channels = av_get_channel_layout_nb_channels(MS->frame->channel_layout);
                if (MS->swr_ctx)
                {
                    swr_free(&MS->swr_ctx);
                    MS->swr_ctx = nullptr;
                }
                qDebug()<<"设置重采样";
                //设置数据转换上下文的参数
                MS->swr_ctx = swr_alloc_set_opts(nullptr, MS->wanted_frame->channel_layout,
                                             (AVSampleFormat)MS->wanted_frame->format,
                                             MS->wanted_frame->sample_rate,
                                             MS->frame->channel_layout,
                                             (AVSampleFormat)MS->frame->format,
                                             MS->frame->sample_rate, 0, nullptr);//无限分？
                if (!MS->swr_ctx || swr_init(MS->swr_ctx) < 0)
                {
                    cout << "swr_init failed:" << endl;
                    break;
                }
                //`a * b / c`
                int dst_nb_samples = av_rescale_rnd(swr_get_delay(MS->swr_ctx, MS->frame->sample_rate) + MS->frame->nb_samples, MS->frame->sample_rate, MS->frame->sample_rate, AVRounding(1));
                //数据转换
                //实际的数据长度
                int len2 = swr_convert(MS->swr_ctx, (uint8_t**)(*audio_buf+data_size), dst_nb_samples,(const uint8_t**)MS->frame->data, MS->frame->nb_samples);//这个才是最重要的~前面所做的工作都是为这个
                if (len2 < 0)
                {
                    cout << "swr_convert failed\n";
                    break;
                }

                //这里是重采样的数据长度
                data_size += MS->wanted_frame->channels * len2 * av_get_bytes_per_sample((AVSampleFormat)MS->wanted_frame->format);
                //这里返回的才是需要的


            }

            //数据块大小读取完毕后

            MS->audio_pkt_size = 0;
            //全部接受完毕
            if(data_size <=0){

                continue;
            }

            return data_size;
            */
            //return data_size; // we have data,return it and come back for more later
            //planar 是每个声道分开存储
            qDebug()<<av_get_sample_fmt_name((AVSampleFormat) MS->frame->format)<<" "
                   <<MS->acct->channels<<" "<<MS->frame->nb_samples<<" "<<av_get_sample_fmt_name((AVSampleFormat)MS->acct->sample_fmt);
            MS->audio_pkt_data += len1;
            MS->audio_pkt_size -= len1;
            data_size = 0;

            //重采样
            if(got_frame) {
                //这个data_size 是总的通道数 * 采样数 * 数据格式
                data_size = av_samples_get_buffer_size(NULL,
                                     MS->acct->channels,
                                     MS->frame->nb_samples,
                                     MS->acct->sample_fmt,
                                     1);
                if (MS->frame->channels > 0 && MS->frame->channel_layout == 0)
                    MS->frame->channel_layout = av_get_default_channel_layout(MS->frame->channels);
                else if (MS->frame->channels == 0 && MS->frame->channel_layout > 0)
                    MS->frame->channels = av_get_channel_layout_nb_channels(MS->frame->channel_layout);
                if (MS->swr_ctx)
                {
                    swr_free(&MS->swr_ctx);
                    MS->swr_ctx = nullptr;
                }
                qDebug()<<"设置重采样";
                //设置数据转换上下文的参数
                MS->swr_ctx = swr_alloc_set_opts(nullptr, MS->wanted_frame->channel_layout,
                                             (AVSampleFormat)MS->wanted_frame->format,
                                             MS->wanted_frame->sample_rate,
                                             MS->frame->channel_layout,
                                             (AVSampleFormat)MS->frame->format,
                                             MS->frame->sample_rate, 0, nullptr);//无限分？
                if (!MS->swr_ctx || swr_init(MS->swr_ctx) < 0)
                {
                    cout << "swr_init failed:" << endl;
                    break;
                }
                //`a * b / c`
                int dst_nb_samples = av_rescale_rnd(swr_get_delay(MS->swr_ctx, MS->frame->sample_rate) + MS->frame->nb_samples, MS->frame->sample_rate, MS->frame->sample_rate, AVRounding(1));
                //数据转换
                //实际的数据长度
                qDebug()<<sizeof(MS->frame->data)<<"   dst_nb_samples:"<<dst_nb_samples
                       <<" av_get_bytes_per_sample :" << av_get_bytes_per_sample((AVSampleFormat)MS->wanted_frame->format);
                //audio_buf 是一个  一维数组指针   audio_buf 本身存的是一个地址  所以&audio_buf 就是存放数组起始地址的空间的地址
                int len2 = swr_convert(MS->swr_ctx, &audio_buf, dst_nb_samples,(const uint8_t**)MS->frame->data, MS->frame->nb_samples);//这个才是最重要的~前面所做的工作都是为这个
                if (len2 < 0)
                {
                    cout << "swr_convert failed\n";
                    break;
                }

                //这里是重采样的数据长度   通道数*长度 * 2
                data_size = MS->wanted_frame->channels * len2 * av_get_bytes_per_sample((AVSampleFormat)MS->wanted_frame->format);
                //这里返回的才是需要的


                //assert(data_size <= buf_size);
                //memcpy(audio_buf, MS->frame->data[0], data_size);
            }
            if(data_size <= 0) {
            /* No data yet, get more frames */
                continue;
            }
            /* We have data, return it and come back for more later */
            return data_size;


        }
        if (MS->pkt.buf)
            av_free_packet(&MS->pkt);
        if (packet_queue_get(&MS->audioq,&MS->pkt,1)<=0)
            return -1;
        /*
        err = avcodec_send_packet(MS->acct,&MS->pkt);
        if ( err < 0 ) {
            printf("Error in decoding audio frame.\n");
            exit(0);
        }
        */
        //从队列中取得数据并将数据指针赋值
        //avcodec_send_packet(MS->acct,&MS->pkt);
        MS->audio_pkt_data =MS->pkt.data;
        MS->audio_pkt_size = MS->pkt.size;
    }
}

//注意userdata是前面的AVCodecContext.
//len的值常为2048,表示一次发送多少。
//audio_buf_size：一直为样本缓冲区的大小，wanted_spec.samples.（一般每次解码这么多，文件不同，这个值不同)
//audio_buf_index： 标记发送到哪里了。
//这个函数的工作模式是:
//1. 解码数据放到audio_buf, 大小放audio_buf_size。(audio_buf_size = audio_size;这句设置）
//2. 调用一次callback只能发送len个字节,而每次取回的解码数据可能比len大，一次发不完。
//3. 发不完的时候，会len == 0，不继续循环，退出函数，继续调用callback，进行下一次发送。
//4. 由于上次没发完，这次不取数据，发上次的剩余的，audio_buf_size标记发送到哪里了。
//5. 注意，callback每次一定要发且仅发len个数据，否则不会退出。
//如果没发够，缓冲区又没有了，就再取。发够了，就退出，留给下一个发，以此循环。
//三个变量设置为static就是为了保存上次数据，也可以用全局变量，但是感觉这样更好。

void audio_callback(void* userdata, Uint8* stream, int len)
{
    mediaState* MS = (mediaState*)userdata;
    int len1, audio_size;
    SDL_memset(stream, 0, len);
    qDebug()<<"调用一次callback";
    if (isquit)
        return;
    while (len > 0)
    {
        //audio_buff 保存一次的数据
       //buff一定要*2以上，如果小了就会在memcpy的时候变小！
         uint8_t audio_buff[MAX_AUDIO_FRAME_SIZE*2];

        if (MS->audio_buf_index >= MS->audio_buf_size)
        {
            //index >= size 则重新获取数据
            //数据全部发送 ，再去获取数据
            //解码
            audio_size = audio_decode_frame(MS, audio_buff, sizeof(audio_buff));

            qDebug()<<"audio_size:"<<audio_size;
            if (isquit)
                return;
            if (audio_size < 0){
                //错误则静音
                MS->audio_buf_size = 1024;
                SDL_memset(audio_buff, 0, MS->audio_buf_size);
            }else{
                //每次读取成功会设置当前的size
                MS->audio_buf_size = audio_size;

            }
            //回到缓冲区开头
            MS->audio_buf_index = 0;
        }

        //剩余的数据
        len1 = MS->audio_buf_size - MS->audio_buf_index;
        qDebug()<<"len1:"<<len1<<" len: "<<len;
        //len1常比len大，但是一个callback只能发len个
        if (len1 > len)
            len1 = len;
        //每次传输 len长度的数据  从buff开头 +index
        //SDL_MixAudio(stream, (uint8_t*)audio_buff + MS->audio_buf_index, len1, SDL_MIX_MAXVOLUME);
        memcpy(stream, (uint8_t *)audio_buff + MS->audio_buf_index, len1);
        //改变stream的位置
        //如果len>len1  则index 肯定小于size  此时 len 还有空间
        len -= len1;
        stream += len1;
        MS->audio_buf_index += len1;//这个就代表的当前位置
        qDebug()<<"index:"<<MS->audio_buf_index<<"  len:"<<len<<" size:"<<MS->audio_buf_size;
        //qDebug()<<MS->audio_buf_index;
    }
}

void PlayThread::FreeAllocSpace()
{
    SDL_CloseAudio();//Close SDL
    SDL_Quit();

    if(m_MS.wanted_frame)
    av_frame_free(&m_MS.wanted_frame);
    if(m_MS.frame)
    av_frame_free(&m_MS.frame);
    if(m_MS.acct)
    avcodec_close(m_MS.acct);
    if(m_MS.afct)
    avformat_close_input(&m_MS.afct);
    if(m_MS.swr_ctx)
    swr_free(&m_MS.swr_ctx);
    if(m_MS.audio_pkt_data)
    av_freep(m_MS.audio_pkt_data);
    if(m_MS.audioq.first_pkt)
    packet_queue_flush(&m_MS.audioq);
    //avcodec_close(m_MS.acct);
    avfilter_graph_free(&m_MS.graph);


    m_MS={0};//自动将能初始化为0的都初始化为0
    //使用memset(m_MS,0,sizeof(m_MS));会出现bug！！
}

AVFilterContext* PlayThread::initFilter(AVFilterGraph *graph,QString filtername,AVDictionary *options_dict)
{
    /*
    int err;
    AVFilterContext* filter_ctx = nullptr;
    //《《音量控制
    const AVFilter* filter = avfilter_get_by_name(filtername.toStdString().c_str());
    if (!filter) {
        fprintf(stderr, "Could not find the volume filter.\n");
        return filter_ctx;
    }
    AVFilterContext* filter_ctx = avfilter_graph_alloc_filter(graph, filter, filtername.toStdString().c_str());
    if (!filter_ctx) {
        fprintf(stderr, "Could not allocate the volume instance.\n");
        return filter_ctx;
    }


    //av_dict_set(&options_dict, "expr", "(0.5*PTS)", 0);
    err = avfilter_init_dict(asetpts_ctx, &options_dict);
    av_dict_free(&options_dict);
    if (err < 0) {
        fprintf(stderr, "Could not initialize the volume filter.\n");
        return filter_ctx;
    }
    return filter_ctx;
    */
}

AVFilterContext *PlayThread::initEqualizerFilter(AVFilterGraph *graph, QString filtername, QJsonObject configObj,QString instanceName)
{
    /*
    AVDictionary *options_dict = nullptr;
    const AVFilter* equalizer = avfilter_get_by_name("equalizer");
    if (!equalizer) {
        fprintf(stderr, "Could not find the volume filter.\n");
        return AVERROR_FILTER_NOT_FOUND;
    }
    AVFilterContext* equalizer_ctx = avfilter_graph_alloc_filter(filter_graph, equalizer64, instanceName);
    if (!equalizer_ctx) {
        fprintf(stderr, "Could not allocate the volume instance.\n");
        return AVERROR(ENOMEM);
    }

    av_dict_set_int(&options_dict, "frequency", configObj.value("frequency"), 0);
    av_dict_set(&options_dict,"width_type","h",0);
    av_dict_set_int(&options_dict,"width",configObj.value("width"),0);
    av_dict_set_int(&options_dict,"gain",configObj.value("gain"),0);
    err = avfilter_init_dict(volume_ctx, &options_dict);
    av_dict_free(&options_dict);
    if (err < 0) {
        fprintf(stderr, "Could not initialize the volume filter.\n");
        return err;
    }
    return equalizer_ctx;
    */
}

int PlayThread::insertFilter(AVFilterGraph *graph,QString filtername,AVDictionary *options_dict)
{
    /*
    AVFilterContext* filtCtx =  avfilter_graph_get_filter(graph,filtername.toStdString().c_str());
    AVFilterLink* link =  volumeCtx->outputs[0];
    int err;
    //《《音量控制

    const AVFilter* filter = avfilter_get_by_name(filtername.toStdString().c_str());
    if (!filter) {
        fprintf(stderr, "Could not find the volume filter.\n");
        return AVERROR_FILTER_NOT_FOUND;
    }
    AVFilterContext* filter_ctx = avfilter_graph_alloc_filter(this->m_MS.graph, asetpts, "setpts");
    if (!asetpts_ctx) {
        fprintf(stderr, "Could not allocate the volume instance.\n");
        return AVERROR(ENOMEM);
    }

    av_dict_set(&options_dict, "expr", "(0.5*PTS)", 0);
    err = avfilter_init_dict(asetpts_ctx, &options_dict);
    av_dict_free(&options_dict);
    if (err < 0) {
        fprintf(stderr, "Could not initialize the volume filter.\n");
        return err;
    }

    avfilter_insert_filter(link,asetpts_ctx,0,0);
    qDebug()<<"插入完毕";
    */
}


PlayThread::PlayThread(QObject *parent) : QThread(parent)
{
    av_register_all();
    avformat_network_init();
    m_MS={0};//自动将能初始化为0的都初始化为0
    //使用memset(m_MS,0,sizeof(m_MS));会出现bug！！

    init();
              //初始化图
}

void PlayThread::init()
{
    this->m_MS.playThread = this;

    this->__volume = 100;

    this->initFilterConfigObj();

}

void PlayThread::initFilterConfigObj(){



    //QJsonObject EqualizerObj;
    /*
     * {
     * "Equalizer":[{"instance_name":"Equalizer35","width":1,......},{}]
     * "volume":[{}]
     * }
     *
     *
     */
    QJsonArray equalizerArray;
    for(int i =0;i<EQUALIZER_FILTER_COUNT;i++){
        QJsonObject eqObj;
        QJsonValue freq(equalizer_freqs[i]);
        QJsonValue width_type("h");
        QJsonValue width(100);
        QJsonValue gain(-12);
        eqObj.insert(equalizer_config_name[0],freq);
        eqObj.insert(equalizer_config_name[1],width_type);
        eqObj.insert(equalizer_config_name[2],width);
        eqObj.insert(equalizer_config_name[3],gain);
        eqObj.insert(equalizer_config_name[4],Equalizer_instance_name[i]);

        equalizerArray.append(eqObj);
    }

    this->__filtersConfigs.insert(FILTER_EQUALIZER_NAME,equalizerArray);

}

void PlayThread::setMedia(const QString url)
{
    stop();
    m_url=url;
    //start();
    setPriority(QThread::HighestPriority);
    isquit=0;
    this->initMediaEnv(m_url);

}

int PlayThread::initMediaEnv(const QString)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
    // 读取文件头，将格式相关信息存放在AVFormatContext结构体中
    if (avformat_open_input(&m_MS.afct, m_url.toUtf8().data(), nullptr, nullptr) != 0)
    {
      FreeAllocSpace();
      return -1; // 打开失败
    }

    // 检测文件的流信息
    if (avformat_find_stream_info(m_MS.afct, nullptr) < 0)
    {
      FreeAllocSpace();
      return -1; // 没有检测到流信息 stream infomation
    }

    AVCodec* pCodec;

    int ret = av_find_best_stream(m_MS.afct, AVMEDIA_TYPE_AUDIO, -1, -1, &pCodec, 0);
    if (ret < 0) {
      __hasTrouble = true;
      av_log(NULL, AV_LOG_ERROR, "Cannot find an audio stream in the input file\n");
      return ret;
    }
    this->m_MS.curStreamIndex  = ret;

    m_MS.acct = m_MS.afct->streams[ret]->codec; // codec context

    //获取时长
    //this->setDuration(qint64(double(m_MS.afct->duration)*av_q2d( m_MS.afct->streams[i]->time_base)));

    qDebug()<<"duration:  "<<double(m_MS.afct->duration)/ AV_TIME_BASE;
    qint64 duration = 1000*m_MS.afct->duration/ AV_TIME_BASE;
    this->setDuration(duration);
    if (!pCodec)
    {
        cout << "Unsupported codec!" << endl;
        FreeAllocSpace();
        this->__hasTrouble = true;
        return -1;
    }

    //wanted_spec:想要打开的 //spec: 实际打开的,可以不用这个，
    //函数中直接用NULL，下面用到spec的用wanted_spec代替。
     //这里会开一个线程，调用callback。
    //SDL_OpenAudio->open_audio_device(开线程)->SDL_RunAudio->fill(指向callback函数）
    //可以用SDL_OpenAudioDevice()代替


    // Set audio settings from codec info

    __wanted_spec.freq = m_MS.acct->sample_rate;   //采样率
    __wanted_spec.format = AUDIO_F32SYS;       //audio format
    __wanted_spec.channels = 2;//m_MS.acct->channels;
    __wanted_spec.silence = 0;
    __wanted_spec.samples = SDL_AUDIO_BUFFER_SIZE;
    __wanted_spec.callback = audio_callback;   //类外面
    __wanted_spec.userdata = &m_MS;
    //打开设备
    // CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (SDL_OpenAudio(&__wanted_spec, &__spec) < 0)
    {
        cout << "Open audio failed:" << SDL_GetError() << endl;
        FreeAllocSpace();
        return -1;
    }
    m_MS.wanted_frame=av_frame_alloc();
    m_MS.frame=av_frame_alloc();

    //设置参数，供重采样时候用, swr_alloc_set_opts的in部分参数
    //不知道格式
    m_MS.wanted_frame->format = AV_SAMPLE_FMT_FLT;
    m_MS.wanted_frame->sample_rate = __spec.freq;
    qDebug()<<"sample_rate:"<<__spec.freq;
    m_MS.wanted_frame->channel_layout = av_get_default_channel_layout(__spec.channels);
    m_MS.wanted_frame->channels = 2;

    qDebug()<<"m_MS.wanted_frame->channels:"<<m_MS.wanted_frame->channels;
    //打开编码上下文
    avcodec_open2(m_MS.acct, pCodec, nullptr);


    //初始化图
    this->initFilterGraph(&m_MS.graph,&m_MS.src,&m_MS.sink,m_MS.acct);


    //初始化队列
    packet_queue_init(&m_MS.audioq);
    //打开设备
    SDL_PauseAudio(0);
}


void PlayThread::clearCache()
{
    this->m_MS.audio_buf_index = 0;
    this->m_MS.audio_buf_size = 0;
    this->m_MS.audio_pkt_data = 0;
    this->m_MS.audio_pkt_size = 0;
}

void PlayThread::stop()
{
    isquit=1;
    m_url="";
    //Sleep(100);//等待退出线程
}

void PlayThread::pause()
{
    SDL_PauseAudio(1);
}

void PlayThread::play()
{
    SDL_PauseAudio(0);
}

void PlayThread::setPosition(qint64 position)
{
    this->__position = (qint64)position;
    emit positionChanged(__position);
    //qDebug()<<this->__position;
    //改变当前的寻址

}


void PlayThread::setVolume(int volume)
{
    this->__volume  = volume;
    emit volumeChanged(__volume);
}

void PlayThread::changeCurPosition(qint64 position)
{
    this->__position =     (qint64)position;
    //qDebug()<<this->__position;
    //改变当前的寻址
    int64_t timestamp = (position/100)*AV_TIME_BASE;
    this->pause();
    this->clearCache();
    packet_queue_flush(&this->m_MS.audioq);
    qDebug()<<"timestamp"<<timestamp;
    av_seek_frame(this->m_MS.afct,this->m_MS.curStreamIndex,timestamp,AVSEEK_FLAG_ANY);
    this->play();
}

QJsonObject PlayThread::getFiltersConfigs() const
{
    return __filtersConfigs;
}

void PlayThread::setFiltersConfigs(const QJsonObject &filtersConfigs)
{
    __filtersConfigs = filtersConfigs;
}

int PlayThread::getVolume() const
{
    return __volume;
}


qint64 PlayThread::getPosition() const
{
    return __position;
}

/*
void PlayThread::audio_callback(void *userdata, Uint8 *stream, int len)
{
    mediaState* MS = (mediaState*)userdata;
    int len1, audio_size;
    SDL_memset(stream, 0, len);
    qDebug()<<"调用一次callback";
    if (isquit)
        return;
    while (len > 0)
    {
        //audio_buff 保存一次的数据
       //buff一定要*2以上，如果小了就会在memcpy的时候变小！
         uint8_t audio_buff[MAX_AUDIO_FRAME_SIZE*2];

        if (MS->audio_buf_index >= MS->audio_buf_size)
        {
            //index >= size 则重新获取数据
            //数据全部发送 ，再去获取数据
            //解码
            audio_size = audio_decode_frame(MS, audio_buff, sizeof(audio_buff));



            qDebug()<<"audio_size:"<<audio_size;
            if (isquit)
                return;
            if (audio_size < 0){
                //错误则静音
                MS->audio_buf_size = 1024;
                SDL_memset(audio_buff, 0, MS->audio_buf_size);
            }else{
                //每次读取成功会设置当前的size
                MS->audio_buf_size = audio_size;

            }
            //回到缓冲区开头
            MS->audio_buf_index = 0;
        }

        //剩余的数据
        len1 = MS->audio_buf_size - MS->audio_buf_index;
        qDebug()<<"len1:"<<len1<<" len: "<<len;
        //len1常比len大，但是一个callback只能发len个
        if (len1 > len)
            len1 = len;
        //每次传输 len长度的数据  从buff开头 +index
        //SDL_MixAudio(stream, (uint8_t*)audio_buff + MS->audio_buf_index, len1, SDL_MIX_MAXVOLUME);
        memcpy(stream, (uint8_t *)audio_buff + MS->audio_buf_index, len1);
        //改变stream的位置
        //如果len>len1  则index 肯定小于size  此时 len 还有空间
        len -= len1;
        stream += len1;
        MS->audio_buf_index += len1;//这个就代表的当前位置
        qDebug()<<"index:"<<MS->audio_buf_index<<"  len:"<<len<<" size:"<<MS->audio_buf_size;
        //qDebug()<<MS->audio_buf_index;
    }
}

*/
qint64 PlayThread::getDuration() const
{
    return __duration;
}

void PlayThread::setDuration(const qint64 &duration)
{
    __duration = duration;
    emit durationChanged(__duration);
    qDebug()<<"总长度"<<this->__duration;
}

playerStatus PlayThread::getPlayerStatus()
{
    if(SDL_AUDIO_PAUSED==SDL_GetAudioStatus())
        return pausing;
    if(SDL_AUDIO_PLAYING==SDL_GetAudioStatus())
        return playing;
    return stopping;
}

QJsonObject PlayThread::getConfigObjByInstanceName(QString filtername,QString instanceName)
{
    QJsonArray eqArray = this->__filtersConfigs.value(filtername).toArray();
    for(int j =0;j<eqArray.size();j++){

        QJsonObject eqObj = eqArray.at(j).toObject();
        QString key_name = equalizer_config_name[4];
        if(eqObj.contains(key_name)){
            if(eqObj.value(key_name).toString() == instanceName){
                return eqObj;
            }
        }
    }

    return QJsonObject();
}

int PlayThread::initFilterGraph()
{
    this->initFilterGraph(&this->m_MS.graph,&this->m_MS.src,&this->m_MS.sink,this->m_MS.acct);
}

int PlayThread::initFilterGraph(AVFilterGraph **graph, AVFilterContext **src, AVFilterContext **sink, AVCodecContext *pCodecCtx)
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
    volume_ctx = avfilter_graph_alloc_filter(filter_graph, volume, "volume");
    this->__volumeFilterCtx = volume_ctx;
    if (!volume_ctx) {
        fprintf(stderr, "Could not allocate the volume instance.\n");
        return AVERROR(ENOMEM);
    }
    /* A different way of passing the options is as key/value pairs in a
     * dictionary. */
    av_dict_set_int(&options_dict, "volume", this->__volume, 0);
    err = avfilter_init_dict(volume_ctx, &options_dict);
    av_dict_free(&options_dict);
    if (err < 0) {
        fprintf(stderr, "Could not initialize the volume filter.\n");
        return err;
    }

    /*

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
    */

    for(int i =0;i< EQUALIZER_FILTER_COUNT;i++){
        const AVFilter* equalizer = avfilter_get_by_name(FILTER_EQUALIZER_NAME.toStdString().c_str());
        if(!equalizer){
            fprintf(stderr, "Could not find the volume filter.\n");
            return AVERROR_FILTER_NOT_FOUND;
        }
        AVFilterContext* equalizer_ctx = avfilter_graph_alloc_filter(filter_graph, equalizer, Equalizer_instance_name[i].toStdString().c_str());
        if (!equalizer_ctx) {
            fprintf(stderr, "Could not allocate the volume instance.\n");
            return AVERROR(ENOMEM);
        }

        QJsonObject objConfig = this->getConfigObjByInstanceName(FILTER_EQUALIZER_NAME,Equalizer_instance_name[i]);
        /* A different way of passing the options is as key/value pairs in a
         * dictionary. */

        //for(int i=0;i<objConfig.keys().size();i++)

        av_dict_set_int(&options_dict, equalizer_config_name[0].toStdString().c_str(), objConfig.value(equalizer_config_name[0]).toInt(), 0);
        av_dict_set(&options_dict,equalizer_config_name[1].toStdString().c_str(),"h",0);
        av_dict_set_int(&options_dict,equalizer_config_name[2].toStdString().c_str(),objConfig.value(equalizer_config_name[2]).toInt(),0);
        av_dict_set_int(&options_dict,equalizer_config_name[3].toStdString().c_str(),objConfig.value(equalizer_config_name[3]).toInt(),0);
        err = avfilter_init_dict(equalizer_ctx, &options_dict);
        av_dict_free(&options_dict);
        if (err < 0) {
            fprintf(stderr, "Could not initialize the volume filter.\n");
            return err;
        }
        this->__equalizerFilterCtxs.append(equalizer_ctx);
    }

    //从一个obj中分解出所有的



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
    for(int i = 0;i<this->__equalizerFilterCtxs.size();i++){
        err = avfilter_link(pre,0,__equalizerFilterCtxs.at(i),0);
        pre = __equalizerFilterCtxs.at(i);
    }

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


void PlayThread::updateFilterGraph(const QJsonObject& obj)
{
    this->pause();
    //avfilter_graph_get_filter()
    //this->initFilterGraph(&m_MS.graph,&m_MS.src,&m_MS.sink,m_MS.acct);
    //AVDictionary* options_dict = nullptr;
    //av_dict_set_int(&options_dict, "volume", 5, 0);
    //avfilter_init_dict(this->__volumeFilterCtx,&options_dict);
    //avfilter_graph_free(&m_MS.graph);
    //this->__equalizerFilterCtxs.clear();
    //this->__volume = 2;
    this->__equalizerFilterCtxs.clear();
    this->setFiltersConfigs(obj);
    this->initFilterGraph();
    this->play();
}

int PlayThread::addFilters(QList<AVFilterContext *> filters)
{

}


void PlayThread::run()
{

    AVPacket packet;
    while (true) //这里有一个顺序！先判断退出线程信号~再 读 再写入
    {
        SDL_Delay(10);
        if (isquit)
        {
            __wanted_spec.callback=NULL;
            __wanted_spec.userdata=NULL;
            break;
        }

        if (m_MS.audioq.size > MAX_AUDIO_SIZE )//防止一下子把音频全部读完了~
            continue;
        if(av_read_frame(m_MS.afct, &packet)==0)//=0就是正确的~再添加进队列
        {

            /*
            avcodec_send_packet(m_MS.acct,&packet);
            while(avcodec_receive_frame(m_MS.acct,m_MS.frame)==0) {
                int data_size = av_samples_get_buffer_size(NULL,
                                     m_MS.acct->channels,
                                     m_MS.frame->nb_samples,
                                     m_MS.acct->sample_fmt,
                                     1);

                qDebug()<<m_MS.frame->extended_data[0][0];

                //streamOut->write((const char*)m_MS.frame->extended_data[0],data_size);
            }
            */
            qDebug()<<"packet pts:"<<packet.pts;
            if (packet.stream_index == m_MS.curStreamIndex){
                packet_queue_put(&m_MS.audioq, &packet);
            }
            else
                av_free_packet(&packet);

        }

    }
    FreeAllocSpace();
}

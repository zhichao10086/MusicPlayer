#include "audiorecord.h"

AudioRecord::AudioRecord()
{
    this->init();
}

AudioRecord::AudioRecord(QString filename)
{
    this->filename = filename;

    this->init();
}

AudioRecord::~AudioRecord()
{

}

void AudioRecord::init()
{
    this->rawFile  = new QFile(filename + ".raw");
    this->wavFile = new QFile(filename + ".wav");
    this->rawFile->open(QIODevice::Append |QIODevice::ReadWrite);
    this->wavFile->open(QIODevice::Append|QIODevice::ReadWrite);
    this->status = recordStatus::stopped;

    QAudioDeviceInfo audioDeviceInfo = QAudioDeviceInfo::defaultInputDevice();
    // 判断本地是否有录音设备;
    if (!audioDeviceInfo.isNull())
    {
        //m_isRecord = true;
        //this->rawFile.setFileName(RAW_RECORD_FILENAME);
        //destinationFile.open(QIODevice::WriteOnly | QIODevice::Truncate);

        // 设置音频文件格式;
        //QAudioFormat format;
        // 设置采样频率;
        format.setSampleRate(44100);
        // 设置通道数;
        format.setChannelCount(2);
        // 设置每次采样得到的样本数据位值;
        format.setSampleSize(16);
        // 设置编码方法;
        format.setCodec("audio/pcm");
        // 设置采样字节存储顺序;
        format.setByteOrder(QAudioFormat::LittleEndian);
        // 设置采样类型;
        format.setSampleType(QAudioFormat::Unknown);

        // 判断当前设备设置是否支持该音频格式;
        if (!audioDeviceInfo.isFormatSupported(format))
        {
            qDebug() << "Default format not supported, trying to use the nearest.";
            format = audioDeviceInfo.nearestFormat(format);
        }
        // 开始录音;
        m_audioInput = new QAudioInput(format);


    }

}



void AudioRecord::recordStart()
{
    if(this->status ==pause){
        //暂停
        m_audioInput = new  QAudioInput();
        m_audioInput->start(this->rawFile);
        this->status = recording;
    }else if(this->status == stopped){
        m_audioInput->start(this->rawFile);
        this->status = recording;
    }
}

void AudioRecord::recordStop()
{
    if(this->status != stopped){
        this->m_audioInput->stop();
        //this->rawFile->close();
        delete this->m_audioInput;
        this->addWavHeader(this->filename + ".raw",this->filename + ".wav");
        this->wavFile->write(this->rawFile->readAll());
        this->rawFile->close();
        this->wavFile->close();
        this->status = stopped;
    }

}

void AudioRecord::recordPause()
{
    if(this->status == recording){
        this->m_audioInput->stop();
        delete this->m_audioInput;
        this->status = pause;
    }

}

QString AudioRecord::getFilename() const
{
    return filename;
}

void AudioRecord::setFilename(const QString &value)
{
    filename = value;
}

AudioRecord::recordStatus AudioRecord::getStatus() const
{
    return this->status;
}

void AudioRecord::setStatus(AudioRecord::recordStatus &value)
{

}




// 将生成的.raw文件转成.wav格式文件;
qint64 AudioRecord::addWavHeader(QString catheFileName , QString wavFileName)
{
    // 开始设置WAV的文件头
    // 这里具体的数据代表什么含义请看上一篇文章（Qt之WAV文件解析）中对wav文件头的介绍
    WAVFILEHEADER WavFileHeader;
    qstrcpy(WavFileHeader.RiffName, "RIFF");
    qstrcpy(WavFileHeader.WavName, "WAVE");
    qstrcpy(WavFileHeader.FmtName, "fmt ");
    qstrcpy(WavFileHeader.DATANAME, "data");

    // 表示 FMT块 的长度
    WavFileHeader.nFmtLength = 16;
    // 表示 按照PCM 编码;
    WavFileHeader.nAudioFormat = 1;
    // 声道数目;
    WavFileHeader.nChannleNumber = 1;
    // 采样频率;
    WavFileHeader.nSampleRate = 44100;

    // nBytesPerSample 和 nBytesPerSecond这两个值通过设置的参数计算得到;
    // 数据块对齐单位(每个采样需要的字节数 = 通道数 × 每次采样得到的样本数据位数 / 8 )
    WavFileHeader.nBytesPerSample = 2;
    // 波形数据传输速率
    // (每秒平均字节数 = 采样频率 × 通道数 × 每次采样得到的样本数据位数 / 8  = 采样频率 × 每个采样需要的字节数 )
    WavFileHeader.nBytesPerSecond = 88200;

    // 每次采样得到的样本数据位数;
    WavFileHeader.nBitsPerSample = 16;

    QFile cacheFile(catheFileName);
    QFile wavFile(wavFileName);

    if (!cacheFile.open(QIODevice::ReadWrite))
    {
        return -1;
    }
    if (!wavFile.open(QIODevice::WriteOnly))
    {
        return -2;
    }

    int nSize = sizeof(WavFileHeader);
    qint64 nFileLen = cacheFile.bytesAvailable();

    WavFileHeader.nRiffLength = nFileLen - 8 + nSize;
    WavFileHeader.nDataLength = nFileLen;

    // 先将wav文件头信息写入，再将音频数据写入;
    wavFile.write((char *)&WavFileHeader, nSize);
    wavFile.write(cacheFile.readAll());

    cacheFile.close();
    wavFile.close();

    return nFileLen;
}

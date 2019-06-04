#ifndef AUDIORECORD_H
#define AUDIORECORD_H


#include <QObject>
#include <QThread>
#include <QString>
#include <QFile>

#include <QAudioRecorder>
#include <QAudioDeviceInfo>
#include <QAudioInput>

struct WAVFILEHEADER
{
    // RIFF 头
    char RiffName[4];
    unsigned long nRiffLength;

    // 数据类型标识符
    char WavName[4];

    // 格式块中的块头
    char FmtName[4];
    unsigned long nFmtLength;

    // 格式块中的块数据
    unsigned short nAudioFormat;
    unsigned short nChannleNumber;
    unsigned long nSampleRate;
    unsigned long nBytesPerSecond;
    unsigned short nBytesPerSample;
    unsigned short nBitsPerSample;

    // 数据块中的块头
    char    DATANAME[4];
    unsigned long   nDataLength;
};


class AudioRecord : public QObject
{
    Q_OBJECT
public:
    AudioRecord();

    AudioRecord(QString filename);

    ~AudioRecord();


    enum recordStatus{
        recording,
        pause,
        stopped,
    };

    void init();

    recordStatus status;


    QString filename;

    QFile* rawFile;
    QFile* wavFile;

    QAudioFormat format;

    QAudioInput* m_audioInput;


    void recordStart();
    void recordStop();
    void recordPause();//暂停


   qint64 addWavHeader(QString catheFileName , QString wavFileName);


    QString getFilename() const;
    void setFilename(const QString &value);




     recordStatus getStatus()const;
    void setStatus( recordStatus &value);

signals:
    void finish(int);
public slots:


};



#endif // AUDIORECORD_H

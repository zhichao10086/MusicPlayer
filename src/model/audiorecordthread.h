#ifndef AUDIORECORDTHREAD_H
#define AUDIORECORDTHREAD_H

#include <QObject>
#include <QThread>
#include <QString>
#include <QFile>

#include <QAudioRecorder>
#include <QAudioDeviceInfo>




class AudioRecordThread : public QObject
{
    Q_OBJECT
public:
    AudioRecordThread();

    AudioRecordThread(QString filename);

    ~AudioRecordThread();




signals:
    void finish(int);
public slots:


};

#endif // AUDIORECORDTHREAD_H

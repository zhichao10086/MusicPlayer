#ifndef AUDIORECORDVIEW_H
#define AUDIORECORDVIEW_H

#include <QWidget>
#include "multimusicfunc.h"
#include <QStringList>
#include <QDebug>
#include "audiorecord.h"
#include "playthread.h"


namespace Ui {
class AudioRecordView;
}

class AudioRecordView : public QWidget
{
    Q_OBJECT

public:
    explicit AudioRecordView(QWidget *parent = 0);
    ~AudioRecordView();


    static AudioRecordView* single_audioRecordView;
    static AudioRecordView* newInstance();


    enum recordStatus{
        Playing,
        Recording,
        Stopped,
    };

    recordStatus _curStatus;

    QString filename;
    void init();


private slots:
    void on_btnRecord_clicked();

    void on_btnPlay_clicked();

    void on_btnFinishRecord_clicked();

private:
    Ui::AudioRecordView *ui;

    AudioRecord* __record;
    PlayThread* __playThread;
};

#endif // AUDIORECORDVIEW_H

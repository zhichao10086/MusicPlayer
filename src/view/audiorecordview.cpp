#include "audiorecordview.h"
#include "ui_audiorecordview.h"

AudioRecordView* AudioRecordView::single_audioRecordView = nullptr;

AudioRecordView::AudioRecordView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudioRecordView)
{
    ui->setupUi(this);
    this->filename = "./record/record01";
    this->init();
}

AudioRecordView::~AudioRecordView()
{
    delete ui;
}

AudioRecordView *AudioRecordView::newInstance()
{
    if(single_audioRecordView!= nullptr)
        return single_audioRecordView;

    single_audioRecordView = new AudioRecordView;
    return single_audioRecordView;
}

void AudioRecordView::init()
{
    this->_curStatus = recordStatus::Stopped;
    this->__record = new AudioRecord(this->filename);
}

void AudioRecordView::on_btnRecord_clicked()
{

    if(AudioRecord::recording != this->__record->getStatus()){
        this->__record->recordStart();
        this->ui->btnRecord->setText("停止");
        return;
    }

    this->__record->recordPause();
    this->ui->btnRecord->setText("录音");


}

void AudioRecordView::on_btnPlay_clicked()
{
    if(this->__record->getStatus() == AudioRecord::stopped){

        this->__playThread->setMedia(filename+".wav");
        this->__playThread->start();
        this->ui->btnPlay->setText("停止");
    }else{
        this->__playThread->stop();

        this->ui->btnPlay->setText("播放");
    }
}

void AudioRecordView::on_btnFinishRecord_clicked()
{
    this->__record->recordStop();
}

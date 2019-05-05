#include "musiccutview.h"
#include "ui_musiccutview.h"

MusicCutView::MusicCutView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicCutView)
{
    ui->setupUi(this);
    initView();
}

MusicCutView::~MusicCutView()
{
    delete ui;
}

void MusicCutView::initView()
{
    this->ui->leInFileName->setPlaceholderText("音乐文件绝对路径");
    this->ui->leOutputPath->setPlaceholderText("输出目录");
    this->ui->leStartTime->setPlaceholderText("00.000(秒.毫秒)");
    this->ui->leEndTime->setPlaceholderText("00.000(秒.毫秒)");
    this->ui->leOutputFilename->setPlaceholderText("请与输入文件后缀保持一致");
}

void MusicCutView::showMessage(int ret)
{
    if(ret >=0){
        QMessageBox::about(this,"提示","剪辑成功");
    }else{
        QMessageBox::about(this,"提示","剪辑失败");
    }
}

void MusicCutView::on_btnOpenFile_clicked()
{

    QString filename = QFileDialog::getOpenFileName(this,tr("选择音乐文件"),tr("../"),tr("*.mp3;*.wav;*.ape;*flac;*.ogg;*.wv;*.wma"));
    if(!filename.isEmpty()){

        this->ui->leInFileName->setText(filename);
    }
}

void MusicCutView::on_btnOpenOutputPath_clicked()
{
    QString outputFilePath = QFileDialog::getExistingDirectory(this,tr("选择输出目录"),"../");
    if(!outputFilePath.isEmpty()){
        this->ui->leOutputPath->setText(outputFilePath);
    }
}



void MusicCutView::on_btnStart_clicked()
{

    QString inFilename = this->ui->leInFileName->text();
    QString outputFilename = this->ui->leOutputFilename->text();
    QString outputFilepath = this->ui->leOutputPath->text();
    QString startTime = this->ui->leStartTime->text();
    QString endTime = this->ui->leEndTime->text();

    if(inFilename.isEmpty()){
        QMessageBox::about(this,"提示","输入文件为空");
        return;
    }

    if(outputFilename.isEmpty()){
        QMessageBox::about(this,"提示","输出文件名为空");
        return;
    }
    if(outputFilepath.isEmpty()){
        QMessageBox::about(this,"提示","输出文件目录为空");
        return;
        }
    bool ok ;
    double start = (double)startTime.toFloat(&ok);
    if(!ok){
        QMessageBox::about(this,"提示","时间格式有误，应该为00.000(秒.毫秒)");
        return;
    }
    double end = (double)endTime.toFloat(&ok);
    if(!(ok)){
        QMessageBox::about(this,"提示","时间格式有误，应该为00.000(秒.毫秒)");
        return;
    }

    QString output = outputFilepath + "/" + outputFilename;

    qDebug()<<output;
    MusicCutThread *thread = new MusicCutThread(start,end,inFilename,output);
    QObject::connect(thread,&MusicCutThread::finish,this,&MusicCutView::showMessage);
    thread->start();
    thread->wait();

}

#include "playfuncview.h"
#include "ui_playfuncview.h"

PlayFuncView::PlayFuncView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayFuncView)
{
    ui->setupUi(this);
    init();
}

PlayFuncView::PlayFuncView(PlayFuncController *pfc, QWidget *parent):
    QWidget(parent)
{
    //this->PlayFuncView(parent);
    this->_playFuncController = pfc;
    this->init_view();

}

PlayFuncView::~PlayFuncView()
{
    delete ui;
}

void PlayFuncView::init()
{

}

void PlayFuncView::init_view()
{
    ui = new Ui::PlayFuncView;
    ui->setupUi(this);

    //播放器音量 0-100
    this->getVolumeSlider()->setRange(0,100);

    /*
     * connect 槽
     */


}

void PlayFuncView::setStartView()
{
    this->ui->btnStartOrPause->setStyleSheet(tr("border-image: url(:/images/icon/images/play_1296db.png);"));
}

void PlayFuncView::setPauseView()
{
    //设置停止界面

    this->ui->btnStartOrPause->setStyleSheet(tr("border-image: url(:/images/icon/images/pause_1296db.png);"));
}

void PlayFuncView::setBackgroundImage(QPixmap &p)
{
//    QLabel label = new QLabel(this);
//    label.setGeometry(0,0,this->width(),this->height());
    //    label->setPixmap(p.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

QLabel *PlayFuncView::getLabelTime()
{
    return this->ui->lbTime;
}

QSlider *PlayFuncView::getTimeSlider()
{
    return this->ui->timeSlider;
}

QSlider *PlayFuncView::getVolumeSlider()
{
    return this->ui->volumeSlider;
}

void PlayFuncView::connectTimeAndSlider(QMediaPlayer *mp)
{

}

void PlayFuncView::showCurDuration(qint64 all)
{
    this->ui->lbTime->setText(Util::qint642Qtring(all));
}

void PlayFuncView::showCurPosition(qint64 cur)
{
    this->ui->labCurTIme->setText(Util::qint642Qtring(cur));
}

void PlayFuncView::setTimeSLiderRange(qint64 all)
{
    this->ui->timeSlider->setRange(0,all);
}

void PlayFuncView::setTimeSliderPosition(qint64 position)
{
    this->ui->timeSlider->setValue(position);
}

void PlayFuncView::on_btnStartOrPause_clicked()
{
    this->_playFuncController->playOrPause();
}

void PlayFuncView::on_btnNext_clicked()
{
    this->_playFuncController->next();
}

void PlayFuncView::on_btnPre_clicked()
{
    this->_playFuncController->pre();
}

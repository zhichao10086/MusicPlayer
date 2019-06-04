#include "playfuncview.h"
#include "ui_playfuncview.h"

PlayFuncView::PlayFuncView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayFuncView)
{
    this->init_view();
}

PlayFuncView::PlayFuncView(PlayFuncController *pfc, QWidget *parent):
    QWidget(parent),
    ui(new Ui::PlayFuncView)
{
    //this->PlayFuncView(parent);
    this->_playFuncController = pfc;
    this->init_view();

}

PlayFuncView::~PlayFuncView()
{
    delete ui;
}

bool PlayFuncView::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this->ui->timeSlider){
        if(event->type() == QEvent::MouseButtonRelease){
            //进度滑动条的拖动事件
            QMouseEvent *mouseEvent = (QMouseEvent *)event;
            if(mouseEvent->button() == Qt::LeftButton){
                int value = ui->timeSlider->value();
                qDebug()<<"filter"<<value;
                emit this->customSliderMoved(value*1000);
                return true;
            }
        }

    }/*else if(watched == this->ui->btnPlaySheet){
        if(event->type() == QEvent::MouseButtonPress){
            //播放按钮的点击显示播放列表
            QMouseEvent *mouseEvent = (QMouseEvent *)event;
            if(mouseEvent->button() == Qt::LeftButton){
                if(!this->_playFuncController->getPlaySheetView()->isHidden()){
                    cout<<"111111111111"<<endl;
                    return true;
                }

            }
        }

    }*/

    return QWidget::eventFilter(watched, event);
}

void PlayFuncView::init()
{

}

void PlayFuncView::init_view()
{

    ui->setupUi(this);

    //播放器音量 0-100
    this->getVolumeSlider()->setRange(0,100);
    this->ui->timeSlider->installEventFilter(this);
    this->ui->btnPlaySheet->installEventFilter(this);
    /*
     * connect 播放顺序
     */

    QObject::connect(this->ui->btnPlayMode,&QMenuButton::changePlayBackMode,
                     this->_playFuncController,&PlayFuncController::setMusicListMode);
}

void PlayFuncView::setStartView()
{
    //this->ui->btnStartOrPause->setStyleSheet(tr("border-image: url(:/images/icon/images/play_1296db.png);"));
    this->ui->btnStartOrPause->setStyleSheet("QPushButton{	\
                                             border-image: url(:/images/icon/images/播放(7).png);\
                                         }\
                                         QPushButton:hover{\
                                             border-image: url(:/images/icon/images/播放(6).png);\
                                         }");
}

void PlayFuncView::setPauseView()
{
    //设置停止界面

    //this->ui->btnStartOrPause->setStyleSheet(tr("border-image: url(:/images/icon/images/pause_1296db.png);"));

    this->ui->btnStartOrPause->setStyleSheet("QPushButton{	\
                                             border-image: url(:/images/icon/images/暂停.png);\
                                         }\
                                         QPushButton:hover{\
                                             border-image: url(:/images/icon/images/暂停(1).png);\
                                         }");

}

void PlayFuncView::setBackgroundImage(QPixmap &p)
{
//    QLabel label = new QLabel(this);
//    label.setGeometry(0,0,this->width(),this->height());
    //    label->setPixmap(p.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void PlayFuncView::setVolume(int value)
{
    this->ui->volumeSlider->setValue(value);
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



void PlayFuncView::showCurDuration(qint64 all)
{
    this->ui->lbTime->setText(Util::qint642QStringMinSec(all));
}

void PlayFuncView::showCurPosition(qint64 cur)
{
    this->ui->labCurTIme->setText(Util::qint642QStringMinSec(cur));
}

void PlayFuncView::setTimeSLiderRange(qint64 all)
{
    //qDebug()<<all/1000;
    this->ui->timeSlider->setRange(0,(int)(all/1000));
}

void PlayFuncView::setTimeSliderPosition(qint64 position)
{
    int lastValue = this->ui->timeSlider->value();
    int curValue = (int)(position/1000);
    //qDebug()<<lastValue<<" "<<curValue;
    if (lastValue != curValue)
        this->ui->timeSlider->setValue(curValue);
}

void PlayFuncView::setMusicImageThumbnail(QPixmap &p)
{
    this->ui->btnMusicDetial->setText("");
    this->ui->btnMusicDetial->setAutoFillBackground(true);
    //设置背景
    QPixmap p1 = p.scaled(this->ui->btnMusicDetial->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    QPalette pal;
    pal.setBrush(QPalette::Button,QBrush(p1));
    this->ui->btnMusicDetial->setPalette(pal);
    //QSize size = this->ui->btnMusicDetial->size();
    //this->ui->btnMusicDetial->setIconSize(size);
    //this->ui->btnMusicDetial->setIcon(QIcon(p.scaled(size)));
    //this->ui->btnMusicDetial->setPalette(pal);
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

void PlayFuncView::on_btnPlaySheet_clicked()
{

    PlaySheetView* psv = this->_playFuncController->getPlaySheetView();

    //psv->setParent(this->_playFuncController->getMusicPlayerView());
    if(psv->isHidden()){
        //QDesktopWidget* desktopWidget = QApplication::desktop();
        QPoint funcViewGlobalPos = QWidget::mapToGlobal(this->_playFuncController->getMusicPlayerViewPos());
        //qDebug()<<psv->size()<<" "<<funcViewGlobalPos;
        //QPoint mianwindowPos() =
        //QPoint funcViewGlobalPos =this->pos();
        int x = funcViewGlobalPos.x() + (this->size().width() - psv->size().width());
        int y = funcViewGlobalPos.y() - psv->size().height();
        //qDebug()<<this->pos().x()<<" "<<this->pos().y()<<x<<"  "<<y;
        psv->move(x,y);
        psv->show();
        //psv->updateListWidgetPlaySheet(this->_playFuncController->playFuncModel()->curMusicSheet());

        cout<<"dianji1"<<endl;
    }else{
        psv->hide();
    }

    //psv->setIsFilter(false);


}

void PlayFuncView::on_btnMusicDetial_clicked()
{
    //打开当前播放音乐的详细内容
    this->_playFuncController->showDetialMusicView();
}

void PlayFuncView::on_btnPlayMode_clicked()
{
    this->ui->btnPlayMode->popupMenu();

}

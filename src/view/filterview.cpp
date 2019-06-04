#include "filterview.h"
#include "ui_filterview.h"


FilterView* FilterView::single_filterView=nullptr;


FilterView::FilterView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FilterView)
{
    ui->setupUi(this);
    this->initView();

}

FilterView *FilterView::newInstance()
{
    if(single_filterView!=nullptr)
        return single_filterView;
    single_filterView = new FilterView;
    return single_filterView;
}

FilterView::~FilterView()
{
    delete ui;
}

QJsonObject FilterView::getFiltersValue()
{

}

QJsonObject FilterView::getFreqFiltersValue()
{

}

void FilterView::initView()
{
    this->ui->timeSlider->installEventFilter(this);
    this->__playThread = new PlayThread;
    __filterConfigObj = this->__playThread->getFiltersConfigs();

    //初始化频率slider
    this->__freqSliders.append(this->ui->vslider32  );
    this->__freqSliders.append(this->ui->vslider64  );
    this->__freqSliders.append(this->ui->vslider125 );
    this->__freqSliders.append(this->ui->vslider250 );
    this->__freqSliders.append(this->ui->vslider500 );
    this->__freqSliders.append(this->ui->vslider1K  );
    this->__freqSliders.append(this->ui->vslider2K  );
    this->__freqSliders.append(this->ui->vslider4K  );
    this->__freqSliders.append(this->ui->vslider8K  );
    this->__freqSliders.append(this->ui->vslider16K );


    for(int i=0;i<this->__freqSliders.size();i++){
        this->__freqSliders.at(i)->setMinimum(-50);
        this->__freqSliders.at(i)->setMaximum(50);
    }

    QObject::connect(this->ui->vslider32,&QSlider::valueChanged,this,&FilterView::updateFiltersValue);
    QObject::connect(this->ui->vslider64,&QSlider::valueChanged,this,&FilterView::updateFiltersValue);
    QObject::connect(this->ui->vslider125,&QSlider::valueChanged,this,&FilterView::updateFiltersValue);
    QObject::connect(this->ui->vslider250,&QSlider::valueChanged,this,&FilterView::updateFiltersValue);
    QObject::connect(this->ui->vslider500,&QSlider::valueChanged,this,&FilterView::updateFiltersValue);
    QObject::connect(this->ui->vslider1K,&QSlider::valueChanged,this,&FilterView::updateFiltersValue);
    QObject::connect(this->ui->vslider2K,&QSlider::valueChanged,this,&FilterView::updateFiltersValue);
    QObject::connect(this->ui->vslider4K,&QSlider::valueChanged,this,&FilterView::updateFiltersValue);
    QObject::connect(this->ui->vslider8K,&QSlider::valueChanged,this,&FilterView::updateFiltersValue);
    QObject::connect(this->ui->vslider16K,&QSlider::valueChanged,this,&FilterView::updateFiltersValue);
    QObject::connect(this->ui->cBoxFadeIn,&QCheckBox::stateChanged,this,&FilterView::updateFiltersValue);
    QObject::connect(this->ui->cBoxFadeOut,&QCheckBox::stateChanged,this,&FilterView::updateFiltersValue);



    QObject::connect(__playThread,&PlayThread::durationChanged,this,&FilterView::setduration);

    //this->__playThread->setMedia("./local/123.mp3");
    //this->__playThread->pause();

    QObject::connect(__playThread,&PlayThread::positionChanged,this->ui->timeSlider,&QSlider::setValue);
    QObject::connect(this,&FilterView::customSliderMoved,__playThread,&PlayThread::changeCurPosition);
    this->__isConnectPosition = true;
    //QObject::connect(this->ui->timeSlider,&QSlider::valueChanged,)
    this->__playThread->setMedia("./local/123.mp3");
    this->__playThread->start();
}

bool FilterView::eventFilter(QObject *watched, QEvent *event)
{

    if(watched == this->ui->timeSlider){
        if(event->type() == QEvent::MouseButtonRelease){
            //进度滑动条的拖动事件
            QMouseEvent *mouseEvent = (QMouseEvent *)event;
            if(mouseEvent->button() == Qt::LeftButton){
                this->__playThread->pause();
                QPoint p =ui->timeSlider->mapFromGlobal(  mouseEvent->globalPos());
                int value = (double(p.x())/double(this->ui->timeSlider->width()))*this->ui->timeSlider->maximum();
                //int value = ui->timeSlider->value();

                qDebug()<<"filter"<<value<<" width:"<<this->ui->timeSlider->width();
                emit this->customSliderMoved(value);
                if(!this->__isConnectPosition)
                    QObject::connect(__playThread,&PlayThread::positionChanged,this->ui->timeSlider,&QSlider::setValue);
                this->__isConnectPosition = true;
                //return true;
            }
        }else if(event->type() == QEvent::MouseButtonPress){
            QMouseEvent *mouseEvent = (QMouseEvent *)event;
            if(mouseEvent->button() == Qt::LeftButton){
                if(this->__isConnectPosition){
                    QObject::disconnect(__playThread,&PlayThread::positionChanged,this->ui->timeSlider,&QSlider::setValue);
                    this->__isConnectPosition = false;
                }
            }
            //return true;
        }else if(event->type() ==QEvent::MouseMove){
            //滑块拖动
            if(!this->__isConnectPosition){
                //说明正在被拖动
                qDebug()<<"拖动";
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

void FilterView::setMedia(QString filename)
{
    this->__playThread->clearCache();
    this->__playThread->FreeAllocSpace();
    delete this->__playThread;
    this->__playThread = new PlayThread;
    this->__playThread->setMedia(filename);
    this->__playThread->start();
}

void FilterView::on_btnStartOrPause_clicked()
{
    if(this->__playThread->getPlayerStatus() == playerStatus::stopping){
        this->__playThread->play();
    }else if(this->__playThread->getPlayerStatus() == playerStatus::playing){
        this->__playThread->pause();
    }
}

void FilterView::on_btnPre_clicked()
{
    //this->__playThread->setVolume(this->__playThread->getVolume() - 20);
    //this->__playThread->insertFilter();
    //this->__playThread->changeCurPosition(20000);
    //this->__playThread->setVolume(1000);
}

void FilterView::on_btnNext_clicked()
{
    this->__playThread->setVolume(this->__playThread->getVolume() + 20);
}

void FilterView::on_timeSlider_valueChanged(int value)
{
    //__playThread->changeCurPosition(value);
}

void FilterView::on_timeSlider_sliderMoved(int position)
{
    //__playThread->changeCurPosition(position);
    //QObject::disconnect(__playThread,&PlayThread::positionChanged,this->ui->timeSlider,&QSlider::setValue);
    qDebug()<<"moved:"<<position;
    //this->ui->timeSlider
    //__playThread->changeCurPosition(position);
    //this->ui->timeSlider->setValue(position);
    //QObject::connect(__playThread,&PlayThread::positionChanged,this->ui->timeSlider,&QSlider::setValue);
}

void FilterView::setduration(qint64 duration)
{
    this->ui->timeSlider->setRange(0,duration);
    qDebug()<<"duration:"<<duration;
}

void FilterView::on_timeSlider_actionTriggered(int action)
{
    //__playThread->changeCurPosition(action);
}

void FilterView::on_timeSlider_sliderReleased()
{
     //__playThread->changeCurPosition(this->ui->timeSlider->value());
    //QObject::connect(__playThread,&PlayThread::positionChanged,this->ui->timeSlider,&QSlider::setValue);
    //qDebug()<<"released";
}

void FilterView::on_timeSlider_sliderPressed()
{
    qDebug()<<"presseed";
    if(this->__isConnectPosition)
        QObject::disconnect(__playThread,&PlayThread::positionChanged,this->ui->timeSlider,&QSlider::setValue);

}

void FilterView::updateFiltersValue()
{

    //顺序
    for(int i=0;i<this->__freqSliders.size();i++){
        if(this->__filterConfigObj.contains(FILTER_EQUALIZER_NAME)){
            QJsonArray eqArray = this->__filterConfigObj.value(FILTER_EQUALIZER_NAME).toArray();
            for(int j =0;j<eqArray.size();j++){
                QString filter_name = Equalizer_instance_name[i];
                QJsonObject eqObj = eqArray.at(j).toObject();
                QString key_name = equalizer_config_name[4];
                //是否包含这个 instance
                if(eqObj.contains(key_name)){
                    if(eqObj.value(key_name).toString() == filter_name){
                        int gain = this->__freqSliders.at(i)->value();
                        qDebug()<<filter_name<<"  gain:"<<gain;
                        eqObj[equalizer_config_name[3]] = gain;
                        eqArray.replace(j,eqObj);
                        break;
                    }
                }
            }
            this->__filterConfigObj[FILTER_EQUALIZER_NAME] = eqArray;
        }

    }
    this->__playThread->updateFilterGraph(__filterConfigObj);


}

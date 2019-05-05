#include "musicplayerview.h"
#include "ui_musicplayerview.h"

MusicPlayerView::MusicPlayerView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicPlayerView)
{
    ui->setupUi(this);
    init_view();
}

MusicPlayerView::MusicPlayerView( MusicPlayerController *mpc)
{
    //this->MusicPlayerView();
    this->_musicPlayerController = mpc;

    init_view();
}

MusicPlayerView::~MusicPlayerView()
{
    delete ui;
}

bool MusicPlayerView::eventFilter(QObject *watched, QEvent *event)
{

    if(watched == this){
        if(event->type() == QEvent::Resize){
            QResizeEvent* resizeEvent = (QResizeEvent*) event;
            if(this->__p.isNull()){
                this->__p = QPixmap(":/images/images/flower.jpg");
            }
            this->__p = this->__p.scaled(resizeEvent->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
            this->setBackgroundImage(this->__p);
        }
    }/*else if(watched == this->ui->stackedWidget->children().last()){
        int count = this->ui->stackedWidget->count();
        qDebug()<<"count:"<<count;
        if(count == 1){
            this->setMainWindowWidget(this->ui->stackedWidget->widget(0));
        }else{
            this->setMainWindowWidget(this->ui->stackedWidget->widget(count-1));
        }
    }*/




}

void MusicPlayerView::init_view()
{
    ui = new Ui::MusicPlayerView;
    ui->setupUi(this);

    this->installEventFilter(this);
    this->__isMax = false;
    this->ui->leSearch->setPlaceholderText("搜索");
    this->removeMainWindowWidget();

//    case 居中:
//        label->setStyleSheet("background-color:black;background-image:url(1.jpg);background-position:center;background-repeat:no-repeat;");
//        break;

//    case 缩放:
//        label->setStyleSheet("background-color:black");
//        label->setAlignment(Qt::AlignCenter);
//        label->setPixmap(bgImage.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
//        break;

//    case 拉伸:
//        label->setStyleSheet("background-color:black");
//        label->setPixmap(bgImage.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
//        break;

//    case 平铺:
//        label->setStyleSheet("background-color:black;background-image:url(1.jpg);background-position:top left;background-repeat:repeat-xy;");
//        break;


//    pal.setBrush(QPalette::Background,QBrush(QPixmap("")));
//    this->setPalette(pal);

    /*
     *未实现拉伸功能
     */
    //this->setAttribute();

    //this->__p == QPixmap(":/images/images/flower.jpg");
    //this->__p = this->__p.scaled(this->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    //this->setBackgroundImage(p);


    //this->setStyleSheet("QWidget#MusicPlayerView{background-image: url(:/images/images/flower.jpg);}");

    //this->setBackgroundImage(p);

    //this->setBackground(QUrl(":/images/images/background-hai.jpg"));

    //QPixmap p(":/images/images/background1.jpg");
    //this->setBackgroundImage(p);
    cout<<"musicplayerview : init_view"<<endl;
    //闇€瑕佹挱鏀炬帶鍒剁晫闈¢
    PlayFuncView* pfView = this->_musicPlayerController->getPlayFuncView();
    cout<<"musicplayerview : add PlayFuncView"<<endl;

    //PlayFuncView* p = new PlayFuncView;
    this->ui->HLayout_PlayFunc->addWidget(pfView);

    QWidget* localMusicWidget = (QWidget*)this->_musicPlayerController->getLocalMusicView();
    this->setMainWindowWidget(localMusicWidget);

    //this->ui->btnPullMySheet->setText("收起");
    //this->ui->btnCollectSheetPull->setText("收起");

}

void MusicPlayerView::updateCreatedMusicSheet(QList<MusicSheet> msList)
{
    this->ui->listWdgSongSheet->clear();
    for(int i=0;i<msList.size();i++){
        //QListWidgetItem* item = new QListWidgetItem;
        this->ui->listWdgSongSheet->addItem(msList.at(i).sheetName());

    }


}

void MusicPlayerView::updateCollectedMusicSheet(QList<MusicSheet> msList)
{
    this->ui->listWidgetCollect->clear();
    for(int i=0;i<msList.size();i++){
        //QListWidgetItem* item = new QListWidgetItem;
        this->ui->listWidgetCollect->addItem(msList.at(i).sheetName());

    }
}

void MusicPlayerView::setBackgroundImage(QPixmap &p)
{
    this->setAutoFillBackground(true);
    //设置背景

    QPalette pal;
    pal.setBrush(QPalette::Background,QBrush(p));
    this->setPalette(pal);
}

void MusicPlayerView::setBackground(QUrl url)
{
    this->setBackground(url);
}

void MusicPlayerView::setMainWindowWidget(QWidget *w)
{
//    if(this->_curMainWindowWidget != nullptr){
//        //this->removeMainWindowWidget();
//        this->hideCurMainWindowWidget();
//    }
    int DEBUG = 0;
    if(DEBUG){
        this->hideMainWindowWidget();
        int index = ui->vLayoutMainWindow->indexOf(w);
        qDebug()<<index;
        if(index <0){
            ui->vLayoutMainWindow->addWidget(w);
            w->installEventFilter(this);
            qDebug()<<ui->vLayoutMainWindow->layout()->count();
            if(this->ui->vLayoutMainWindow->layout()->count() > 1){
                this->_lastMainWindowWidget =this->_curMainWindowWidget;
            }else{
                this->_curMainWindowWidget = w;
                this->_lastMainWindowWidget = this->_curMainWindowWidget;
            }

        }else{
            this->_lastMainWindowWidget = this->_curMainWindowWidget;
            this->_curMainWindowWidget = w;
            w->show();
        }
    }else{
        //如果不在stackedwidget里
        int index = this->ui->stackedWidget->indexOf(w);
        if(index <0){
            w->installEventFilter(this);
            index = this->ui->stackedWidget->addWidget(w);

        }else{
            qDebug()<<"index : "<<index;
            QWidget* curWidget = this->ui->stackedWidget->widget(index);
            this->ui->stackedWidget->removeWidget(curWidget);
            index = this->ui->stackedWidget->addWidget(w);
        }
        this->ui->stackedWidget->setCurrentIndex(index);
    }


}

void MusicPlayerView::showMusicDetialView(PlayMusicDetialView *pmdv)
{

}

QWidget* MusicPlayerView::getCurMainWindowWidget()
{
    return this->_curMainWindowWidget;
}

void MusicPlayerView::removeMainWindowWidget()
{

    for(int i=this->ui->stackedWidget->count()-1;i>=0;i--){
        QWidget* w  = this->ui->stackedWidget->widget(i);
        this->ui->stackedWidget->removeWidget(w);
        qDebug()<<i;
    }
    qDebug()<<"ss";

//    cout<<"remove mainwindowWidget"<<endl;
//    cout<<this->_curMainWindowWidget<<endl;
//    int index = this->ui->vLayoutMainWindow->indexOf(this->_curMainWindowWidget);
//    QLayoutItem* item = this->ui->vLayoutMainWindow->itemAt(index);
//    this->ui->vLayoutMainWindow->removeItem(item);
//    this->ui->vLayoutMainWindow->removeWidget(this->_curMainWindowWidget);
    //鍦ㄧЩ闄ゆ椂鏈変竴浜涘伐浣滆¦佸仛
    //this->_musicPlayerController->hiddenWidgetToDo((BaseView*)this->_curMainWindowWidget);
}

void MusicPlayerView::hideCurMainWindowWidget()
{
    this->_curMainWindowWidget->hide();
}

void MusicPlayerView::hideMainWindowWidget()
{
    int all = this->ui->vLayoutMainWindow->layout()->count();
    for(int i=0;i<all;i++){
        QLayoutItem * item = this->ui->vLayoutMainWindow->itemAt(i);
        item->widget()->hide();
        //ui->vLayoutMainWindow->removeWidget(item->widget());
        //ui->vLayoutMainWindow->removeItem(item);


    }
}


void MusicPlayerView::on_btnLocalFile_clicked()
{

    //this->_musicPlayerController->setMainWindowWidget(MusicPlayerController::LOCAL_FILE_WINDOW);
    this->setMainWindowWidget(this->_musicPlayerController->getLocalMusicView());
}

void MusicPlayerView::on_btnDownload_clicked()
{
    this->_musicPlayerController->setMainWindowWidget(MusicPlayerController::DOWNLOAD_FILE_WINDOW);

}

void MusicPlayerView::on_btnClose_clicked()
{
    this->_musicPlayerController->closeApp();
}

void MusicPlayerView::on_btnMinWindow_clicked()
{
    this->_musicPlayerController->minApp();
}

void MusicPlayerView::on_btnMaxWindow_clicked()
{

    this->_musicPlayerController->maxApp();

    if(this->__isMax){

        this->__isMax = false;
        this->ui->btnMaxWindow->setStyleSheet("QPushButton{\
                                          border-image: url(:/images/icon/images/放大(1).png);\
                                      }\
                                      QPushButton:hover{\
                                          border-image: url(:/images/icon/images/放大(2).png);\
                                      }");



    }else{


        this->ui->btnMaxWindow->setStyleSheet("QPushButton{\
                                              border-image: url(:/images/icon/images/缩小(6).png);\
                                          }\
                                          QPushButton:hover{\
                                              border-image: url(:/images/icon/images/缩小(7).png);\
                                          }");

        this->__isMax = true;
    }


}

void MusicPlayerView::on_btnNewMusicSheet_clicked()
{
    //新建歌单
    NewMusicSheetDialog nmsDialog;
    if(nmsDialog.exec()==QDialog::Accepted){
        //如果要创建
        QString sheetName = nmsDialog.getValue();
        MusicSheet ms;
        ms.setSheetName(sheetName);
        ms.setCreateTime(QDateTime::currentDateTime().toString(Qt::TextDate));
        this->_musicPlayerController->createMusicSheet(ms);
    }

}

void MusicPlayerView::on_listWdgSongSheet_doubleClicked(const QModelIndex &index)
{
    int row = index.row();
    //this->_musicPlayerController
    //this->_musicPlayerController->setMainWindowWidget();
//    MusicSheetDetialView* msd =  this->_musicPlayerController->getMusicSheetDetialView();
//    this->_musicPlayerController->
//    msd->updateView();

//    this->setMainWindowWidget();

    MusicSheet ms = this->_musicPlayerController->getCreatedSheet().value(row);
    this->_musicPlayerController->showMusicSheetDetialView(ms);
}

void MusicPlayerView::on_listWidgetCollect_doubleClicked(const QModelIndex &index)
{
    int row = index.row();
    MusicSheet ms = this->_musicPlayerController->getCollectSheet().value(row);
    this->_musicPlayerController->showMusicSheetDetialView(ms);
}



void MusicPlayerView::on_btnPullMySheet_clicked()
{
    if(this->ui->listWdgSongSheet->isHidden()){
        this->ui->listWdgSongSheet->show();
        //this->ui->btnPullMySheet->setText("收起");
        this->ui->btnPullMySheet->setStyleSheet("QPushButton{\
                                                border-image: url(:/images/icon/images/收起.png);\
                                                }\
                                                 QPushButton:hover{border-image: url(:/images/icon/images/收起(1).png);}\
                                            ");
    }else{
        this->ui->listWdgSongSheet->hide();
        //this->ui->btnPullMySheet->setText("下拉");
        this->ui->btnPullMySheet->setStyleSheet("QPushButton{\
                                        border-image: url(:/images/icon/images/下拉.png);\
                                        }\
                                         QPushButton:hover{border-image: url(:/images/icon/images/下拉(1).png);}\
                                    ");
    }
}

void MusicPlayerView::on_btnCollectSheetPull_clicked()
{
    if(this->ui->listWidgetCollect->isHidden()){
        this->ui->listWidgetCollect->show();
        //this->ui->btnCollectSheetPull->setText("收起");
        this->ui->btnCollectSheetPull->setStyleSheet("QPushButton{\
                                                border-image: url(:/images/icon/images/收起.png);\
                                                }\
                                                 QPushButton:hover{border-image: url(:/images/icon/images/收起(1).png);}\
                                            ");
    }else{
        this->ui->listWidgetCollect->hide();
        //this->ui->btnCollectSheetPull->setText("下拉");
        this->ui->btnCollectSheetPull->setStyleSheet("QPushButton{\
                                        border-image: url(:/images/icon/images/下拉.png);\
                                        }\
                                         QPushButton:hover{border-image: url(:/images/icon/images/下拉(1).png);}\
                                    ");
    }
}

void MusicPlayerView::on_btnMusicCut_clicked()
{
    MusicCutView* mcView = new MusicCutView;
    mcView->show();
}

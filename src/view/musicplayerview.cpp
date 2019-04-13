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

void MusicPlayerView::init_view()
{
    ui = new Ui::MusicPlayerView;
    ui->setupUi(this);
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
    QLabel* label = new QLabel(this);
    label->setGeometry(0,0,this->width(),this->height());
    label->setPixmap(p.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
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
    this->hideMainWindowWidget();
    int index = ui->vLayoutMainWindow->indexOf(w);
    qDebug()<<index;
    if(index <0){
        ui->vLayoutMainWindow->addWidget(w);
        qDebug()<<ui->vLayoutMainWindow->layout()->count();
        this->_curMainWindowWidget = w;
    }else{
        w->show();
    }
    qDebug()<<this->size();

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
    cout<<"remove mainwindowWidget"<<endl;
    cout<<this->_curMainWindowWidget<<endl;
    int index = this->ui->vLayoutMainWindow->indexOf(this->_curMainWindowWidget);
    QLayoutItem* item = this->ui->vLayoutMainWindow->itemAt(index);
    this->ui->vLayoutMainWindow->removeItem(item);
    this->ui->vLayoutMainWindow->removeWidget(this->_curMainWindowWidget);
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

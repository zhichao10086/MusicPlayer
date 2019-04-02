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
    //需要播放控制界面
    PlayFuncView* pfView = this->_musicPlayerController->getPlayFuncView();
    cout<<"musicplayerview : add PlayFuncView"<<endl;

    //PlayFuncView* p = new PlayFuncView;
    this->ui->HLayout_PlayFunc->addWidget(pfView);

    QWidget* localMusicWidget = (QWidget*)this->_musicPlayerController->getLocalMusicView();
    this->setMainWindowWidget(localMusicWidget);

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
    if(this->_curMainWindowWidget != nullptr){
        this->removeMainWindowWidget();
    }
    //设置主界面
    cout<<"zhuejiemian "<<endl;
    ui->vLayoutMainWindow->addWidget(w);
    this->_curMainWindowWidget = w;
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
    //在移除时有一些工作要做
    //this->_musicPlayerController->hiddenWidgetToDo((BaseView*)this->_curMainWindowWidget);
}


void MusicPlayerView::on_btnLocalFile_clicked()
{

    this->_musicPlayerController->setMainWindowWidget(MusicPlayerController::LOCAL_FILE_WINDOW);
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

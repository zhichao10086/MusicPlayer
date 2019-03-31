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

    QPixmap p(":/images/images/background1.jpg");
    //this->setBackgroundImage(p);
    cout<<"musicplayerview : init_view"<<endl;
    //需要播放控制界面
    PlayFuncView* pfView = this->_musicPlayerController->getPlayFuncView();
    cout<<"musicplayerview : add PlayFuncView"<<endl;

    //PlayFuncView* p = new PlayFuncView;
    this->ui->HLayout_PlayFunc->addWidget(pfView);
}

void MusicPlayerView::setBackgroundImage(QPixmap &p)
{
    QLabel* label = new QLabel(this);
    label->setGeometry(0,0,this->width(),this->height());
    label->setPixmap(p.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void MusicPlayerView::setMainWindowWidget(QWidget *w)
{
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
    this->ui->vLayoutMainWindow->removeWidget(this->_curMainWindowWidget);
}

void MusicPlayerView::on_btnLocalFile_clicked()
{

    this->_musicPlayerController->setMainWindowWidget(MusicPlayerController::LOCAL_FILE_WINDOW);
}

#include "musicplayerview.h"
#include "ui_musicplayerview.h"

MusicPlayerView::MusicPlayerView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicPlayerView)
{
    ui->setupUi(this);
}

MusicPlayerView::MusicPlayerView( MusicPlayerController *mpc)
{
    //this->MusicPlayerView();
    this->_musicPlayerController = mpc;
    ui = new Ui::MusicPlayerView;
    ui->setupUi(this);
}

MusicPlayerView::~MusicPlayerView()
{
    delete ui;
}

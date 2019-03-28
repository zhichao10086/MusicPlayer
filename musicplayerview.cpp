#include "musicplayerview.h"
#include "ui_musicplayerview.h"

MusicPlayerView::MusicPlayerView(MusicPlayerController *mpc,QWidget *parent =0 ):
    QMainWindow(parent),
    ui(new Ui::MusicPlayerView)
{

    ui->setupUi(this);
    _musicPlayerController = mpc;
}

MusicPlayerView::MusicPlayerView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MusicPlayerView)
{
    ui->setupUi(this);

}

MusicPlayerView::~MusicPlayerView()
{
    delete ui;
}

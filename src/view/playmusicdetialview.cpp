#include "playmusicdetialview.h"
#include "ui_playmusicdetialview.h"

PlayMusicDetialView::PlayMusicDetialView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayMusicDetialView)
{
    this->__initView();
}

PlayMusicDetialView::PlayMusicDetialView(PlayMusicDetialController *pmdc, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayMusicDetialView)
{
    this->__playMusicDetialCtrl = pmdc;
    this->__initView();

}

PlayMusicDetialView::~PlayMusicDetialView()
{
    delete ui;
}

void PlayMusicDetialView::updateView(Music music)
{
    if(music.isEmpty())
        return;

    this->ui->labMusicName->setText(music.musicName());
    this->ui->labAlbum->setText(music.album());

}

void PlayMusicDetialView::__initView()
{
    ui->setupUi(this);


}

bool PlayMusicDetialView::event(QEvent *event)
{
    if(event->type() == QEvent::Hide){
        this->__playMusicDetialCtrl->disconnectPlayer();
    }else if(event->type() == QEvent::Show){
        this->__playMusicDetialCtrl->connectPlayer();
    }
    return QWidget::event(event);
}

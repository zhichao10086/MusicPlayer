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

    if(music == this->__music)
        return;
    this->__music = music;

    this->ui->labMusicName->setText(music.title());
    this->ui->labAlbum->setText(music.album());
    this->ui->labSinger->setText(music.artist());
    if(!music.images().isEmpty()){

        QSize imageSize = this->ui->labMusicImage->sizeHint();
        this->ui->labMusicImage->setPixmap(QPixmap::fromImage(music.images().at(0)).scaled(imageSize));
    }

    this->ui->lwMusicLyrics->setLyrics(music.lyrics());
    this->ui->lwMusicLyrics->initView();

}

void PlayMusicDetialView::__initView()
{
    ui->setupUi(this);
    this->ui->btn_mv->hide();
    this->ui->btnLike->setIcon(QIcon(":/images/icon/images/喜欢(1).png"));
    this->ui->btnCollect->setIcon(QIcon(":/images/icon/images/收藏夹(2).png"));
    this->ui->btnDownload->setIcon(QIcon(":/images/icon/images/下载(1).png"));
    this->ui->btnShare->setIcon(QIcon(":/images/icon/images/分享(2).png"));
    //QPixmap()
    //ui->btnLike->setIcon(QIcon());

}

void PlayMusicDetialView::updateLyrics(qint64 position)
{
    this->ui->lwMusicLyrics->updateLyricsView(position);
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

void PlayMusicDetialView::on_btnMin_clicked()
{
    this->hide();
}

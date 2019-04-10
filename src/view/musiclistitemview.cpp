#include "musiclistitemview.h"
#include "ui_musiclistitemview.h"

MusicListItemView::MusicListItemView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicListItemView)
{
    ui->setupUi(this);
}

MusicListItemView::MusicListItemView(int index,Music music,ViewMode mode, QWidget *parent):
    QWidget(parent),
    ui(new Ui::MusicListItemView)
{
    ui->setupUi(this);
    this->__index = index;
    this->__music = music;

    ui->labIndex->setText(QString::number(index));
    if(!music.musicName().isEmpty())
        ui->labMusicName->setText(music.musicName());

    if(!music.time().isEmpty())
        ui->labTime->setText(music.time());

    if(!music.album().isEmpty())
        ui->labAlbum->setText(music.album());

    if(mode == ViewMode::LocalMusicListItem){
        this->localMusicListItemShow();
    }else if(mode == ViewMode::SearchMusicListItem){
        this->searchMusicListItemShow();
    }else if(mode == ViewMode::PlaySheetListItem){
        this->playSheetListItemShow();
    }else if(mode == ViewMode::RecentSheetListItem){
        this->recentSheetListItemShow();
    }

}

MusicListItemView::~MusicListItemView()
{
    delete ui;
}

void MusicListItemView::localMusicListItemShow()
{
    if(__music.fileSize()>=0){
        double fileSize = ((double)this->__music.fileSize())/1024;

        ui->labFileSize->setText(QString::number(fileSize) + "MB");
    }

    ui->btnDownload->hide();  //1
    ui->btnLike->hide();
    ui->progBarHot->hide();

}

void MusicListItemView::searchMusicListItemShow()
{
    ui->labFileSize->hide();
    ui->progBarHot->setRange(0,100);
    if(__music.musicHot() >=0)
        ui->progBarHot->setValue(static_cast<int>(__music.musicHot()));
    else
        ui->progBarHot->setValue(0);

}

void MusicListItemView::playSheetListItemShow()
{
    ui->labFileSize->hide();

    ui->btnDownload->hide();
    ui->btnLike->hide();
    ui->progBarHot->hide();
}

void MusicListItemView::recentSheetListItemShow()
{
    ui->labFileSize->hide();

    ui->btnDownload->hide();
    ui->btnLike->hide();
    ui->progBarHot->hide();
}

void MusicListItemView::initView()
{
    QSize size = this->parentWidget()->size();
    this->resize(size.width(),40);
}

Music MusicListItemView::music() const
{
    return __music;
}

void MusicListItemView::setMusic(const Music &music)
{
    __music = music;
}

#include "localmusicview.h"
#include "ui_localmusicview.h"

LocalMusicView::LocalMusicView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LocalMusicView)
{
    ui->setupUi(this);
}

LocalMusicView::LocalMusicView(LocalMusicController *lmc, QWidget *parent):
    QWidget(parent)
{
    this->_localMusicCtrl = lmc;
    this->init_view();
}

LocalMusicView::~LocalMusicView()
{
    delete ui;
}

void LocalMusicView::init_view()
{
    ui = new Ui::LocalMusicView;
    ui->setupUi(this);
}

void LocalMusicView::updateListWidget(QVector<Music> &musics)
{

    for(int i =0;i<musics.size();i++){
        QListWidgetItem* item = new QListWidgetItem;
        QLabel *label  = new QLabel(musics.at(i).musicName());

        this->ui->lwMusicList->addItem(item);
        this->ui->lwMusicList->setItemWidget(item,label);
    }
}

void LocalMusicView::clearMusicListWidget()
{
    this->ui->lwMusicList->clear();
}

void LocalMusicView::on_btnOpenDir_clicked()
{

    this->_localMusicCtrl->showChooseDirsDialog();

}

void LocalMusicView::on_lwMusicList_doubleClicked(const QModelIndex &index)
{

    this->_localMusicCtrl->playMusic(index);

}

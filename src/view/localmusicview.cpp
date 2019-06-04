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
    //this->ui->lwMusicList->setItemViewMode(ViewMode::LocalMusicListItem);


}

void LocalMusicView::updateListWidget(QList<Music> &musics)
{
    this->ui->lwMusicList->clear();
    this->ui->lwMusicList->updateView(musics);
    /*
    this->ui->lwMusicList->clear();
    for(int i =0;i<musics.size();i++){
        QListWidgetItem* item = new QListWidgetItem;
        //QLabel *label  = new QLabel(musics.at(i).musicName());
        MusicListItemView* itemView = new MusicListItemView(i,musics.at(i),MusicListItemView::ViewMode::LocalMusicListItem);

        QSize size = item->sizeHint();
        item->setSizeHint(QSize(size.width(),30));
        this->ui->lwMusicList->addItem(item);
        this->ui->lwMusicList->setItemWidget(item,itemView);
    }
    */
}

void LocalMusicView::clearMusicListWidget()
{
    this->ui->lwMusicList->clear();
}

void LocalMusicView::setCurListWidgetIndex(int index)
{
    cout<<index<<endl;
    QListWidgetItem* item =  this->ui->lwMusicList->item(index);
    this->ui->lwMusicList->setItemSelected(item,true);

}

void LocalMusicView::on_btnOpenDir_clicked()
{

    this->_localMusicCtrl->showChooseDirsDialog();

}

void LocalMusicView::on_lwMusicList_doubleClicked(const QModelIndex &index)
{
    int music_index = index.row();

    if(this->_localMusicCtrl->getCurMusicSheet().sheetName() != QString("本地音乐")){
    //如果同意切换列表
        if(QMessageBox::Yes == QMessageBox::question(this,"切换提示","是否要切换播放列表",QMessageBox::Yes | QMessageBox::No)){

            this->_localMusicCtrl->addSheetToMedia();
            //this->_localMusicCtrl->playMusic(music_index);

            qDebug()<<"local"<<endl;
        }else{
            music_index = this->_localMusicCtrl->addMusicToCurSheet(index);

            //this->_localMusicCtrl->playMusic(index);
        }
    }
    this->_localMusicCtrl->playMusic(music_index);

}

void LocalMusicView::hiddenToDo()
{

}

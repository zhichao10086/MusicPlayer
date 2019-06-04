#include "downloadview.h"
#include "ui_downloadview.h"

DownLoadView::DownLoadView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DownLoadView)
{
    ui->setupUi(this);

}

DownLoadView::~DownLoadView()
{
    delete ui;
}

DownLoadView::DownLoadView(DownLoadController *dlc, QWidget *p)
{
   this->_dlc = dlc;
   initView();
}

DownLoadController *DownLoadView::dlc() const
{
    return _dlc;
}

void DownLoadView::setDlc(DownLoadController *dlc)
{
    _dlc = dlc;
}

void DownLoadView::initView()
{
    ui = new Ui::DownLoadView;
    ui->setupUi(this);

    this->__netManager = new QNetworkAccessManager;

    this->__downloadDir.append(GlobalVariable::global_download_file_path);

    this->__downMusics =  FileFuncController::searchMusics(this->__downloadDir);
    this->updateDownloadedView();

}

void DownLoadView::addDownLoadTask(Music &music)
{

    qDebug()<<"tianjia xaizai renwu"<<music.musicID();
    //设置当前的
    this->ui->tabWidget->setCurrentIndex(1);
    int index = this->ui->lwDownloading->count();

    for(int i=0;i<this->__downMusics.size();i++){
        if(this->__downMusics.at(i).title() == music.title())
        QMessageBox::about(this,tr("提示"),tr("已下载"));
        return;
    }

    DownLoadMusicListItemView* itemView = new DownLoadMusicListItemView(index,music,DownLoadMusicListItemView::ViewType::downLoading);
    itemView->setDlView(this);
    QListWidgetItem* item = new QListWidgetItem();

    QSize size = this->ui->lwDownloading->sizeHint();
    item->setSizeHint(QSize(size.width(),40));
    this->ui->lwDownloading->addItem(item);
    this->ui->lwDownloading->setItemWidget(item,itemView);
    this->_downLoadingMusics.append(music);

}

void DownLoadView::musicDownLoaded(int index)
{
    qDebug()<<index;
    const Music& music = this->_downLoadingMusics.at(index);
    QListWidgetItem* item = this->ui->lwDownloading->item(index);
    this->ui->lwDownloading->removeItemWidget(item);
    delete item;
    /*
     * 添加到已下载队列
     */
    this->__downMusics.append(music);
    qDebug()<<"tianjia dao yixiazai ";
    this->updateDownloadedView();
    /*
    int index1 = this->ui->lwDownload->count();

    DownLoadMusicListItemView* itemView = new DownLoadMusicListItemView(index1,music,DownLoadMusicListItemView::ViewType::downLoaded);

    QListWidgetItem* item1 = new QListWidgetItem();

    QSize size = this->ui->lwDownload->sizeHint();
    item1->setSizeHint(QSize(size.width(),40));
    this->ui->lwDownload->addItem(item1);
    this->ui->lwDownload->setItemWidget(item1,itemView);

    this->_downLoadedMusics.append(music);
    this->_downLoadingMusics.removeAt(index);
    */

}

void DownLoadView::updateDownloadedView()
{
    this->ui->lwDownload->clear();
    for(int i =0;i<this->__downMusics.size();i++){
        QListWidgetItem* item = new QListWidgetItem;
        //QLabel *label  = new QLabel(musics.at(i).musicName());
        DownLoadMusicListItemView* itemView = new DownLoadMusicListItemView(i,this->__downMusics.at(i),DownLoadMusicListItemView::ViewType::downLoaded);


        QSize size = item->sizeHint();
        item->setSizeHint(QSize(size.width(),40));
        this->ui->lwDownload->addItem(item);
        this->ui->lwDownload->setItemWidget(item,itemView);
    }
}


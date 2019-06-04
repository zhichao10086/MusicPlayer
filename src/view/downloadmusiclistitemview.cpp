#include "downloadmusiclistitemview.h"
#include "ui_downloadmusiclistitemview.h"

DownLoadMusicListItemView::DownLoadMusicListItemView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DownLoadMusicListItemView)
{
    ui->setupUi(this);
}

DownLoadMusicListItemView::DownLoadMusicListItemView(int index,const Music &music,ViewType viewtype, QWidget *parent):
    QWidget(parent),
    ui(new Ui::DownLoadMusicListItemView)
{
    ui->setupUi(this);
    this->initView();

    this->__netManager = new QNetworkAccessManager;
    this->_index = index;
    this->_music = music;
    ui->labIndex->setText(QString::number(index));
    if(!music.title().isEmpty()){
        this->ui->labMusicName->setText(music.title());
    }
    if(!music.time().isEmpty())
        this->ui->labTime->setText(music.time());

    if(!music.album().isEmpty())
        this->ui->labAlbum->setText(music.album());

    if(!music.artist().isEmpty())
        this->ui->labSinger->setText(music.artist());

    if(viewtype == ViewType::downLoading){
        QObject::connect(this->__netManager,&QNetworkAccessManager::finished,
                         this,&DownLoadMusicListItemView::musicDownLoaded);

        QNetworkRequest req;
        qDebug()<<"下载请求  "<<music.musicID();
        this->__file  = new QFile("./download/" + music.title() + ".mp3");
        this->__file->open(QIODevice::WriteOnly);
        QString strUrl = (GlobalVariable::global_server_download_url + "?" + "musicid=" + music.musicID()) ;
        qDebug()<<strUrl;

        req.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");

        //DownLoadMusicListItemView* itemView = new DownLoadMusicListItemView(music);


        req.setUrl(QUrl(strUrl));
        this->__reply =  this->__netManager->get(req);

        QObject::connect(this->__reply,&QNetworkReply::downloadProgress,this,&DownLoadMusicListItemView::musicDownLoading);
        QObject::connect(this->__reply,&QNetworkReply::readyRead,this,&DownLoadMusicListItemView::readContent);
        this->__netManager->get(req);
    }else{
        this->ui->pbDownLoad->hide();
    }


}

void DownLoadMusicListItemView::initView()
{
    this->_menu = new MusicListItemMenu(this->_music);
    QObject::connect(this,&DownLoadMusicListItemView::customContextMenuRequested,
                     this,&DownLoadMusicListItemView::popupContextMenu);

    this->ui->pbDownLoad->setMinimum(0);
    this->ui->pbDownLoad->setMaximum(100);
}

void DownLoadMusicListItemView::musicDownLoading(qint64 bytesReceived, qint64 bytesTotal)
{
    this->ui->pbDownLoad->setValue(int((bytesReceived/bytesTotal)*100));
}

void DownLoadMusicListItemView::musicDownLoaded(QNetworkReply *reply)
{
    if(reply->error() == QNetworkReply::NoError) {
        reply->deleteLater();
        this->__file->flush();
        this->__file->close();
        this->ui->pbDownLoad->setValue(100);
        qDebug()<<"xiazai wancheng";



       this->__dlView->musicDownLoaded(this->_index);
    } else {
        QMessageBox::critical(NULL, tr("Error"), "Failed!!!");
    }

}

void DownLoadMusicListItemView::readContent()
{
    this->__file->write(this->__reply->readAll());
}

DownLoadMusicListItemView::~DownLoadMusicListItemView()
{
    delete ui;
}

void DownLoadMusicListItemView::popupContextMenu(QPoint p)
{
    this->_menu->exec(this->mapToGlobal(p));
}

void DownLoadMusicListItemView::setDlView(DownLoadView *dlView)
{
    __dlView = dlView;
}

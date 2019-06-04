#include "musicsheetdetialview.h"
#include "ui_musicsheetdetialview.h"

MusicSheetDetialView::MusicSheetDetialView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicSheetDetialView)
{
    ui->setupUi(this);
}

MusicSheetDetialView::MusicSheetDetialView(MusicSheetDetialController *msdCtrl, QWidget *parent):
    QWidget(parent),
    ui(new Ui::MusicSheetDetialView)
{
    this->__msdCtrl = msdCtrl;
    this->__netManager = new QNetworkAccessManager;
    this->initView();
}

MusicSheetDetialView::~MusicSheetDetialView()
{
    delete ui;
}

void MusicSheetDetialView::initView()
{
    ui->setupUi(this);
    this->ui->leSearch->setPlaceholderText("搜索");
}



void MusicSheetDetialView::updateView(const MusicSheet& musicSheet)
{
    //this->__musicSheet = musicSheet;
    this->ui->labCreateTime->setText(musicSheet.createTime());
    this->ui->labPlayCnt->setText(QString::number( musicSheet.playCount()));
    this->ui->labSheetName->setText(musicSheet.sheetName());

    this->ui->labMuiscCnt->setText(QString::number(musicSheet.playCount()));

    if(!musicSheet.userName().isEmpty())
        this->ui->labUserName->setText(musicSheet.userName());
    else{
        this->ui->labUserName->setText(CONST_ERROR_STRING_SHUJUCUOWU);
    }
    if(!musicSheet.userHeadImageUrl().isEmpty()){
        QObject::connect(this->__netManager,&QNetworkAccessManager::finished,
                         this,&MusicSheetDetialView::headImageFinished);
        QNetworkRequest req;
        req.setUrl(QUrl(musicSheet.userHeadImageUrl()));
        this->__netManager->get(req);
    }

    //this->ui->labIntroducement->setText(musicSheet);
    if(musicSheet.localSheetImageUrl().isEmpty()){
        //网络加载
        QObject::connect(this->__netManager,&QNetworkAccessManager::finished,
                         this,&MusicSheetDetialView::imageFinished);

        QNetworkRequest req;
        req.setUrl(QUrl(musicSheet.netSheetImageUrl()));
        this->__netManager->get(req);

    }else{
        qDebug()<<"local";
        this->ui->labSheetImage->setPixmap(QPixmap(musicSheet.localSheetImageUrl()));
    }


    //刷新列表
    this->updateMusicListView(musicSheet.musics());
}

void MusicSheetDetialView::imageFinished(QNetworkReply *reply)
{
    /*
     * 图片加载完毕后，存储在本地
     */
    if(reply->error() == QNetworkReply::NoError){
        QByteArray ba = reply->readAll();
        QPixmap p;
        p.loadFromData(ba);
        this->ui->labSheetImage->setPixmap(p);
        qDebug()<<"加载图片"<<ba;

        /*
        QString filename = GlobalVariable::global_local_file_path + "/" + CONST_GLOBAL_STRING_SHEETIMAGES_DIR+"/"
                 + this->ui->labSheetName->text() + ".png";
        QFile file(filename);

        if(file.open(QIODevice::WriteOnly)){
            file.write(ba);
            this->__msdCtrl->updateLocalImageUrl(filename);
        }
        file.close();
        */
        //将结果更新给musicsheet

    }
}

void MusicSheetDetialView::headImageFinished(QNetworkReply *reply)
{
    if(reply->error() == QNetworkReply::NoError){
        QByteArray ba = reply->readAll();
        QPixmap p;
        p.loadFromData(ba);
        this->ui->labSheetImage->setPixmap(p);

        /*
        QString filename = GlobalVariable::global_local_file_path + "/" + CONST_GLOBAL_STRING_SHEETIMAGES_DIR+"/"
                 + this->ui->labSheetName->text() + ".png";
        QFile file(filename);

        if(file.open(QIODevice::WriteOnly)){
            file.write(ba);
            this->__msdCtrl->updateLocalImageUrl(filename);
        }
        file.close();
        //将结果更新给musicsheet
        */
    }
}

void MusicSheetDetialView::updateMusicListView(QList<Music> musics)
{
    this->ui->lwMusicSheet->clear();
    for(int i=0;i<musics.size();i++){
        MusicListItemView* view =  new MusicListItemView(i,musics.at(i),MusicItemViewMode::MusicSheetListItem);
        QListWidgetItem* item = new QListWidgetItem;
        //QLabel *label  = new QLabel(musics.at(i).musicName());
        QSize size = item->sizeHint();
        qDebug()<<i;
        item->setSizeHint(QSize(this->ui->lwMusicSheet->sizeHint().width(),28));
        this->ui->lwMusicSheet->addItem(item);
        this->ui->lwMusicSheet->setItemWidget(item,view);

    }
}


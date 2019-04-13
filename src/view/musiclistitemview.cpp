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

    /*
     * 初始化action
     */
    this->_menu = new QMenu;
    this->_actionPlay = new QAction("播放");
    this->_actionDownload = new QAction("下载");
    this->_actionNextPlay = new QAction("下一首播放");
    this->_actionCollect = new QAction("收藏");
    this->_menu->addAction(this->_actionPlay);
    this->_menu->addAction(this->_actionNextPlay);
    this->_menu->addAction(this->_actionDownload);



    this->_collectMenu = new QMenu("收藏到歌单");

    QList<MusicSheet> msList = GlobalVariable::get_global_User().createdMusicSheets();
    for(int i=0;i<msList.size();i++){
        QAction* action = new QAction(msList.at(i).sheetName());
        this->_collectMenu->addAction(action);
        this->_collectActions.append(action);
    }
    this->_menu->addMenu(this->_collectMenu);


    QObject::connect(this,&MusicListItemView::customContextMenuRequested,
                     this,&MusicListItemView::popupContextMenu);

    this->__index = index;
    this->__music = music;



    ui->labIndex->setText(QString::number(index));
    if(!music.musicName().isEmpty()){
        this->setTextElide(this->ui->labMusicName,music.musicName());
    }
    if(!music.time().isEmpty())
        this->ui->labTime->setText(music.time());

    if(!music.album().isEmpty())
        this->setTextElide(ui->labAlbum,music.album());

    if(!music.singer().isEmpty())
        this->setTextElide(ui->labSinger,music.singer());

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



void MusicListItemView::setTextElide(QLabel *label, QString string)
{
    QFontMetrics fontMetrics(this->font());

    int fontSize = fontMetrics.width(string);//获取之前设置的字符串的像素大小

    QString str = string;

    if(fontSize > label->width())
    {
        str = fontMetrics.elidedText(string, Qt::ElideRight, label->width());//返回一个带有省略号的字符串
        label->setToolTip(string);
    }

    label->setText(str);
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
    this->resize(size.width(),30);
}

Music MusicListItemView::music() const
{
    return __music;
}

void MusicListItemView::setMusic(const Music &music)
{
    __music = music;
}

void MusicListItemView::on_labMusicName_linkHovered(const QString &link)
{

}

void MusicListItemView::popupContextMenu(QPoint p)
{
    this->_menu->exec(this->mapToGlobal(p));
}



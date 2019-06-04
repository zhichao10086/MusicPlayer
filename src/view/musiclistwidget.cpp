#include "musiclistwidget.h"
#include "ui_musiclistwidget.h"

MusicListWidget::MusicListWidget(QWidget *parent) :
    QListWidget(parent),
    ui(new Ui::MusicListWidget)
{
    ui->setupUi(this);
    this->initView();
}



MusicListWidget::~MusicListWidget()
{
    delete ui;
}

MusicItemViewMode MusicListWidget::getItemViewMode() const
{
    return _itemViewMode;
}

void MusicListWidget::setItemViewMode( MusicItemViewMode value)
{
    _itemViewMode = value;
}

void MusicListWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    PlayFuncController* pfc = PlayFuncController::newInstance();
    pfc->playMusic(this->__musics.at(this->currentRow()));
}

void MusicListWidget::initView()
{
    /*
    QListWidgetItem* item = new QListWidgetItem;
    //QLabel *label  = new QLabel(musics.at(i).musicName());
    MusicListHeaderVIew* itemView = new MusicListHeaderVIew;

    QSize size = item->sizeHint();
    item->setSizeHint(QSize(size.width(),CONST_GLOBAL_INT_MUSIClISTITEMVIEW_HIEGHT+10));
    this->addItem(item);
    this->setItemWidget(item,itemView);
    */
    this->_itemViewMode = MusicItemViewMode::LocalMusicListItem;
}

void MusicListWidget::updateView(QList<Music> &musics)
{
    this->clear();
    for(int i =0;i<musics.size();i++){
        QListWidgetItem* item = new QListWidgetItem;
        //QLabel *label  = new QLabel(musics.at(i).musicName());

        MusicListItemView* itemView = new MusicListItemView(i,musics.at(i),this->_itemViewMode);

        QSize size = item->sizeHint();
        item->setSizeHint(QSize(this->size().width(),CONST_GLOBAL_INT_MUSIClISTITEMVIEW_HIEGHT));
        this->addItem(item);
        this->setItemWidget(item,itemView);
    }
}

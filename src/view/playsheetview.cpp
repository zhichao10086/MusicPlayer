#include "playsheetview.h"
#include "ui_playsheetview.h"

PlaySheetView::PlaySheetView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlaySheetView)
{
    this->initView();
}

PlaySheetView::PlaySheetView(PlaySheetController *pfc, QWidget *parent):
    QWidget(parent),
    ui(new Ui::PlaySheetView)
{
    this->__pfCtrl = pfc;
    this->initView();
}

PlaySheetView::~PlaySheetView()
{
    delete ui;
}

bool PlaySheetView::getIsFilter() const
{
    return isFilter;
}

void PlaySheetView::setIsFilter(bool value)
{
    isFilter = value;
}

bool PlaySheetView::eventFilter(QObject *o, QEvent *e)
{
//    if(QEvent::WindowDeactivate == e->type())//窗口停用
//    {
//        hide();//或者关闭窗口
//        qDebug()<<"hide"<<endl;
//        isFilter = true;
//        //return true;
//    }

    //if(watched == this->ui->btnPlaySheet){
//    if(e->type() == QEvent::MouseButtonPress){
//        //播放按钮的点击显示播放列表
//        QMouseEvent *mouseEvent = (QMouseEvent *)e;
//        if(mouseEvent->button() == Qt::LeftButton){
//            QSize parentSize = this->parentWidget()->size();
//            QPoint pLeft = this->pos();
//            QPoint pright = QPoint(this->pos().x()+ this->width(),this->pos().y()+this->height());
//            QPoint mousePoint = QWidget::mapTo(this->parentWidget(),mouseEvent->pos());
//            qDebug()<<pLeft<<pright<<mousePoint;
//            if(!this->isHidden()){
//                if(mousePoint.x() <0 || mousePoint.y() <0
//                        || mousePoint.x() >parentSize.width() ||
//                        mousePoint.y() > parentSize.height())
//                    return true;
//                if(!(mousePoint.x() >= pLeft.x() &&
//                    mousePoint.x() <= pright.x() &&
//                     mousePoint.y() >= pLeft.y() &&
//                      mousePoint.y() <= pright.y()) )
//                    hide();

//                cout<<"111111111111"<<endl;
//                return true;
//            }

//        }
//    }



    return QWidget::eventFilter(o , e);
}

void PlaySheetView::initView()
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->resize(QSize(700,400));
    //this->__pfCtrl->updateView();
    //installEventFilter(this);
}

void PlaySheetView::updateListWidgetPlaySheet(const MusicSheet &musicSheet)
{

    this->ui->lwplaySheet->clear();
    QList<Music> musics = musicSheet.musics();
    for(int i =0;i<musics.size();i++){
        QListWidgetItem* item = new QListWidgetItem;
        //QLabel *label  = new QLabel(musics.at(i).musicName());
        MusicListItemView* itemView = new MusicListItemView(i,musics.at(i),MusicListItemView::ViewMode::PlaySheetListItem);
        QSize size = item->sizeHint();
        qDebug()<<i;
        item->setSizeHint(QSize(this->ui->lwplaySheet->sizeHint().width(),28));
        this->ui->lwplaySheet->addItem(item);
        this->ui->lwplaySheet->setItemWidget(item,itemView);

    }


}

void PlaySheetView::updateListWidgetRecentPlaySheet(const MusicSheet &musicSheet)
{
    this->ui->lwRecentPlaySheet->clear();
    QList<Music> musics = musicSheet.musics();
    for(int i =0;i<musics.size();i++){
        QListWidgetItem* item = new QListWidgetItem;
        //QLabel *label  = new QLabel(musics.at(i).musicName());
        MusicListItemView* itemView = new MusicListItemView(i,musics.at(i),MusicListItemView::ViewMode::RecentSheetListItem);
        QSize size = item->sizeHint();
        item->setSizeHint(QSize(this->ui->lwRecentPlaySheet->sizeHint().width(),28));
        this->ui->lwRecentPlaySheet->addItem(item);
        this->ui->lwRecentPlaySheet->setItemWidget(item,itemView);
    }

}



PlaySheetController *PlaySheetView::pfCtrl() const
{
    return __pfCtrl;
}

void PlaySheetView::setPfCtrl(PlaySheetController *pfCtrl)
{
    __pfCtrl = pfCtrl;
}

void PlaySheetView::on_lwplaySheet_itemDoubleClicked(QListWidgetItem *item)
{
    /*
     * 播放事件
     */

    //QWidget* w = this->ui->lwplaySheet->itemWidget(item);
    //QModelIndex* index = this->ui->lwplaySheet->indexFromItem()
    //this->__pfCtrl->playMusic();
}

void PlaySheetView::on_lwplaySheet_doubleClicked(const QModelIndex &index)
{
    this->__pfCtrl->playMusic(index);
}

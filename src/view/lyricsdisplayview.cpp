#include "lyricsdisplayview.h"
#include "ui_lyricsdisplayview.h"

LyricsDisplayView::LyricsDisplayView(QWidget *parent) :
    QListWidget(parent),
    ui(new Ui::LyricsDisplayView)
{
    ui->setupUi(this);
}

LyricsDisplayView::~LyricsDisplayView()
{
    delete ui;
}

void LyricsDisplayView::setLyrics(Lyrics lyrics)
{
    this->__lyrics = lyrics;
    this->__curLyricsIndex = this->__lyrics.lyricsBeginIndex();
    this->__veclyrics = this->__lyrics.vecLyrics();
}

void LyricsDisplayView::setDuration(qint64 duration)
{
    this->__duration = duration;
}

void LyricsDisplayView::initView()
{
    this->ui->listWidget->clear();
    QStringList allData = this->__lyrics.allData();

    for(int i=0;i<allData.size();i++){
        //显示所有信息
        QString line = allData.at(i);
        QListWidgetItem* item = new QListWidgetItem();
        LyricsItemView* view =  new LyricsItemView(LyricsItemView::ViewMode::NoPlaying);
        view->setText(line);
        QSize size = this->ui->listWidget->sizeHint();
        item->setSizeHint(QSize(size.width(),28));
        if(i == this->__curLyricsIndex){
            view->setMode(LyricsItemView::ViewMode::Playing);
            item->setSizeHint(QSize(size.width(),35));
        }
        this->ui->listWidget->addItem(item);
        this->ui->listWidget->setItemWidget(item,view);
    }


}

void LyricsDisplayView::updateLyricsView(qint64 position)
{
    //首先将时间信息转换为
    //知道当前的位置信息，也就知道当前的时间 如果这个位置在这个与下一个之间则不变，
    //如果超过下一个则变化
    //LLData curLine =  this->__veclyrics.at(this->__curLyricsIndex);

    //如果到最后一行则不再刷新

    if(this->__curLyricsIndex  >=this->__veclyrics.size()-1 || this->__curLyricsIndex <0){
        return;
    }
    int next=this->__curLyricsIndex;
    LLData curLine  = this->__veclyrics.at(this->__curLyricsIndex);
    LLData nextLine  = this->__veclyrics.at(this->__curLyricsIndex+1);
//    if(nextLine.position > position){
//        return;
//    }
    if(position > nextLine.position){
        for(int i=this->__curLyricsIndex +1;i<this->__veclyrics.size();i++){
            if(this->__veclyrics.at(i).position > position){
                //如果出现一个position大于歌曲的postion，则此时在前一个
                next = i-1;
                break;
            }
        }
    }else if(position <curLine.position){
        for(int i=this->__curLyricsIndex -1;i>=this->__lyrics.lyricsBeginIndex();i--){
            if(this->__veclyrics.at(i).position < position){
                //如果出现一个position大于歌曲的postion，则此时在前一个
                next = i;
                break;
            }
        }
    }

    if(next == this->__curLyricsIndex)
        return;
    qDebug()<<"displayview"<<position;
    //则向下刷新一个



    QListWidgetItem* curitem = this->ui->listWidget->item(this->__curLyricsIndex);
    LyricsItemView* view  = (LyricsItemView*)this->ui->listWidget->itemWidget(curitem);
    //QModelIndex curmodelindex();this->ui->listWidget->childAt(this->__curLyricsIndex,0);
    //LyricsItemView* view = (LyricsItemView*) this->ui->listWidget->childAt(this->__curLyricsIndex,0);
    QSize listSize = this->ui->listWidget->size();
    view->setMode(LyricsItemView::ViewMode::NoPlaying);
    //view->resize(listSize.width(),28);
    //QListWidgetItem* newcuritem = new QListWidgetItem;


    QListWidgetItem* nextitem = this->ui->listWidget->item(next);
    LyricsItemView* nextview =  (LyricsItemView*)this->ui->listWidget->itemWidget(nextitem);

    nextview->setMode(LyricsItemView::ViewMode::Playing);
    //nextview->resize(listSize.width(),35);
    this->__curLyricsIndex = next;
}

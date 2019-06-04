#include "lyricsitemview.h"
#include "ui_lyricsitemview.h"

LyricsItemView::LyricsItemView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LyricsItemView)
{
    ui->setupUi(this);
}

LyricsItemView::LyricsItemView(LyricsItemView::ViewMode mode, QWidget *parent):
    QWidget(parent),
    ui(new Ui::LyricsItemView)
{
    ui->setupUi(this);
    this->setMode(mode);
}

LyricsItemView::~LyricsItemView()
{
    delete ui;
}

void LyricsItemView::setMode(LyricsItemView::ViewMode mode)
{
    if(mode == ViewMode::Playing){

        this->ui->label->setStyleSheet("QLabel{color: rgb(31, 255, 7);\
                                       font-size:10pt;\
                                       min-height:35p;}");

    }else if(mode ==ViewMode::NoPlaying){

        this->ui->label->setStyleSheet("QLabel{color: rgb(0, 0, 0)\
                                        min-height:35p;}");
    }
}

void LyricsItemView::setText(QString lineLyrics)
{
    this->ui->label->setText(lineLyrics);
}

QString LyricsItemView::getText()
{
    return this->ui->label->text();
}

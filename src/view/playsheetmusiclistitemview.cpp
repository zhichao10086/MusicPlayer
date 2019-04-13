#include "playsheetmusiclistitemview.h"
#include "ui_playsheetmusiclistitemview.h"

PlaySheetMusicListItemView::PlaySheetMusicListItemView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlaySheetMusicListItemView)
{
    ui->setupUi(this);
}

PlaySheetMusicListItemView::~PlaySheetMusicListItemView()
{
    delete ui;
}

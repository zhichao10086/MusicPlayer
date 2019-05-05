#include "searchmusicview.h"
#include "ui_searchmusicview.h"

SearchMusicView::SearchMusicView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchMusicView)
{
    ui->setupUi(this);
}

SearchMusicView::~SearchMusicView()
{
    delete ui;
}

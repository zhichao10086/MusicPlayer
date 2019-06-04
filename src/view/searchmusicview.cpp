#include "searchmusicview.h"
#include "ui_searchmusicview.h"


SearchMusicView* SearchMusicView::single_searchMusicView = nullptr;
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

SearchMusicView *SearchMusicView::newInstance()
{
    if(single_searchMusicView != nullptr)
        return single_searchMusicView;
    single_searchMusicView = new SearchMusicView;
    return single_searchMusicView;
}

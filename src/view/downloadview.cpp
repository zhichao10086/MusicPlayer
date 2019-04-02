#include "downloadview.h"
#include "ui_downloadview.h"

DownLoadView::DownLoadView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DownLoadView)
{
    ui->setupUi(this);
}

DownLoadView::~DownLoadView()
{
    delete ui;
}

DownLoadView::DownLoadView(DownLoadController *dlc, QWidget *p)
{
   this->_dlc = dlc;
   initView();
}

DownLoadController *DownLoadView::dlc() const
{
    return _dlc;
}

void DownLoadView::setDlc(DownLoadController *dlc)
{
    _dlc = dlc;
}

void DownLoadView::initView()
{
    ui = new Ui::DownLoadView;
    ui->setupUi(this);
}

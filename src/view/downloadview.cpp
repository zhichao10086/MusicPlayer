#include "downloadview.h"
#include "ui_downloadview.h"

DownloadView::DownloadView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DownloadView)
{
    ui->setupUi(this);
}

DownloadView::~DownloadView()
{
    delete ui;
}

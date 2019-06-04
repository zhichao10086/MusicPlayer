#include "musiclistheaderview.h"
#include "ui_musiclistheaderview.h"

MusicListHeaderVIew::MusicListHeaderVIew(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicListHeaderVIew)
{
    this->initView();

}

MusicListHeaderVIew::MusicListHeaderVIew(ViewMode viewmode, QWidget *parent):
    QWidget(parent),
    ui(new Ui::MusicListHeaderVIew)
{
    _viewmode = viewmode;
    this->initView();
}

MusicListHeaderVIew::~MusicListHeaderVIew()
{
    delete ui;
}

void MusicListHeaderVIew::initView()
{
    ui->setupUi(this);
}

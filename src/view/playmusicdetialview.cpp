#include "playmusicdetialview.h"
#include "ui_playmusicdetialview.h"

PlayMusicDetialView::PlayMusicDetialView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayMusicDetialView)
{
    this->__initView();
}

PlayMusicDetialView::PlayMusicDetialView(PlayMusicDetialController *pmdc, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayMusicDetialView)
{
    this->__playMusicDetialCtrl = pmdc;
    this->__initView();

}

PlayMusicDetialView::~PlayMusicDetialView()
{
    delete ui;
}

void PlayMusicDetialView::__initView()
{
    ui->setupUi(this);


}

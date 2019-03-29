#include "playfuncview.h"
#include "ui_playfuncview.h"

PlayFuncView::PlayFuncView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayFuncView)
{
    ui->setupUi(this);
}

PlayFuncView::PlayFuncView(PlayFuncController *pfc, QWidget *parent)
{
    //this->PlayFuncView(parent);

    this->_playFuncController = pfc;

    this->init();

}

PlayFuncView::~PlayFuncView()
{
    delete ui;
}

void PlayFuncView::init()
{

}

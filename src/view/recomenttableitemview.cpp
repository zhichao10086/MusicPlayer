#include "recomenttableitemview.h"
#include "ui_recomenttableitemview.h"

RecomentTableItemView::RecomentTableItemView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecomentTableItemView)
{
    ui->setupUi(this);
}

RecomentTableItemView::~RecomentTableItemView()
{
    delete ui;
}

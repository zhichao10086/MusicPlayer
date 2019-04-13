#include "musiclistwidget.h"
#include "ui_musiclistwidget.h"

MusicListWidget::MusicListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicListWidget)
{
    ui->setupUi(this);
}

MusicListWidget::~MusicListWidget()
{
    delete ui;
}

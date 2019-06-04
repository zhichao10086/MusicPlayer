#include "choosemusicsheetdialog.h"
#include "ui_choosemusicsheetdialog.h"

ChooseMusicSheetDialog::ChooseMusicSheetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseMusicSheetDialog)
{
    ui->setupUi(this);
}

ChooseMusicSheetDialog::ChooseMusicSheetDialog(QList<MusicSheet> musicSheets, QWidget *parent):
    QDialog(parent),
    ui(new Ui::ChooseMusicSheetDialog)
{
    ui->setupUi(this);
    this->__musicSheets = musicSheets;
    this->initView();
}

ChooseMusicSheetDialog::~ChooseMusicSheetDialog()
{
    delete ui;
}

void ChooseMusicSheetDialog::initView()
{
    QLayout* layout =  this->ui->groupBox->layout();
    for(int i=0;i<this->__musicSheets.size();i++){
        qDebug()<<"歌单";
        QCheckBox* checkBox = new QCheckBox();
        checkBox->setText(this->__musicSheets.at(i).sheetName());
        checkBox->setChecked(false);
        this->__checkBoxs.append(checkBox);

        layout->addWidget(checkBox);

    }
    this->ui->groupBox->setLayout(layout);
}

QVector<int> ChooseMusicSheetDialog::getMusicSheets()
{
    QVector<int> result;
    for(int i=0;i<this->__checkBoxs.size();i++){
        if(this->__checkBoxs.at(i)->isChecked()){
            result.append(i);
        }
    }
    return result;
}

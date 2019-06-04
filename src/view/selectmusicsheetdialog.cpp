#include "selectmusicsheetdialog.h"
#include "ui_selectmusicsheetdialog.h"

SelectMusicSheetDialog::SelectMusicSheetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectMusicSheetDialog)
{
    ui->setupUi(this);
}

SelectMusicSheetDialog::SelectMusicSheetDialog(QList<MusicSheet> musicSheets, QWidget *parent):
    QDialog(parent),
    ui(new Ui::SelectMusicSheetDialog)
{

    ui->setupUi(this);
    this->__musicSheets = musicSheets;
    this->initView();

}




SelectMusicSheetDialog::~SelectMusicSheetDialog()
{
    delete ui;
}

void SelectMusicSheetDialog::initView()
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

QVector<int> SelectMusicSheetDialog::getMusicSheets()
{
    QVector<int> result;
    for(int i=0;i<this->__checkBoxs.size();i++){
        if(this->__checkBoxs.at(i)->isChecked()){
            result.append(i);
        }
    }
    return result;
}

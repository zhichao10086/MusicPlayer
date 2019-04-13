#include "newmusicsheetdialog.h"
#include "ui_newmusicsheetdialog.h"

NewMusicSheetDialog::NewMusicSheetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewMusicSheetDialog)
{
    ui->setupUi(this);
}

NewMusicSheetDialog::~NewMusicSheetDialog()
{
    delete ui;
}

QString NewMusicSheetDialog::getValue()
{
    return this->musicSheetName;
}

QString NewMusicSheetDialog::getMusicSheetName() const
{
    return musicSheetName;
}

void NewMusicSheetDialog::setMusicSheetName(const QString &value)
{
    musicSheetName = value;
}

void NewMusicSheetDialog::on_buttonBox_accepted()
{
    this->musicSheetName = this->ui->lineEdit->text();
}

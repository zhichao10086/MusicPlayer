#include "choosedirsdialog.h"
#include "ui_choosedirsdialog.h"

ChooseDirsDialog::ChooseDirsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseDirsDialog)
{
    ui->setupUi(this);



}

ChooseDirsDialog::ChooseDirsDialog(QStringList dirs, QWidget *parent):
    QDialog(parent)
{

    ui = new Ui::ChooseDirsDialog;
    ui->setupUi(this);

    this->_dirs = dirs;
    initView();
}

ChooseDirsDialog::~ChooseDirsDialog()
{
    delete ui;
}

QStringList ChooseDirsDialog::dirs() const
{
    return _dirs;
}

void ChooseDirsDialog::setDirs(const QStringList &dirs)
{
    _dirs = dirs;
}


void ChooseDirsDialog::removeCheckDir()
{
    QVector<int> vecRemove;
    for(int i =0;i<this->_dirs.size();i++){
        QListWidgetItem* item = this->ui->lwDirList->item(i);
        QWidget* widget = ui->lwDirList->itemWidget(item);
        QCheckBox* box = (QCheckBox*)widget;
        if(box->checkState()){
            //如果选中则加入到要删除的
            this->_dirs.removeAt(i);
            this->ui->lwDirList->removeItemWidget(item);
            i--;
        }
    }
}

void ChooseDirsDialog::selectAll()
{
    for(int i =0;i<this->_dirs.size();i++){
        QListWidgetItem* item = this->ui->lwDirList->item(i);
        QWidget* widget = ui->lwDirList->itemWidget(item);
        QCheckBox* box = (QCheckBox*)widget;
        box->setChecked(true);
    }
}

void ChooseDirsDialog::initView()
{
    for(int i =0;i<this->_dirs.size();i++){
        QListWidgetItem* item = new QListWidgetItem;
        QCheckBox * box = new QCheckBox(this->_dirs.at(i));

        this->ui->lwDirList->addItem(item);
        this->ui->lwDirList->setItemWidget(item,box);
    }
}


void ChooseDirsDialog::on_pushButton_clicked()
{
    QString dir =  QFileDialog::getExistingDirectory(this,tr("请选择要浏览的文件夹"));
    cout<<dir.toStdString()<<endl;
    if(!dir.isEmpty()&& !Util::hasDuplicate(this->_dirs,dir) ){


        QListWidgetItem* item = new QListWidgetItem;
        QCheckBox * box = new QCheckBox(dir);

        this->ui->lwDirList->addItem(item);
        this->ui->lwDirList->setItemWidget(item,box);
        this->_dirs.append(dir);
    }

}

void ChooseDirsDialog::on_btnSelectAll_clicked()
{
    this->selectAll();
}

void ChooseDirsDialog::on_btnRemoveSelected_clicked()
{
    this->removeCheckDir();
}

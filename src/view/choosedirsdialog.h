#ifndef CHOOSEDIRSDIALOG_H
#define CHOOSEDIRSDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QUrl>
#include <QList>
#include <QListWidgetItem>
#include <QVector>
#include <QCheckBox>
#include <iostream>
#include "util.h"

using namespace std;

namespace Ui {
class ChooseDirsDialog;
}

class ChooseDirsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseDirsDialog(QWidget *parent = 0);

    ChooseDirsDialog(QStringList dirs,QWidget *parent=0);

    ~ChooseDirsDialog();


    QStringList _dirs;

    /*
     * 删掉选中文件夹
     */
    void removeCheckDir();

    /*
     * 选择全部
     */
    void selectAll();

    void initView();



    QStringList dirs() const;
    void setDirs(const QStringList &dirs);

private slots:
    void on_pushButton_clicked();

    void on_btnSelectAll_clicked();

    void on_btnRemoveSelected_clicked();

private:
    Ui::ChooseDirsDialog *ui;
};

#endif // CHOOSEDIRSDIALOG_H

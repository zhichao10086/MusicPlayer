#ifndef CHOOSEMUSICSHEETDIALOG_H
#define CHOOSEMUSICSHEETDIALOG_H

#include <QDialog>
#include <QList>
#include <QCheckBox>
#include "musicsheet.h"
#include <QVector>
#include <QLayout>


namespace Ui {
class ChooseMusicSheetDialog;
}

class ChooseMusicSheetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseMusicSheetDialog(QWidget *parent = 0);
    explicit ChooseMusicSheetDialog(QList<MusicSheet> musicSheets, QWidget *parent = 0);

    ~ChooseMusicSheetDialog();

    void initView();

    //获得歌单的序列
    QVector<int> getMusicSheets();

public slots:


private:
    Ui::ChooseMusicSheetDialog *ui;

    QList<QCheckBox*> __checkBoxs;
    QList<MusicSheet> __musicSheets;


};

#endif // CHOOSEMUSICSHEETDIALOG_H

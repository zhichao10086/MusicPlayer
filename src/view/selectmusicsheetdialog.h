#ifndef SELECTMUSICSHEETDIALOG_H
#define SELECTMUSICSHEETDIALOG_H

#include <QDialog>
#include <QList>
#include <QCheckBox>
#include "musicsheet.h"
#include <QVector>
#include <QLayout>

namespace Ui {
class SelectMusicSheetDialog;
}

class SelectMusicSheetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectMusicSheetDialog(QWidget *parent = 0);
    explicit SelectMusicSheetDialog(QList<MusicSheet> musicSheets, QWidget *parent = 0);
    ~SelectMusicSheetDialog();

    void initView();

    //获得歌单的序列
    QVector<int> getMusicSheets();

private:
    Ui::SelectMusicSheetDialog *ui;

    QList<QCheckBox*> __checkBoxs;
    QList<MusicSheet> __musicSheets;
};



#endif // SELECTMUSICSHEETDIALOG_H

#ifndef NEWMUSICSHEETDIALOG_H
#define NEWMUSICSHEETDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class NewMusicSheetDialog;
}

class NewMusicSheetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewMusicSheetDialog(QWidget *parent = 0);
    ~NewMusicSheetDialog();

    QString getValue();

    QString musicSheetName;

    QString getMusicSheetName() const;
    void setMusicSheetName(const QString &value);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::NewMusicSheetDialog *ui;
};

#endif // NEWMUSICSHEETDIALOG_H

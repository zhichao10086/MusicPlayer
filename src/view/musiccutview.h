#ifndef MUSICCUTVIEW_H
#define MUSICCUTVIEW_H

#include <QWidget>
#include <QFileDialog>
#include "multimusicfunc.h"
#include <QMessageBox>
#include <QThread>
#include "musiccutthread.h"
#include <QString>
#include <QDebug>

namespace Ui {
class MusicCutView;
}

class MusicCutView : public QWidget
{
    Q_OBJECT

public:
    explicit MusicCutView(QWidget *parent = 0);
    ~MusicCutView();

    void initView();

public slots:
    void showMessage(int);

private slots:
    void on_btnOpenFile_clicked();

    void on_btnOpenOutputPath_clicked();


    void on_btnStart_clicked();

private:
    Ui::MusicCutView *ui;
};

#endif // MUSICCUTVIEW_H

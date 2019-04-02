#ifndef DOWNLOADVIEW_H
#define DOWNLOADVIEW_H

#include <QWidget>
#include "downloadcontroller.h"

class DownLoadController;

namespace Ui {
class DownLoadView;
}

class DownLoadView : public QWidget
{
    Q_OBJECT

public:
    explicit DownLoadView(QWidget *parent = 0);


    DownLoadView(DownLoadController* dlc,QWidget* p = 0);


    DownLoadController* _dlc;

    void initView();

    ~DownLoadView();

    DownLoadController *dlc() const;
    void setDlc(DownLoadController *dlc);

private:
    Ui::DownLoadView *ui;
};

#endif // DOWNLOADVIEW_H

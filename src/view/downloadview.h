#ifndef DOWNLOADVIEW_H
#define DOWNLOADVIEW_H

#include <QWidget>
#include "downloadcontroller.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "downloadmusiclistitemview.h"
#include <QListWidgetItem>
#include <QDebug>
#include <QStringList>
#include "filefunccontroller.h"
#include "globalvariable.h"

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
    ~DownLoadView();

    void initView();

    //添加下载任务
    void addDownLoadTask(Music& music);

    //下载完成后
    void musicDownLoaded(int);

    //显示已下载的
    void updateDownloadedView();

    DownLoadController *dlc() const;
    void setDlc(DownLoadController *dlc);


    DownLoadController* _dlc;

    QList<Music> _downLoadingMusics;
    QList<Music> _downLoadedMusics;
private:
    Ui::DownLoadView *ui;

    QNetworkAccessManager* __netManager;
    QStringList __downloadDir;
    QList<Music> __downMusics;
};

#endif // DOWNLOADVIEW_H

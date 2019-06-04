#ifndef DOWNLOADMUSICLISTITEMVIEW_H
#define DOWNLOADMUSICLISTITEMVIEW_H

#include <QWidget>
#include "music.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "downloadmusiclistitemview.h"
#include "downloadview.h"
#include "musiclistitemmenu.h"
#include "QMessageBox"
#include "globalvariable.h"
#include <QDebug>
#include <QIODevice>
#include "downloadview.h"

namespace Ui {
class DownLoadMusicListItemView;
}

class MusicListItemMenu;
class DownLoadView;

class DownLoadMusicListItemView : public QWidget
{
    Q_OBJECT

public:
    enum ViewType{
        downLoading,
        downLoaded
    };

    explicit DownLoadMusicListItemView(QWidget *parent = 0);

    DownLoadMusicListItemView(int index,const Music& music,ViewType viewtype,QWidget *parent = 0);



    void initView();

    void musicDownLoading(qint64 bytesReceived, qint64 bytesTotal);

    void musicDownLoaded(QNetworkReply* reply);


    void readContent();

    ~DownLoadMusicListItemView();

    int _index;
    Music _music;

    MusicListItemMenu* _menu;

    void setDlView(DownLoadView *dlView);

public slots:
    void popupContextMenu(QPoint p);

private:
    Ui::DownLoadMusicListItemView *ui;
    QNetworkAccessManager* __netManager;
    QFile* __file;
    QNetworkReply* __reply;
    DownLoadView* __dlView;
};



#endif // DOWNLOADMUSICLISTITEMVIEW_H

#ifndef MUSICSHEETDETIALVIEW_H
#define MUSICSHEETDETIALVIEW_H

#include <QWidget>
#include "musicsheetdetialcontroller.h"
#include "music.h"
#include "musicsheet.h"
#include <QPixmap>
#include <QLabel>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include "globalvariable.h"
#include "globalconstant.h"
#include <QDebug>
#include <QListWidgetItem>
#include <musiclistitemview.h>

class MusicSheetDetialController;

namespace Ui {
class MusicSheetDetialView;
}

class MusicSheetDetialView : public QWidget
{
    Q_OBJECT

public:
    explicit MusicSheetDetialView(QWidget *parent = 0);

    MusicSheetDetialView(MusicSheetDetialController* msdCtrl,QWidget* parent= 0);
    ~MusicSheetDetialView();

    void initView();




    /*
     *更新画面
     */
    void updateView(const MusicSheet& musicSheet);


public slots:

    void imageFinished(QNetworkReply *reply);

    void headImageFinished(QNetworkReply* reply);

    //刷新歌曲界面
    void updateMusicListView(QList<Music> musics);

private:
    Ui::MusicSheetDetialView *ui;
    MusicSheetDetialController* __msdCtrl;

    QNetworkAccessManager* __netManager;
    MusicSheet __musicSheet;
};

#endif // MUSICSHEETDETIALVIEW_H

#ifndef MUSICPLAYERVIEW_H
#define MUSICPLAYERVIEW_H

#include <QWidget>
#include "musicplayercontroller.h"
#include "playfuncview.h"
#include <iostream>
#include <QLabel>
#include <QWidget>
#include <QLayoutItem>
#include <QUrl>


namespace Ui {
class MusicPlayerView;
}

using namespace std;
class MusicPlayerController;

class MusicPlayerView : public QWidget
{
    Q_OBJECT

public:
    explicit MusicPlayerView(QWidget *parent = 0);

    MusicPlayerView(MusicPlayerController* mpc);
    ~MusicPlayerView();




    QPoint _dragPosition;


    void init_view();

    /*
     *设置背景
     */
    void setBackgroundImage(QPixmap& p);

    void setBackground(QUrl);

    /*
     * 设置当前主界面
     */
    void setMainWindowWidget(QWidget* w);

    /*
     * 获取当前主界面的指针
     */
    QWidget* getCurMainWindowWidget();

    void removeMainWindowWidget();



    MusicPlayerController* _musicPlayerController;
    QWidget* _curMainWindowWidget = nullptr;




private slots:
    void on_btnLocalFile_clicked();

    void on_btnDownload_clicked();

    void on_btnClose_clicked();

    void on_btnMinWindow_clicked();

    void on_btnMaxWindow_clicked();

private:
    Ui::MusicPlayerView *ui;
};

#endif // MUSICPLAYERVIEW_H

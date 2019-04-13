#ifndef QMENUBUTTON_H
#define QMENUBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QMenu>
#include <QAction>
#include <QMediaPlayer>
#include <QMediaPlaylist>

namespace Ui {
class QMenuButton;
}

class QMenuButton : public QPushButton
{
    Q_OBJECT

public:
    explicit QMenuButton(QWidget *parent = 0);
    ~QMenuButton();

    QMenu *getMenu();

    void initView();

    QAction *actionShunXu ;
    QAction *actionSuiJi  ;
    QAction *actionXunHuan;
    QAction *actionDanQu  ;

signals:
    void changePlayBackMode(QMediaPlaylist::PlaybackMode);

public slots:
    void popupMenu();


private:
    Ui::QMenuButton *ui;
    QMenu* __menu;
};

#endif // QMENUBUTTON_H

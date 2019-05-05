#ifndef MUSICLISTITEMVIEW_H
#define MUSICLISTITEMVIEW_H

#include <QWidget>
#include "music.h"
#include <QString>
#include <iostream>
#include <QSize>
#include <QFont>
#include <QLabel>
#include <QAction>
#include <QMenu>
#include "globalvariable.h"

using namespace std;

namespace Ui {
class MusicListItemView;
}

class MusicListItemView : public QWidget
{
    Q_OBJECT



public:
    enum ViewMode{
        LocalMusicListItem,
        SearchMusicListItem,
        PlaySheetListItem,
        RecentSheetListItem,
        MusicSheetListItem
    };


    explicit MusicListItemView(QWidget *parent = 0);

    MusicListItemView(int index, Music music,ViewMode mode,QWidget *parent = 0);
    ~MusicListItemView();

    QMenu* _menu;

    QMenu* _collectMenu;
    QAction* _actionPlay;
    QAction* _actionCollect;
    QAction* _actionNextPlay;
    QAction* _actionDownload;
    QList<QAction*> _collectActions;




    //重写
    //bool eventFilter(QObject *watched, QEvent *event);


    void setTextElide(QLabel* label,QString string);

    void localMusicListItemShow();

    void searchMusicListItemShow();

    void playSheetListItemShow();

    void recentSheetListItemShow();

    void MusicSheetListItemShow();

    void initView();




    Music music() const;
    void setMusic(const Music &music);

private slots:

    void popupContextMenu(QPoint p);

private:
    Ui::MusicListItemView *ui;

    Music __music;
    int __index;
};

#endif // MUSICLISTITEMVIEW_H

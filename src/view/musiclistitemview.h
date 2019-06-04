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
#include "musiclistitemmenu.h"

using namespace std;

enum class MusicItemViewMode{
    LocalMusicListItem,
    SearchMusicListItem,
    PlaySheetListItem,
    RecentSheetListItem,
    MusicSheetListItem,
};


namespace Ui {
class MusicListItemView;
}

class MusicListItemMenu;


class MusicListItemView : public QWidget
{
    Q_OBJECT


public:




    explicit MusicListItemView(QWidget *parent = 0);

    MusicListItemView(int index, Music music,MusicItemViewMode mode,QWidget *parent = 0);
    ~MusicListItemView();

    MusicListItemMenu* _menu;

    /*
    QMenu* _menu;

    QMenu* _collectMenu;
    QAction* _actionPlay;
    QAction* _actionCollect;
    QAction* _actionNextPlay;
    QAction* _actionDownload;
    QList<QAction*> _collectActions;
    */



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

#ifndef MUSICLISTITEMVIEW_H
#define MUSICLISTITEMVIEW_H

#include <QWidget>
#include "music.h"
#include <QString>
#include <iostream>
#include <QSize>

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
        RecentSheetListItem
    };


    explicit MusicListItemView(QWidget *parent = 0);

    MusicListItemView(int index, Music music,ViewMode mode,QWidget *parent = 0);
    ~MusicListItemView();


    void localMusicListItemShow();

    void searchMusicListItemShow();

    void playSheetListItemShow();

    void recentSheetListItemShow();

    void initView();




    Music music() const;
    void setMusic(const Music &music);

private:
    Ui::MusicListItemView *ui;

    Music __music;
    int __index;
};

#endif // MUSICLISTITEMVIEW_H

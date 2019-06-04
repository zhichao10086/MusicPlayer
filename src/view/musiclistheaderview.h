#ifndef MUSICLISTHEADERVIEW_H
#define MUSICLISTHEADERVIEW_H

#include <QWidget>
#include "musiclistitemview.h"



namespace Ui {
class MusicListHeaderVIew;
}


class MusicListHeaderVIew : public QWidget
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

    explicit MusicListHeaderVIew(QWidget *parent = 0);
    MusicListHeaderVIew(ViewMode viewmode ,QWidget *parent = 0);
    ~MusicListHeaderVIew();


     void initView();

     ViewMode _viewmode;
private:
    Ui::MusicListHeaderVIew *ui;
};

#endif // MUSICLISTHEADERVIEW_H

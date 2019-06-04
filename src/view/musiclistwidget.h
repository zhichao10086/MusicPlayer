#ifndef MUSICLISTWIDGET_H
#define MUSICLISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QList>
#include <QListWidgetItem>
#include "musiclistitemview.h"
#include "music.h"
#include "globalconstant.h"
#include "musiclistheaderview.h"
#include <QMediaPlayer>

using namespace std;

namespace Ui {
class MusicListWidget;
}


enum class MusicItemViewMode;

//class MusicListItemView;

class MusicListWidget : public QListWidget
{
    Q_OBJECT

public:
    explicit MusicListWidget(QWidget *parent = 0);
    ~MusicListWidget();


    MusicItemViewMode _itemViewMode;


    void initView();
    void updateView(QList<Music>& musics);


    MusicItemViewMode getItemViewMode() const;
    void setItemViewMode( MusicItemViewMode value);

private:
    Ui::MusicListWidget *ui;
    QList<Music> __musics;

    // QWidget interface
protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // MUSICLISTWIDGET_H

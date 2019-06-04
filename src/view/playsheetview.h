#ifndef PLAYSHEETVIEW_H
#define PLAYSHEETVIEW_H

#include <QWidget>
#include "playsheetcontroller.h"
#include <QDebug>
#include <QMouseEvent>
#include "music.h"
#include <QPushButton>
#include <QLabel>
#include <QListWidgetItem>
#include <QSize>
#include <QListWidget>
#include "musiclistitemview.h"
#include "musicsheet.h"
#include <QModelIndex>
#include <Qlist>


namespace Ui {
class PlaySheetView;
}

class PlaySheetController;

class PlaySheetView : public QWidget
{
    Q_OBJECT

public:
    explicit PlaySheetView(QWidget *parent = 0);

    PlaySheetView(PlaySheetController* pfc, QWidget *parent = 0);
    ~PlaySheetView();


    bool isFilter = false;

    bool eventFilter(QObject *o, QEvent *e);

    void initView();

    void updateListWidgetPlaySheet(const MusicSheet& musicSheet);

    void updateListWidgetRecentPlaySheet(const MusicSheet& musicSheet);


    PlaySheetController *pfCtrl() const;
    void setPfCtrl(PlaySheetController *pfCtrl);

    bool getIsFilter() const;
    void setIsFilter(bool value);

private slots:
    //void on_lwplaySheet_itemDoubleClicked(QListWidgetItem *item);

    void on_lwplaySheet_doubleClicked(const QModelIndex &index);

private:
    Ui::PlaySheetView *ui;
    PlaySheetController *__pfCtrl;
};

#endif // PLAYSHEETVIEW_H

#ifndef MUSICLISTITEMMENU_H
#define MUSICLISTITEMMENU_H

#include <QWidget>
#include <QMenu>
#include <QACtion>
#include "downloadcontroller.h"
#include "music.h"
#include <QDebug>
#include "selectmusicsheetdialog.h"
#include "globalvariable.h"


namespace Ui {
class MusicListItemMenu;
}

class MusicListItemMenu : public QMenu
{
    Q_OBJECT

public:
    explicit MusicListItemMenu(QWidget *parent = 0);
    MusicListItemMenu(const Music& music,QWidget *parent = 0);

    ~MusicListItemMenu();

    static QAction* single_actionPlay;


    void initView();




    QAction* _actionPlay;
    QAction* _actionDownload;
    QAction* _actionNextPlay;
    QAction* _actionCollect ;


    QMenu* _collectMenu;


    Music _music;

public slots:
    void actionDownLoad();
    void actionCollectDialogShow();


private:
    Ui::MusicListItemMenu *ui;
};

#endif // MUSICLISTITEMMENU_H

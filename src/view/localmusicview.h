#ifndef LOCALMUSICVIEW_H
#define LOCALMUSICVIEW_H

#include <QWidget>
#include "localmusiccontroller.h"
#include "choosedirsdialog.h"



namespace Ui {
class LocalMusicView;
}

class LocalMusicController;


class LocalMusicView : public QWidget
{
    Q_OBJECT

public:
    explicit LocalMusicView(QWidget *parent = 0);

    LocalMusicView(LocalMusicController* lmc,QWidget* parent = 0);
    ~LocalMusicView();

    void init();

    void init_view();

    void updateListWidget(QVector<Music> &musics);

    void clearMusicListWidget();


    LocalMusicController* _localMusicCtrl;


private slots:
    void on_btnOpenDir_clicked();

    void on_lwMusicList_doubleClicked(const QModelIndex &index);

private:
    Ui::LocalMusicView *ui;
};

#endif // LOCALMUSICVIEW_H

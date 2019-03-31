#ifndef PLAYFUNCVIEW_H
#define PLAYFUNCVIEW_H

#include <QWidget>
#include <playfunccontroller.h>

class PlayFuncController;

namespace Ui {
class PlayFuncView;
}

class PlayFuncView : public QWidget
{
    Q_OBJECT

public:
    explicit PlayFuncView(QWidget *parent = 0);

    PlayFuncView(PlayFuncController* pfc, QWidget *parent = 0);

    ~PlayFuncView();

    PlayFuncController* _playFuncController;

    void init();

    void init_view();

    void setStartView();

    void setPauseView();

    void setBackgroundImage(QPixmap& p);



private slots:
    void on_btnStartOrPause_clicked();

    void on_btnNext_clicked();

    void on_btnPre_clicked();

private:
    Ui::PlayFuncView *ui;
};

#endif // PLAYFUNCVIEW_H

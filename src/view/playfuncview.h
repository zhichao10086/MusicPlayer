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



private:
    Ui::PlayFuncView *ui;
};

#endif // PLAYFUNCVIEW_H

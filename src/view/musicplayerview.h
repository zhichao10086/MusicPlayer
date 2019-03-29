#ifndef MUSICPLAYERVIEW_H
#define MUSICPLAYERVIEW_H

#include <QWidget>
#include "musicplayercontroller.h"

namespace Ui {
class MusicPlayerView;
}

class MusicPlayerController;

class MusicPlayerView : public QWidget
{
    Q_OBJECT

public:
    explicit MusicPlayerView(QWidget *parent = 0);

    MusicPlayerView(MusicPlayerController* mpc);
    ~MusicPlayerView();


    MusicPlayerController* _musicPlayerController;

private:
    Ui::MusicPlayerView *ui;
};

#endif // MUSICPLAYERVIEW_H

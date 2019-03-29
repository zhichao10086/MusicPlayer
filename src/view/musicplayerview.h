#ifndef MUSICPLAYERVIEW_H
#define MUSICPLAYERVIEW_H

#include <QMainWindow>
#include <musicplayercontroller.h>

class MusicPlayerController;

namespace Ui {
class MusicPlayerView;
}

class MusicPlayerView : public QMainWindow
{
    Q_OBJECT

public:

    MusicPlayerController* _musicPlayerController;

    MusicPlayerView(){}

    MusicPlayerView(MusicPlayerController*,QWidget *);

    explicit MusicPlayerView(QWidget *parent = 0);
    ~MusicPlayerView();



private:
    Ui::MusicPlayerView *ui;
};

#endif // MUSICPLAYERVIEW_H

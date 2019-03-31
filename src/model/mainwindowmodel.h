#ifndef MAINWINDOWMODEL_H
#define MAINWINDOWMODEL_H

#include <musicplayercontroller.h>
#include "musicplayercontroller.h"
#include "musicplayerview.h"


class MainWindowmodel
{
public:
    MainWindowmodel();

    MusicPlayerController* _musicPlayerController;
    MusicPlayerView* _musicPlayerView;

    void init();

    MusicPlayerView *getMusicPlayerView() const;
};

#endif // MainWindowmodel_H

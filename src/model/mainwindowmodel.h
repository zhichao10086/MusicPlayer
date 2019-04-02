#ifndef MAINWINDOWMODEL_H
#define MAINWINDOWMODEL_H

#include <musicplayercontroller.h>
#include "musicplayercontroller.h"
#include "musicplayerview.h"
#include <iostream>

using namespace std;

class MusicPlayerController;
class MusicPlayerView;

class MainWindowmodel
{
public:
    MainWindowmodel();

    MainWindowmodel(MainWindowController* mwc);

    MainWindowController* _mainWindowCtrl;

    MusicPlayerController* _musicPlayerController;
    MusicPlayerView* _musicPlayerView;

    void init();

    MusicPlayerView *getMusicPlayerView() const;
};

#endif // MainWindowmodel_H

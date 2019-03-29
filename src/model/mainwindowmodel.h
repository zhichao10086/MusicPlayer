#ifndef MAINWINDOWMODEL_H
#define MAINWINDOWMODEL_H

#include <musicplayercontroller.h>



class MainWindowmodel
{
public:
    MainWindowmodel();


    MusicPlayerController* _musicPlayerController;

    MusicPlayerController *musicPlayerController() const;
    void setMusicPlayerController(MusicPlayerController *musicPlayerController);
};

#endif // MainWindowmodel_H

#ifndef MUSICPLAYERCONTROLLER_H
#define MUSICPLAYERCONTROLLER_H

#include "musicplayermodel.h"
#include <musicplayerview.h>


class MusicPlayerModel;
class MusicPlayerView;


class MusicPlayerController
{
public:
    MusicPlayerController();

    static MusicPlayerController* newInstance();


    MusicPlayerModel* _musicPlayerModel;
    MusicPlayerView* _musicPlayerView;


    //初始化controller
    void init();


    void show();

    MusicPlayerView *musicPlayerView() const;
    void setMusicPlayerView(MusicPlayerView *musicPlayerView);
};

#endif // MUSICPLAYERCONTROLLER_H

#ifndef MUSICPLAYERMODEL_H
#define MUSICPLAYERMODEL_H

#include "playfunccontroller.h"
#include "localmusiccontroller.h"




class MusicPlayerModel
{
public:
    MusicPlayerModel();

    /*
     *初始化需要的变量
     */
    void init();


    /*
     *要初始化的变量
     */
    PlayFuncController* _pfc;
    PlayFuncView *_pfView;
    PlayFuncModel* _pfModel;

    LocalMusicController* _localMusicCtrl;
    LocalMusicModel* _localMusicModel;
    LocalMusicView* _localMusicView;



    PlayFuncView *pfView() const;
    void setPfView(PlayFuncView *pfView);
    LocalMusicView *localMusicView() const;
    LocalMusicController *localMusicCtrl() const;
};

#endif // MUSICPLAYERMODEL_H

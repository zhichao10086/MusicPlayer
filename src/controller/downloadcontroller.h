#ifndef DOWNLOADCONTROLLER_H
#define DOWNLOADCONTROLLER_H

#include <QObject>
#include "musicplayercontroller.h"
#include "downloadmodel.h"
#include "downloadview.h"
#include "playfunccontroller.h"


class DownLoadModel;
class DownLoadView;
class MusicPlayerController;



class DownLoadController
{
public:
    DownLoadController();

    DownLoadController(PlayFuncController* pfc);


    void init();


    PlayFuncController* _pfc;

    //MusicPlayerController* _mpc;

    DownLoadModel* _downLoadModel;
    DownLoadView* _downLoadView;

    DownLoadModel *downLoadModel() const;
    void setDownLoadModel(DownLoadModel *downLoadModel);

    DownLoadView *downLoadView() const;
    void setDownLoadView(DownLoadView *downLoadView);
};

#endif // DOWNLOADCONTROLLER_H

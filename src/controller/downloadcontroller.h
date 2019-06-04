#ifndef DOWNLOADCONTROLLER_H
#define DOWNLOADCONTROLLER_H

#include <QObject>
#include "musicplayercontroller.h"
#include "downloadmodel.h"
#include "downloadview.h"
#include "playfunccontroller.h"
#include <QDebug>


class DownLoadModel;
class DownLoadView;
class MusicPlayerController;



class DownLoadController:public QObject
{
public:
    explicit DownLoadController(QObject *parent = nullptr);


    DownLoadController(PlayFuncController* pfc);

    static DownLoadController* single_downLoadCtrl;
    static DownLoadController* newInstance();


    enum retCode{
        DownLoading,
        DownLoaded,
        NotDownLoad
    };

    void init();



    /*
     * 添加下载任务
     */
    retCode addDownLoadTask(Music& music);



    PlayFuncController* _pfc;

    //MusicPlayerController* _mpc;

    DownLoadModel* _downLoadModel;
    DownLoadView* _downLoadView;

    DownLoadModel *downLoadModel() const;
    void setDownLoadModel(DownLoadModel *downLoadModel);

    DownLoadView *downLoadView() const;
    void setDownLoadView(DownLoadView *downLoadView);

signals:

public slots:



private:

};

#endif // DOWNLOADCONTROLLER_H

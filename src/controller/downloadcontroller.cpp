#include "downloadcontroller.h"

DownLoadController* DownLoadController::single_downLoadCtrl = nullptr;


DownLoadController::DownLoadController(QObject *parent):QObject(parent)
{
    this->init();
}

DownLoadController::DownLoadController(PlayFuncController* pfc)
{
    this->_pfc = pfc;
    this->init();
}

DownLoadController *DownLoadController::newInstance()
{
    if(single_downLoadCtrl != nullptr)
        return single_downLoadCtrl;
    single_downLoadCtrl = new DownLoadController;
    return single_downLoadCtrl;
}

void DownLoadController::init()
{
    this->_downLoadModel = new DownLoadModel;
    this->_downLoadView = new DownLoadView(this);
}

DownLoadController::retCode DownLoadController::addDownLoadTask(Music &music)
{
    qDebug()<<"add download";
    this->_downLoadView->addDownLoadTask(music);
}

DownLoadView *DownLoadController::downLoadView() const
{
    return _downLoadView;
}

void DownLoadController::setDownLoadView(DownLoadView *downLoadView)
{
    _downLoadView = downLoadView;
}


DownLoadModel *DownLoadController::downLoadModel() const
{
    return _downLoadModel;
}

void DownLoadController::setDownLoadModel(DownLoadModel *downLoadModel)
{
    _downLoadModel = downLoadModel;
}

#include "downloadcontroller.h"

DownLoadController::DownLoadController()
{

}

DownLoadController::DownLoadController(PlayFuncController* pfc)
{
    this->_pfc = pfc;
    this->init();
}

void DownLoadController::init()
{
    this->_downLoadModel = new DownLoadModel;
    this->_downLoadView = new DownLoadView(this);
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

#include "localmusicmodel.h"

LocalMusicModel::LocalMusicModel()
{
    this->init();
}

LocalMusicModel::LocalMusicModel(PlayFuncController *pfc):
    _playFuncCtrl(pfc)
{

}

PlayFuncController *LocalMusicModel::getPlayFuncCtrl() const
{
    return _playFuncCtrl;
}

void LocalMusicModel::setPlayFuncCtrl(PlayFuncController *value)
{
    _playFuncCtrl = value;
}

QVector<Music>& LocalMusicModel::musics()
{
    return _musics;
}

void LocalMusicModel::setMusics(const QVector<Music> &musics)
{
    _musics = musics;
}


QStringList LocalMusicModel::dirs() const
{
    return _dirs;
}

void LocalMusicModel::setDirs(const QStringList &dirs)
{
    _dirs = dirs;
}

void LocalMusicModel::init()
{
    this->_dirs.append("./local");
}

void LocalMusicModel::setMusicsfromStringList(QStringList &list)
{
    for(int i =0;i<list.size();i++){
        Music music(list.at(i));
        //拆分文件名
    }
}

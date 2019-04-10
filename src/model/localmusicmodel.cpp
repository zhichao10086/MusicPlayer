#include "localmusicmodel.h"

LocalMusicModel::LocalMusicModel()
{
    this->init();
}

LocalMusicModel::LocalMusicModel(PlayFuncController *pfc):
    _playFuncCtrl(pfc)
{

}

MusicSheet LocalMusicModel::getMusicSheet() const
{
    return _musicSheet;
}

void LocalMusicModel::setMusicSheet(const MusicSheet &musicSheet)
{
    _musicSheet = musicSheet;
}

PlayFuncController *LocalMusicModel::getPlayFuncCtrl() const
{
    return _playFuncCtrl;
}

void LocalMusicModel::setPlayFuncCtrl(PlayFuncController *value)
{
    _playFuncCtrl = value;
}

QList<Music>& LocalMusicModel::musics()
{
    return _musics;
}

void LocalMusicModel::setMusics(const QList<Music> &musics)
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

Music LocalMusicModel::getMusicByIndex(const QModelIndex &index)
{
    return this->_musicSheet.musics().at(index.row());
}

void LocalMusicModel::setMusicsfromStringList(QStringList &list)
{
    for(int i =0;i<list.size();i++){
        Music music(list.at(i));
        //拆分文件名
    }
}

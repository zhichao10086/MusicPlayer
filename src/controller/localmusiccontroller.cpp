#include "localmusiccontroller.h"
#include "util.h"
#include <iostream>

LocalMusicController::LocalMusicController()
{
    this->init();
}

LocalMusicController::LocalMusicController(PlayFuncController *pfc)
{
    this->init();
    this->_localMusicModel->setPlayFuncCtrl(pfc);

}

void LocalMusicController::init()
{
    this->_localMusicModel = new LocalMusicModel;
    this->_localMusicView = new LocalMusicView(this);
    this->_localMusicModel->setMusics(this->searchMusics(this->_localMusicModel->dirs()));
    this->_localMusicView->updateListWidget(this->_localMusicModel->musics());
    //this->addMusicsToMedia();

}

void LocalMusicController::showChooseDirsDialog()
{
    ChooseDirsDialog* cdd = new ChooseDirsDialog(this->localMusicModel()->dirs(),this->_localMusicView);

    if(cdd->exec() == QDialog::Accepted){
        this->_localMusicModel->setDirs(cdd->dirs());
    }

    QStringList dirs = cdd->dirs();

    //files 是绝对路径
    QVector<Music> musics = this->searchMusics(dirs);

    this->localMusicModel()->setMusics(musics);

    this->_localMusicView->updateListWidget(musics);

}

QVector<Music> LocalMusicController::searchMusics(QStringList dirs)
{


    QStringList files;
    QStringList filenames;
    QVector<Music> musics;

    std::cout<<dirs.size()<<endl;
    for(int i=0;i<dirs.size();i++){

        files.append(Util::getAbsoluteFileNames(dirs.at(i)));
        filenames.append(Util::getFileNames(dirs.at(i)));

    }
    for(int i=0;i<files.size();i++){
        Music music(files.at(i));
        music.setMusicName(filenames.at(i));
        musics.append(music);
    }

    return musics;
//    for(int i =0;i<files.size();i++){

//        //cout<<((QString)files.at(i)).toStdString()<<endl;

//    }

}

Music LocalMusicController::getMusic(int index)
{
    return this->_localMusicModel->musics().at(index);
}

void LocalMusicController::playMusic(const QModelIndex &index)
{
    //找到歌曲位置
    Music music = this->localMusicModel()->musics().at(index.row());
    //this->_localMusicModel->getPlayFuncCtrl()->playMusic(music);
    //添加本地歌单至歌曲库
    this->addMusicsToMedia();
    this->localMusicModel()->getPlayFuncCtrl()->setCurrentMusic(index.row());
    this->localMusicModel()->getPlayFuncCtrl()->play();

}

void LocalMusicController::addMusicsToMedia()
{
    PlayFuncController* pfc = this->_localMusicModel->getPlayFuncCtrl();
    pfc->setCurrentMusicList(this->localMusicModel()->musics());
}


LocalMusicView *LocalMusicController::localMusicView() const
{
    return _localMusicView;
}

void LocalMusicController::setLocalMusicView(LocalMusicView *localMusicView)
{
    _localMusicView = localMusicView;
}

void LocalMusicController::setCurIndexOnMusicList(int index)
{
    this->localMusicView()->setCurListWidgetIndex(index);
}

LocalMusicModel *LocalMusicController::localMusicModel() const
{
    return _localMusicModel;
}

void LocalMusicController::setLocalMusicModel(LocalMusicModel *localMusicModel)
{
    _localMusicModel = localMusicModel;
}

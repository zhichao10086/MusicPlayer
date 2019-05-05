#include "localmusiccontroller.h"
#include "util.h"
#include <iostream>
#include "mp3header.h"

LocalMusicController::LocalMusicController()
{
    this->init();
}

LocalMusicController::LocalMusicController(PlayFuncController *pfc)
{
    this->init(pfc);


}

void LocalMusicController::init()
{

}

void LocalMusicController::init(PlayFuncController *pfc)
{
    this->_localMusicModel = new LocalMusicModel;
    this->_localMusicModel->setPlayFuncCtrl(pfc);
    this->_localMusicView = new LocalMusicView(this);

    qDebug()<<"开始搜索";
    this->_localMusicModel->setMusics(this->searchMusics(this->_localMusicModel->dirs()));
    this->_localMusicView->updateListWidget(this->_localMusicModel->musics());

    MusicSheet ms;
    ms.setSheetName(QString("本地音乐"));
    ms.setMusics(this->_localMusicModel->musics());
    this->_localMusicModel->setMusicSheet(ms);
    this->addSheetToMedia();
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
    QList<Music> musics = this->searchMusics(dirs);

    //this->localMusicModel()->setMusics(musics);
    MusicSheet ms =  this->localMusicModel()->getMusicSheet();
    ms.setMusics(musics);

    this->_localMusicView->updateListWidget(musics);

}

QList<Music> LocalMusicController::searchMusics(QStringList dirs)
{


    QStringList files;
    QStringList filenames;
    QList<Music> musics;

    std::cout<<dirs.size()<<endl;
    for(int i=0;i<dirs.size();i++){

        files.append(Util::getAbsoluteFileNames(dirs.at(i)));
        filenames.append(Util::getFileNames(dirs.at(i)));

    }

    musics =  FileFuncController::fromFilesGetMusicTags(files);




    qDebug()<<"搜索结束";
    return musics;
//    for(int i =0;i<files.size();i++){

//        //cout<<((QString)files.at(i)).toStdString()<<endl;

//    }

}

MusicSheet LocalMusicController::getCurMusicSheet()
{
    return this->localMusicModel()->getPlayFuncCtrl()->currentMusicSheet();
}



Music LocalMusicController::getMusic(int index)
{
    return this->_localMusicModel->musics().at(index);
}

void LocalMusicController::playMusic(int index)
{
    //找到歌曲位置
    //Music music = this->localMusicModel()->musics().at(index.row());
    //this->_localMusicModel->getPlayFuncCtrl()->playMusic(music);
    //添加本地歌单至歌曲库
    //this->addMusicsToMedia();
    //this->localMusicModel()->getPlayFuncCtrl()->setCurrentMusic(index.row());
    this->localMusicModel()->getPlayFuncCtrl()->playMusic(index);

}

void LocalMusicController::playMusic(const QModelIndex& index)
{
    const Music& music  = this->localMusicModel()->getMusicSheet().musics().at(index.row());
    this->localMusicModel()->getPlayFuncCtrl()->playMusic(music);
}

int LocalMusicController::addMusicToCurSheet(const QModelIndex &index)
{
    Music music = this->_localMusicModel->getMusicByIndex(index);

    return this->_localMusicModel->getPlayFuncCtrl()->addMusicToCurMusicSheet(music);
}

void LocalMusicController::addMusicsToMedia()
{
    PlayFuncController* pfc = this->_localMusicModel->getPlayFuncCtrl();
    pfc->setCurrentMusicSheet(this->localMusicModel()->getMusicSheet());
}

void LocalMusicController::addSheetToMedia()
{
    PlayFuncController* pfc = this->_localMusicModel->getPlayFuncCtrl();
    pfc->setCurrentMusicSheet(this->_localMusicModel->getMusicSheet());
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

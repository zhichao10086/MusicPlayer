#include "musiclistitemmenu.h"
#include "ui_musiclistitemmenu.h"

MusicListItemMenu::MusicListItemMenu(QWidget *parent) :
    QMenu(parent),
    ui(new Ui::MusicListItemMenu)
{
    ui->setupUi(this);
    this->initView();
}

MusicListItemMenu::MusicListItemMenu(const Music& music, QWidget *parent):
    QMenu(parent),
    ui(new Ui::MusicListItemMenu)
{
    ui->setupUi(this);
    this->initView();
    this->_music = music;
    qDebug()<<"item:  "<<this->_music.musicID();
}

MusicListItemMenu::~MusicListItemMenu()
{
    delete ui;
}

void MusicListItemMenu::initView()
{

    this->_actionPlay = new QAction("播放");
    this->_actionDownload = new QAction("下载");
    this->_actionNextPlay = new QAction("下一首播放");
    this->_actionCollect = new QAction("收藏到歌单");
    this->addAction(this->_actionPlay);
    this->addAction(this->_actionNextPlay);
    this->addAction(this->_actionDownload);
    this->addAction(this->_actionCollect);

    //this->_collectMenu = new QMenu("收藏到歌单");

    QObject::connect(this->_actionDownload,&QAction::triggered,this,&MusicListItemMenu::actionDownLoad);
    QObject::connect(this->_actionCollect,&QAction::triggered,this,&MusicListItemMenu::actionCollectDialogShow);

}

void MusicListItemMenu::actionDownLoad()
{
    qDebug()<<"dianjixiazia";
    DownLoadController* dlCtrl =  DownLoadController::newInstance();
    dlCtrl->addDownLoadTask(this->_music);

}

void MusicListItemMenu::actionCollectDialogShow()
{
    QList<MusicSheet> musics =  GlobalVariable::get_global_User().createdMusicSheets();
    SelectMusicSheetDialog* smsDialog = new SelectMusicSheetDialog(musics);
    if(smsDialog->exec() == QDialog::Accepted){
        QVector<int> musicsIndex =  smsDialog->getMusicSheets();
        for(int i=0;i<musicsIndex.size();i++){
            qDebug()<<musics.value(i).sheetName();
            GlobalVariable::get_global_User().addMusicToCreatedMusicSheet(this->_music,i,musics.value(i));
        }
    }
}

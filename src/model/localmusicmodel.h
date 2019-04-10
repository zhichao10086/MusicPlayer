#ifndef LOCALMUSICMODEL_H
#define LOCALMUSICMODEL_H


#include <QUrl>
#include <QStringList>
#include "music.h"
#include "playfunccontroller.h"
#include "musicsheet.h"
#include <QList>

class PlayFuncController;

class LocalMusicModel
{
public:
    LocalMusicModel();

    LocalMusicModel(PlayFuncController* pfc);

    QStringList _dirs;

    MusicSheet _musicSheet;

    QList<Music> _musics;
    

    //播放的控制器
    PlayFuncController* _playFuncCtrl;



    void init();


    Music getMusicByIndex(const QModelIndex& index);

    /*
     * 文件路径列表
     *
     */
    void setMusicsfromStringList(QStringList& list);


    QStringList dirs() const;
    void setDirs(const QStringList &dirs);

    QList<Music>& musics();
    void setMusics(const QList<Music> &musics);
    void setPlayFuncCtrl(PlayFuncController *value);
    PlayFuncController *getPlayFuncCtrl() const;
    MusicSheet getMusicSheet() const;
    void setMusicSheet(const MusicSheet &musicSheet);
};

#endif // LOCALMUSICMODEL_H

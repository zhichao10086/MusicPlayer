#ifndef PLAYSHEETMODEL_H
#define PLAYSHEETMODEL_H

#include <QObject>
#include "playfunccontroller.h"
#include "musicsheet.h"

class PlayFuncController;

class PlaySheetModel : public QObject
{
    Q_OBJECT
public:
    explicit PlaySheetModel(QObject *parent = nullptr);

    PlaySheetModel(PlayFuncController *pfc, QObject *parent = nullptr);

    void init();

    MusicSheet curMusicSheet() const;
    void setCurMusicSheet(const MusicSheet &curMusicSheet);

    MusicSheet recentMusicSheet() const;
    void setRecentMusicSheet(const MusicSheet &recentMusicSheet);

signals:

public slots:


private:
    //播放界面的控制器
    PlayFuncController* __pfCtrl;


    //当前播放列表
    MusicSheet __curMusicSheet;

    //最近播放列表
    MusicSheet __recentMusicSheet;
};

#endif // PLAYSHEETMODEL_H

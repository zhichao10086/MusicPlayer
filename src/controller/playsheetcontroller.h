#ifndef PLAYSHEETCONTROLLER_H
#define PLAYSHEETCONTROLLER_H

#include <QObject>
#include "playfunccontroller.h"
#include "playsheetmodel.h"
#include "playsheetview.h"
#include "musicsheet.h"
#include <QModelIndex>


class PlaySheetView;
class PlayFuncController;
class PlaySheetModel;


class PlaySheetController : public QObject
{
    Q_OBJECT
public:
    explicit PlaySheetController(QObject *parent = nullptr);

    PlaySheetController(PlayFuncController* pfc,QObject *parent = nullptr);




    void init(PlayFuncController *pfc);

    PlayFuncController* _pfCtrl;
    PlaySheetView* _playSheetView;
    PlaySheetModel* _playSheetModel;


    void playMusic(QModelIndex index);

    /*
     * 更新界面 由界面发起的事件请求 涉及到数据
     */
    void updateView();

    //更新播放列表数据
    void updatePlaySheet(const MusicSheet& musicSheet);

    //更新最近播放列表数据
    void updateRecentPlaySheet(const MusicSheet& musicSheet);

    //更新播放列表界面
    void updatePlaySheetView(const MusicSheet& musicSheet);

    //更新最近播放列表数据
    void updateRecentPlaySheetView(const MusicSheet& musicSheet);

    const MusicSheet& getPlaySheet();


    PlaySheetView *playSheetView() const;
    void setPlaySheetView(PlaySheetView *playSheetView);

    PlaySheetModel *playSheetModel() const;
    void setPlaySheetModel(PlaySheetModel *playSheetModel);

signals:

public slots:
};

#endif // PLAYSHEETCONTROLLER_H

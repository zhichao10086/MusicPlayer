#ifndef PLAYMUSICDETIALCONTROLLER_H
#define PLAYMUSICDETIALCONTROLLER_H

#include <QObject>
#include "globalvariable.h"
#include "playfunccontroller.h"
#include "playmusicdetialmodel.h"
#include "playmusicdetialview.h"
#include "music.h"

class PlayFuncController;
class PlayMusicDetialModel;
class PlayMusicDetialView;


class PlayMusicDetialController : public QObject
{
    Q_OBJECT
public:
    static PlayMusicDetialController* Global_playMusicDetialCtrl ;
    explicit PlayMusicDetialController(QObject *parent = nullptr);
    PlayMusicDetialController(PlayFuncController* pfc, QObject *parent = nullptr);

    static PlayMusicDetialController* newInstance(PlayFuncController* pfc, QObject *parent = nullptr);


    /*
     * 连接到播放控制
     */
    void connectPlayer();

    /*
     * 与播放控制断开连接
     */
    void disconnectPlayer();


    /*
     * 获得当前详细页面的歌曲
     */
    Music getCurPlayMusic();

    /*
     *设置当前的播放音乐
     */
    void setCurPlayMusic(Music value);



    /*
     * 新建一个详细页面
     */
    void CreateDetialView(Music& value);

    PlayMusicDetialView *playMusicDetialView() const;
    //void setPlayMusicDetialView(PlayMusicDetialView *playMusicDetialView);

    PlayMusicDetialModel *getPlayMusicDetialModel() const;

private:

    void __init(PlayFuncController *pfc);

    PlayMusicDetialView* __playMusicDetialView;
    PlayMusicDetialModel* __playMusicDetialModel;

signals:

public slots:
    /*
     * 刷新页面
     */
    void updateView(Music music);

    void updateLyricsView(qint64 position);
};



#endif // PLAYMUSICDETIALCONTROLLER_H

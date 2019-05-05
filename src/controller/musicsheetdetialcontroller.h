#ifndef MUSICSHEETDETIALCONTROLLER_H
#define MUSICSHEETDETIALCONTROLLER_H

#include <QObject>
#include "musicsheetdetialmodel.h"
#include "musicsheetdetialview.h"
#include "playfunccontroller.h"

class MusicSheetDetialModel;
class MusicSheetDetialView;


class MusicSheetDetialController : public QObject
{
    Q_OBJECT
public:
    static MusicSheetDetialController* single_musicSheetDetialCtrl;
    explicit MusicSheetDetialController(QObject *parent = nullptr);


    MusicSheetDetialController(PlayFuncController* pfc,QObject *parent= nullptr);

    static MusicSheetDetialController* newInstance();

    void init();


    /*
     * 设置musicSheet
     */
    void setMusicSheet(const MusicSheet& sheet);

    /*
     * 更新照片路径
     */
    void updateLocalImageUrl(QString url);


    /*
     * 更新界面
     */
    void updateMusicSheetView(MusicSheet& sheet);

    MusicSheetDetialModel *msdModel() const;
    void setMsdModel(MusicSheetDetialModel *msdModel);

    MusicSheetDetialView *msdView() const;
    void setMsdView(MusicSheetDetialView *msdView);

signals:

public slots:


private:

    PlayFuncController* __playFuncCtrl;

    MusicSheetDetialModel *__msdModel;
    MusicSheetDetialView *__msdView;
};

#endif // MUSICSHEETDETIALCONTROLLER_H

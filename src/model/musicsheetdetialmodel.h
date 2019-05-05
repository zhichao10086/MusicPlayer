#ifndef MUSICSHEETDETIALMODEL_H
#define MUSICSHEETDETIALMODEL_H

#include <QObject>
#include "musicsheetdetialcontroller.h"
#include "music.h"
#include <QString>
#include "musicsheet.h"

class MusicSheetDetialController;


class MusicSheetDetialModel : public QObject
{
    Q_OBJECT
public:
    explicit MusicSheetDetialModel(QObject *parent = nullptr);
    MusicSheetDetialModel(MusicSheetDetialController* msdCtrl,QObject *parent = nullptr);





    MusicSheetDetialController *msdCtrl() const;
    void setMsdCtrl(MusicSheetDetialController *msdCtrl);


    /*
     * 更新本地图片路径
     */

    void updateLocalImageUrl(QString url);


    MusicSheet musicSheet() const;
    void setMusicSheet(const MusicSheet &musicSheet);

private:
    MusicSheetDetialController* __msdCtrl;

    MusicSheet __musicSheet;
signals:

public slots:
};

#endif // MUSICSHEETDETIALMODEL_H

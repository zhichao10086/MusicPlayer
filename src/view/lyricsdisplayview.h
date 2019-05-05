#ifndef LYRICSDISPLAYVIEW_H
#define LYRICSDISPLAYVIEW_H

#include <QWidget>
#include "lyrics.h"
#include <QListWidget>
#include <QListWidgetItem>
#include <QStringList>
#include <QString>
#include <QLabel>
#include <QTime>
#include <QDateTime>
#include "lyricsitemview.h"
#include <QModelIndex>
#include <QDebug>


namespace Ui {
class LyricsDisplayView;
}

class LyricsDisplayView : public QListWidget
{
    Q_OBJECT

public:
    explicit LyricsDisplayView(QWidget *parent = 0);




    ~LyricsDisplayView();



    void initView();

private:
    Ui::LyricsDisplayView *ui;

    QVector<LLData> __veclyrics;

    Lyrics __lyrics;

    qint64 __duration;

    int __curLyricsIndex;

public slots:

    /*
     * 应该先设置歌词 是一个歌词类
     * 然后再初始化界面 一整套流程
     */
    void setLyrics(Lyrics lyrics);

    /*
     * 设置总时长
     */
    void setDuration(qint64 duration);


    /*
     * 更新歌词的时候应该将当前的进度读取进来
     * 故应该传进来当前的位置 position
     */
    void updateLyricsView(qint64 position);



};

#endif // LYRICSDISPLAYVIEW_H

#ifndef LYRICSITEMVIEW_H
#define LYRICSITEMVIEW_H

#include <QWidget>
#include <QString>

namespace Ui {
class LyricsItemView;
}

class LyricsItemView : public QWidget
{
    Q_OBJECT

public:

    enum ViewMode{
        Playing,
        NoPlaying
    };

    explicit LyricsItemView(QWidget *parent = 0);


    LyricsItemView(ViewMode mode,QWidget *parent = 0);


    ~LyricsItemView();


    void setMode(ViewMode mode);


    void setText(QString lineLyrics);

    QString getText();


private:
    Ui::LyricsItemView *ui;


};

#endif // LYRICSITEMVIEW_H

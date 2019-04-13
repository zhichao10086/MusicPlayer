#ifndef PLAYSHEETMUSICLISTITEMVIEW_H
#define PLAYSHEETMUSICLISTITEMVIEW_H

#include <QWidget>

namespace Ui {
class PlaySheetMusicListItemView;
}

class PlaySheetMusicListItemView : public QWidget
{
    Q_OBJECT

public:
    explicit PlaySheetMusicListItemView(QWidget *parent = 0);
    ~PlaySheetMusicListItemView();

private:
    Ui::PlaySheetMusicListItemView *ui;
};

#endif // PLAYSHEETMUSICLISTITEMVIEW_H

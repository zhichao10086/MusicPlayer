#ifndef SEARCHMUSICVIEW_H
#define SEARCHMUSICVIEW_H

#include <QWidget>

namespace Ui {
class SearchMusicView;
}

class SearchMusicView : public QWidget
{
    Q_OBJECT

public:
    explicit SearchMusicView(QWidget *parent = 0);
    ~SearchMusicView();

    static SearchMusicView* single_searchMusicView;

    static SearchMusicView* newInstance();

private:
    Ui::SearchMusicView *ui;
};

#endif // SEARCHMUSICVIEW_H

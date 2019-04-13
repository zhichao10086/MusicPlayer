#ifndef MUSICLISTWIDGET_H
#define MUSICLISTWIDGET_H

#include <QWidget>
#include <QMenu>

namespace Ui {
class MusicListWidget;
}

class MusicListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MusicListWidget(QWidget *parent = 0);
    ~MusicListWidget();

private:
    Ui::MusicListWidget *ui;
};

#endif // MUSICLISTWIDGET_H

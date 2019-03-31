#ifndef DOWNLOADVIEW_H
#define DOWNLOADVIEW_H

#include <QWidget>

namespace Ui {
class DownloadView;
}

class DownloadView : public QWidget
{
    Q_OBJECT

public:
    explicit DownloadView(QWidget *parent = 0);
    ~DownloadView();

private:
    Ui::DownloadView *ui;
};

#endif // DOWNLOADVIEW_H

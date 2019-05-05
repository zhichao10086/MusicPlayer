#ifndef RECOMENTTABLEITEMVIEW_H
#define RECOMENTTABLEITEMVIEW_H

#include <QWidget>

namespace Ui {
class RecomentTableItemView;
}

class RecomentTableItemView : public QWidget
{
    Q_OBJECT

public:
    explicit RecomentTableItemView(QWidget *parent = 0);
    ~RecomentTableItemView();

private:
    Ui::RecomentTableItemView *ui;
};

#endif // RECOMENTTABLEITEMVIEW_H

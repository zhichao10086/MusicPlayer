#ifndef FILTERVIEW_H
#define FILTERVIEW_H

#include <QWidget>
#include <QDebug>
#include "playthread.h"
#include <QPoint>
#include <QSlider>
#include <QList>
#include <QMap>
#include <QJsonObject>
#include <QJsonArray>
#include "filterconstant.h"

namespace Ui {
class FilterView;
}

class FilterView : public QWidget
{
    Q_OBJECT

public:
    explicit FilterView(QWidget *parent = 0);

    static FilterView* single_filterView;
    static FilterView* newInstance();

    ~FilterView();

    QJsonObject getFiltersValue();

    QJsonObject getFreqFiltersValue();

    //初始化
    void initView();

    bool eventFilter(QObject *watched, QEvent *event);


    void setMedia(QString filename);


signals:
    void customSliderMoved(qint64);

private slots:
    void on_btnStartOrPause_clicked();

    void on_btnPre_clicked();

    void on_btnNext_clicked();

    void on_timeSlider_valueChanged(int value);

    void on_timeSlider_sliderMoved(int position);

    void setduration(qint64 duration);

    void on_timeSlider_actionTriggered(int action);

    void on_timeSlider_sliderReleased();

    void on_timeSlider_sliderPressed();

    void updateFiltersValue();

private:
    Ui::FilterView *ui;

    PlayThread* __playThread;

    bool __isConnectPosition;

    QList<QSlider*> __freqSliders;

    QJsonObject __filterConfigObj;

};

#endif // FILTERVIEW_H

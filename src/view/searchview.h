#ifndef SEARCHVIEW_H
#define SEARCHVIEW_H

#include <QWidget>
#include <QString>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "globalvariable.h"
#include <QJsonObject>
#include "filefunccontroller.h"
#include <QDebug>

namespace Ui {
class SearchView;
}


/*
 * 单例模式
 */
class SearchView : public QWidget
{
    Q_OBJECT

public:



    explicit SearchView(QWidget *parent = 0);


    static SearchView* single_searchView;
    static SearchView *newInstance();


    void updateView(QString searchText);

    void searchFinish(QNetworkReply* reply);


    ~SearchView();

private:
    Ui::SearchView *ui;
    QNetworkAccessManager* __netManager;
};

#endif // SEARCHVIEW_H

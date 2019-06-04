#include "searchview.h"
#include "ui_searchview.h"


SearchView* SearchView::single_searchView = nullptr;

SearchView::SearchView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchView)
{
    ui->setupUi(this);
    this->__netManager = new QNetworkAccessManager;
}

SearchView *SearchView::newInstance()
{
    if(single_searchView == nullptr){
        single_searchView =  new SearchView;
    }
    return single_searchView;

}

void SearchView::updateView(QString searchText)
{

    if(searchText.isEmpty()){
        return;
    }
    QObject::connect(this->__netManager,&QNetworkAccessManager::finished,
                     this,&SearchView::searchFinish);
    QNetworkRequest req;

    QString strUrl = ("http://" + GlobalVariable::global_server_search_url + "?" + "title=" + searchText+"&" +"index=0") ;
    qDebug()<<strUrl;

    req.setUrl(QUrl(strUrl));
    this->__netManager->get(req);

}

void SearchView::searchFinish(QNetworkReply *reply)
{

    if(reply->error() == QNetworkReply::NoError){
        QByteArray ba = reply->readAll();
        QJsonObject obj =  FileFuncController::getJsonObjFromByteArray(ba);
        if(obj.value(CONST_STRING_RET_CODE).toInt() == CONST_INT_RET_CODE_SUCCESS){
            QJsonArray a = obj.value(CONST_STRING_DATA).toArray();
            QList<Music> musics =  Music::fromJsonObj2Musics(a);

            qDebug()<<musics.size();

            this->ui->lwMusics->updateView(musics);
        }
    }

}

SearchView::~SearchView()
{
    delete ui;
}

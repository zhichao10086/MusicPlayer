#include "filefunccontroller.h"

FileFuncController::FileFuncController(QObject *parent) : QObject(parent)
{

}

QJsonObject FileFuncController::getJsonObjFromFile(QFile &file)
{
    if(!file.open(QIODevice::ReadOnly)){
        qDebug()<<"无法打开:"<<file.fileName();
        return QJsonObject();
    }

    QByteArray allData = file.readAll();
    file.close();
    QJsonParseError json_error;
    QString json(allData);
    qDebug()<<json;

    QJsonDocument jsonDoc = QJsonDocument::fromJson(json.toUtf8(),&json_error);

    if(json_error.error != QJsonParseError::NoError){
        qDebug()<<"格式错误："<<file.fileName();
        return QJsonObject();
    }
    QJsonObject obj = jsonDoc.object();
    return obj;

}

bool FileFuncController::saveJsonObjToFile(QJsonObject obj, QString absoluteFileName)
{
    QFile file(absoluteFileName);
    if(!file.open(QIODevice::WriteOnly))
        return false;

    QJsonDocument doc(obj);
    QByteArray ba = doc.toJson();
    file.write(ba);
    file.close();
}



\

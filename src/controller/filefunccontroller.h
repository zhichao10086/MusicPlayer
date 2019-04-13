#ifndef FILEFUNCCONTROLLER_H
#define FILEFUNCCONTROLLER_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QFile>
#include <QByteArray>
#include <QDebug>
#include <QTextCodec>

class FileFuncController : public QObject
{
    Q_OBJECT
public:
    explicit FileFuncController(QObject *parent = nullptr);


    static QJsonObject getJsonObjFromFile(QFile& file);

    static bool saveJsonObjToFile(QJsonObject obj,QString absoluteFileName);
signals:

public slots:
};

#endif // FILEFUNCCONTROLLER_H

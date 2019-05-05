#ifndef MUSICCUTTHREAD_H
#define MUSICCUTTHREAD_H

#include <QObject>
#include <QThread>
#include "multimusicfunc.h"
#include <QMessageBox>

class MusicCutThread : public QThread
{
    Q_OBJECT
public:
    //explicit MusicCutThread(QObject *parent = nullptr);

    MusicCutThread(double start,double end,QString inFilename,QString outFilename);

    ~MusicCutThread();

    double _start;
    double _end;
    QString _inFilename;
    QString _outputFilename;

signals:
    void finish(int);
public slots:

    // QThread interface
protected:
    void run();
};

#endif // MUSICCUTTHREAD_H

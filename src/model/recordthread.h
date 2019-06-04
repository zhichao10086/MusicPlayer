#ifndef RECORDTHREAD_H
#define RECORDTHREAD_H

#include <QObject>
#include <QThread>

class RecordThread : public QThread
{
public:
    explicit RecordThread(QObject *parent = nullptr);
    ~RecordThread();

    // QThread interface
protected:
    void run();
};

#endif // RECORDTHREAD_H

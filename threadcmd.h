#ifndef THREADCMD_H
#define THREADCMD_H
#include <QObject>
#include <QThread>


class ThreadCmd:public QThread
{
    Q_OBJECT
public:
    ThreadCmd();

    void run();


public slots:
    void OnCmd();
};

#endif // THREADCMD_H

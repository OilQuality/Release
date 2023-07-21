#ifndef THREADCHECKSTATE_H
#define THREADCHECKSTATE_H
#include <QObject>
#include <QThread>

class ThreadCheckState: public QThread
{
    Q_OBJECT
public:
    ThreadCheckState();

    void run();

signals:
    void sigCheck();
};

#endif // THREADCHECKSTATE_H

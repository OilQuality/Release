#ifndef THREADCOMMCMD_H
#define THREADCOMMCMD_H

#include <QObject>
#include <QThread>
#include <QSerialPort>

class ThreadCommCmd:public QThread
{
    Q_OBJECT
public:
    ThreadCommCmd();

    void run();
signals:
    void sigThreadCmd();

public slots:
    void OnSerialRead();

public:
    QByteArray m_data;
    //QSerialPort *m_pSerial;
};

#endif // THREADCOMMCMD_H

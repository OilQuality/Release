#ifndef THDSERIALTASK_H
#define THDSERIALTASK_H

#include <QObject>
#include <QThread>
#include <QSemaphore>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QMutex>
#include <QVector>
#include "dataserialtask.h"
#include <QEventLoop>
#include <QTimer>
class ThdSerialTask : public QThread
{
    Q_OBJECT
public:
    ThdSerialTask();

private:
    QByteArray m_baSerialCtrl;
    QByteArray m_baSerialData;

    QString m_strPortCtrl;//控制串口名
    QString m_strPortColl;//采集串口名

    QSerialPort *m_pSerialCtrl;//控制串口
    QSerialPort *m_pSerialColl;//采集串口

    QMutex m_mutex;
    QSemaphore m_semTask;
    QVector <DataSerialTask> m_vecTask;

private:
    void run();
    void OpenSerial();
    void SerialTask();

    void OnSerialTest(DataSerialTask &task);

    bool RequireSerialCtrlCnt(int nCnt);
    bool RequireSerialDataCnt(int nCnt);

    int m_iCnt;
public:
    void init(QString strPortCtrl, QString strPortColl);//控制和数据采集端口
    void SerialCmdTask(DataSerialTask &task);

signals:
    void sigSerialSendCtrl(QByteArray ba);
    void sigSerialSendData(QByteArray ba);
    void sigSerialTaskDone();

public slots:
    void OnSerialReadCtrl();
    void OnSerialReadData();
};

#endif // THDSERIALTASK_H

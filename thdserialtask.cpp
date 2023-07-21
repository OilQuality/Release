
#include "thdserialtask.h"
#include "appdata.h"


ThdSerialTask::ThdSerialTask()
{
    m_pSerialCtrl = nullptr;
    m_pSerialColl = nullptr;

    m_iCnt = 0;
}

void ThdSerialTask::init(QString strPortCtrl, QString strPortColl)
{
    m_strPortCtrl = strPortCtrl;
    m_strPortColl = strPortColl;
}

void ThdSerialTask::run()
{
    //qDebug("ThdSerialTask::run() %d", (int)QThread::currentThreadId());
    OpenSerial();
    while(true)
    {
        m_semTask.acquire();
        SerialTask();
    }
}

void ThdSerialTask::OpenSerial()
{
    m_pSerialCtrl = new QSerialPort();
    m_pSerialCtrl->setPortName(m_strPortCtrl);//设置串口名
    m_pSerialCtrl->setBaudRate(921600);//设置波特率
    m_pSerialCtrl->setDataBits(QSerialPort::Data8);//设置数据位数
    m_pSerialCtrl->setParity(QSerialPort::NoParity);//设置奇偶校验
    m_pSerialCtrl->setStopBits(QSerialPort::OneStop); //设置停止位
    m_pSerialCtrl->setFlowControl(QSerialPort::NoFlowControl);  //设置流控制
    m_pSerialCtrl->open(QIODevice::ReadWrite);  //打开串口

    //m_pSerial->portName();
    connect( m_pSerialCtrl, SIGNAL(readyRead()),this, SLOT(OnSerialReadCtrl()));
}

void ThdSerialTask::SerialTask()
{
    DataSerialTask task;
    m_mutex.lock();
    task = m_vecTask.front();
    m_vecTask.pop_front();
    m_mutex.unlock();

    switch (task.m_iCmdCode) {
        case SERIAL_TEST:
            OnSerialTest(task);
        break;

    default:
        break;
    }
}

void ThdSerialTask::SerialCmdTask(DataSerialTask &task)
{
    m_mutex.lock();
    m_vecTask.push_back(task);
    m_mutex.unlock();

    m_semTask.release();
}

bool ThdSerialTask::RequireSerialCtrlCnt(int nCnt)
{
    bool bRet = false;
    for( int i = 0; i < 1000; i++)
    {

        QByteArray ba;
        App->getSerialCtrl(ba);
        qDebug( "RequireSerialCtrlCnt check: %d -> %d:%d", i, ba.size(), nCnt );
        if( ba.size() >= nCnt )
        {
            bRet = true;
            break;
        }
        msleep(1);
    }

    return bRet;
}

bool ThdSerialTask::RequireSerialDataCnt(int nCnt)
{
    bool bRet = false;
    for( int i = 0; i < 1000; i++)
    {
        QByteArray ba;
        App->getSerialColl(ba);
        if( ba.size() >= nCnt )
        {
            bRet = true;
            break;
        }
        msleep(1);
    }

    return bRet;
}


void ThdSerialTask::OnSerialReadCtrl()
{
    //从接收缓冲区中读取数据
    qDebug("--- ThdSerialTask::OnSerialReadCtrl() ---");

    QByteArray baBuffer = m_pSerialCtrl->readAll();
    m_mutex.lock();
    m_baSerialCtrl.append(baBuffer);
    m_mutex.unlock();
    //以下是打印信息
    char *pBuff = baBuffer.data();
    int nLen = baBuffer.size();

    char szBuff[100] = { 0 };
    QString strResult;
    for(int i = 0; i < nLen; i++)
    {
        sprintf(szBuff," %x", pBuff[i] & 0xFF);
        strResult += QString(szBuff);
    }
    qDebug("***ThdSerialTask::OnSerialReadCtrl,总数:%d 收到:%d字节 ->%s", m_baSerialCtrl.size(), nLen, strResult.toStdString().c_str());
}

void ThdSerialTask::OnSerialReadData()
{
    m_mutex.lock();
    m_mutex.unlock();
}

/*  ************************************ 任务处理函数 ************************************* */
void ThdSerialTask::OnSerialTest(DataSerialTask &task)
{
    Q_UNUSED(task);
    //qDebug("----------------- ThdSerialTask::OnSerialTest -------------------- %d", (int)QThread::currentThreadId());

    if( !m_pSerialCtrl->isOpen())
    {
        return;
    }
    m_iCnt ++;
    char szCmd[13] = "x1 123456";
    szCmd[1] = (char)m_iCnt;
    QByteArray btData;
    btData = QByteArray(szCmd, 9 );
   // emit sigSerialSendCtrl( btData );
    m_pSerialCtrl->write(btData);
    m_pSerialCtrl->waitForBytesWritten();


    strcpy( szCmd, "x2 123");
    btData = QByteArray(szCmd, 6 );
  //  emit sigSerialSendCtrl( btData );
    m_pSerialCtrl->write(btData);
    m_pSerialCtrl->waitForBytesWritten();

    strcpy( szCmd, "x3 123");
    btData = QByteArray(szCmd, 6 );
  //  emit sigSerialSendCtrl( btData );
    m_pSerialCtrl->write(btData);
    m_pSerialCtrl->waitForBytesWritten();

    strcpy( szCmd, "x4 123");
    btData = QByteArray(szCmd, 6 );
  //  emit sigSerialSendCtrl( btData );
    m_pSerialCtrl->write(btData);
    m_pSerialCtrl->waitForBytesWritten();
    //m_pSerialCtrl->flush();

    QEventLoop loop;// 非常重要, 没有事件循环数据无法发送
    QTimer::singleShot(1, &loop, SLOT(quit()));
    loop.exec();
    return;
    if( !RequireSerialCtrlCnt(9) )
    {
        return;
    }
    if( !RequireSerialCtrlCnt(15) )
    {
        return;
    }
    if( !RequireSerialCtrlCnt(21) )
    {
        return;
    }
    if( !RequireSerialCtrlCnt(21) )
    {
        return;
    }
}

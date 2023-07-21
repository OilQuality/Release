#include "threadcommcmd.h"
#include "appdata.h"

ThreadCommCmd::ThreadCommCmd()
{
    //m_pSerial = nullptr;
}

void ThreadCommCmd::run()
{
    qDebug("------------ ThreadCommCmd:: run() ");
    /*
    if( m_pSerial == nullptr )
    {
        return;
    }

    char szCmd[4] = "abc";
    QByteArray btData;
    btData = QByteArray(szCmd, 4 );
    m_pSerial->write(btData);

    sleep(1);
    m_pSerial->write(btData);

    sleep(1);
    m_pSerial->write(btData);
    */
    //qDebug("------------ ThreadCommCmd:: run() ----------- thread id: %d", (int)QThread::currentThreadId());

    QThread::sleep(5);
    emit sigThreadCmd();
}

void ThreadCommCmd::OnSerialRead()
{
    //qDebug("------------ ThreadCommCmd:: OnSerialRead ----------- thread id: %d", (int)QThread::currentThreadId());
    /*
    //从接收缓冲区中读取数据
    if( m_pSerial == nullptr )
    {
        return;
    }

    //QByteArray btBuffer = m_pSerial->readAll();
    m_data.append(btBuffer);

    char *pBuff = btBuffer.data();
    int nLen = btBuffer.size();

    char szBuff[100] = { 0 };
    QString strResult;
    for(int i = 0; i < nLen; i++)
    {
        sprintf(szBuff," %x", pBuff[i] & 0xFF);
        strResult += QString(szBuff);
    }
    qDebug("*****ThreadCommCmd::OnSerialRead: %d字节 ->%s", nLen, strResult.toStdString().c_str());
    */
}

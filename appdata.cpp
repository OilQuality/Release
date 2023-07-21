#include "appdata.h"
#include <QThread>
#include <QTime>
#include <QCoreApplication>
#include "threadcommcmd.h"
#include "threadcheckstate.h"
#include "threadcmd.h"
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QProcess>
#include <QJsonDocument>
#include <QJsonObject>

Q_GLOBAL_STATIC(AppData, appData)
AppData::AppData(QObject *parent) : QObject(parent)
{
    qDebug(" ****** AppData::AppData() ****** ");
    //m_lightSate = 1;
    m_bInitState = false;
    m_strOilName = "000";

    m_SPP_35um = 0;
    m_SPP_REF = 290;
    m_SPP_100um = 601;

    m_dMdjCalcValue = 0;

    m_bTempControl = false;
    m_mcInfo.dtMdj = QDateTime::currentDateTime();
    ListSerialPort();
    armCommLog("AppData Init!\r\n");
}

AppData* AppData::instance()
{
    return appData();
}

bool AppData::getTempControl()
{
    bool bTemp = false;
    m_mtData.lock();
    bTemp = m_bTempControl;
    m_mtData.unlock();
    return bTemp;
}

void AppData::setTempControl(bool bTemp)
{
    m_mtData.lock();
    m_bTempControl = bTemp;
    m_mtData.unlock();
}

void AppData::logs(QString msg)
{
    log(msg);
}

void AppData::setScene(int iScene)
{
    m_mtData.lock();
    m_iScene = iScene;
    m_mtData.unlock();

    qDebug("设置场景: %d", iScene);
}

int AppData::getScene()
{
    int iScene = 0;
    m_mtData.lock();
    iScene = m_iScene;
    m_mtData.unlock();
    return iScene;
}

void AppData::setInitState(bool bState)
{
    m_mtData.lock();
    m_bInitState = bState;
    m_mtData.unlock();
}

bool AppData::getInitState()
{
    bool bState = false;
    m_mtData.lock();
    bState = m_bInitState;
    m_mtData.unlock();

    return bState;
}

void AppData::log(QString &msg)
{
    static QMutex mutex;
    mutex.lock();

    QString strPath = "./log";
    QString timestr=QDateTime::currentDateTime().toString("yyyy_MM_dd");
    QString fileName = timestr + ".txt";

    //写入日志
    //检查路径
    QDir dirRoot;
    if(!dirRoot.exists(strPath))
    {
        dirRoot.mkpath(strPath);
    }

    //检查文件
    QFile file;
    file.setFileName(strPath + QDir::separator() + fileName);
    if( !file.open(QIODevice::Text|QIODevice::WriteOnly | QIODevice::Append))
    {
        qDebug("file cannot create!");
        return;
    }

    QTextStream text_stream(&file);
    text_stream << QTime::currentTime().toString("hh:mm:ss.zzz") << " " << msg << "\r\n";

    file.flush();
    file.close();
    mutex.unlock();
}

void AppData::log(QString strFile, QString msg)
{
//    static QMutex mutex;
//    mutex.lock();

    QString fileName = strFile;
    fileName.append(".txt");

    QString strPath = "./log";

    //检查路径
    QDir dirRoot;
    if(!dirRoot.exists(strPath))
    {
        dirRoot.mkpath(strPath);
    }

    //检查文件
    QFile file;
    file.setFileName(strPath + QDir::separator() + fileName);
    if( !file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        qDebug("file cannot create!");
        return;
    }

    QString strLog;
    QTime cur = QTime::currentTime();
    strLog = QString("%1 %2 \r\n").arg(cur.toString("hh:mm:ss.zzz")).arg(msg);

    file.write(strLog.toStdString().c_str(), strLog.length());
    file.flush();
    file.close();
//    mutex.unlock();
}

void AppData::armCommLog(QString msg)
{
    m_mtLog.lock();
    QString strPath = "./log/comm";
    QString fileTime = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh");
    //检查路径
    QDir dirRoot;
    if(!dirRoot.exists(strPath))
    {
        dirRoot.mkpath(strPath);
    }

    QFile file;
    file.setFileName(strPath + QDir::separator() + fileTime + ".log");
    if( !file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        return;
    }

    QString strLog;
    QTime cur = QTime::currentTime();
    strLog = QString("%1 %2 \r\n").arg(cur.toString("hh:mm:ss.zzz")).arg(msg);

    file.write(strLog.toStdString().c_str(), strLog.length());
    file.flush();
    file.close();
    m_mtLog.unlock();
}

void AppData::armMdjLog(QString msg)
{//密度计
    QString strPath = "./log/mdj";
    QString fileTime = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh");
    //检查路径
    QDir dirRoot;
    if(!dirRoot.exists(strPath))
    {
        dirRoot.mkpath(strPath);
    }

    QFile file;
    file.setFileName(strPath + QDir::separator() + fileTime + ".log");
    if( !file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        return;
    }

    QString strLog;
    QTime cur = QTime::currentTime();
    strLog = QString("%1 %2 \r\n").arg(cur.toString("hh:mm:ss.zzz")).arg(msg);

    file.write(strLog.toStdString().c_str(), strLog.length());
    file.flush();
    file.close();
}

void AppData::setMdjCalc(double dMdj)
{
    m_mtData.lock();
    m_dMdjCalcValue = dMdj;
    m_mtData.unlock();
}

double AppData::getMdjCalc()
{
    double dmdj = 0;
    m_mtData.lock();
    dmdj = m_dMdjCalcValue;
    m_mtData.unlock();
    return dmdj;
}

void AppData::readJsonCfg()
{
    QFile file("./cfg/config.json");
    QByteArray jsonData;
    if(file.open(QIODevice::ReadOnly))
    {
        jsonData = file.readAll();
        file.close();
    }

    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
    if(jsonDoc.isObject())
    {
        QJsonObject obj = jsonDoc.object();

        double dMdjCalc = obj["MdjCalc"].toDouble();
        setMdjCalc(dMdjCalc);

        bool  bTempControl = obj["TempContrl"].toBool();
        setTempControl(bTempControl);
    }
}

void AppData::writeJsonCfg()
{
    QJsonObject obj;
    obj.insert("MdjCalc", getMdjCalc());
    obj.insert("TempContrl", getTempControl());
    QJsonDocument doc;
    doc.setObject(obj);

    //打开Json文件
    QFile file(QString::fromStdString("./cfg/config.json"));
    if(file.open(QIODevice::ReadWrite)) {
        file.write(doc.toJson());  //写入文件
        file.close();
    }
}
/*
void AppData::setTempture(double dTemp)
{
    m_mtData.lock();
    m_dTempSetting = dTemp;
    m_mtData.unlock();
}

double AppData::getTempSetting()
{
    double temp = 0;
    m_mtData.lock();
    temp = m_dTempSetting;
    m_mtData.unlock();
    return temp;
}*/

void AppData::setOilName(QString strName)
{
    m_strOilName = strName;
}

QString AppData::getOilName()
{
    return m_strOilName;
}

void AppData::SetInfo(QByteArray &btInfo)
{
    m_mtData.lock();
    m_baMachineInfo = btInfo;
    uint ih = 0;
    uint il = 0;
    int iRes = 0;
    double dRes = 0;
    ih = (btInfo.at(42) & 0xFF) * 256;
    il = btInfo.at(43) & 0xFF;
    dRes = ih + il;
    m_mcInfo.iTempYpc = dRes / 10.0f;

    ih = (btInfo.at(44) & 0xFF) * 256;
    il = btInfo.at(45) & 0xFF;
    dRes = ih + il;
    m_mcInfo.iTempJyq = dRes / 10.0f;

    ih = (btInfo.at(46) & 0xFF) * 256;
    il = btInfo.at(47) & 0xFF;
    dRes = ih + il;
    m_mcInfo.iTempMdj = dRes / 10.0f;

    ih = (btInfo.at(34) & 0xFF) * 256;
    il = btInfo.at(35) & 0xFF;
    iRes = ih + il;
    m_mcInfo.iLightPower = iRes;

    ih = (btInfo.at(52) & 0xFF) * 256;
    il = btInfo.at(53) & 0xFF;
    dRes = ih + il;
    m_mcInfo.iTempSetJyq = dRes / 10.0f;

    ih = (btInfo.at(54) & 0xFF) * 256;
    il = btInfo.at(55) & 0xFF;
    dRes = ih + il;
    m_mcInfo.iTempSetMdj = dRes / 10.0f;

    ih = (btInfo.at(50) & 0xFF) * 256;
    il = btInfo.at(51) & 0xFF;
    dRes = ih + il;
    m_mcInfo.iTempSetYpc = dRes / 10.0f;
    m_mtData.unlock();
}

void AppData::SetInfo2(QString strip)
{
    m_mtData.lock();
    m_mcInfo.strIP = strip.toStdString();
    m_mtData.unlock();
}

void AppData::SetMDJInfo(double dwMdj, double dwMdjTemp)
{
    m_mtData.lock();
    m_mcInfo.dMdjOriginal = dwMdj;
    m_mcInfo.dMdj = m_mcInfo.dMdjOriginal + m_dMdjCalcValue;
    m_mcInfo.dMdjTemp = dwMdjTemp;
    m_mcInfo.dtMdj = QDateTime::currentDateTime();
    /*
    m_vecMdj.push_back(dwMdj);
    if( m_vecMdj.size() > 5 )
    {
        m_vecMdj.pop_front();
    }*/
    m_mtData.unlock();
}

void AppData::getInfo(MachineInfo &mi)
{
    m_mtData.lock();
    mi = m_mcInfo;
/*
    double  dwResult = 0;
    int nCnt = m_vecMdj.size();
    for(int i = 0; i < nCnt; i++)
    {
        dwResult += m_vecMdj.at(i);
    }

    if( nCnt > 0 )
    {
        mi.dMdj = dwResult / nCnt;
    }else{
        mi.dMdj = 0;
    }
*/
    m_mtData.unlock();
}

void AppData::setArmStatus(QByteArray &bt)
{
    m_mtData.lock();
    m_baMachineInfo = bt;
    m_mtData.unlock();

    SetInfo(bt);
}

int AppData::getSamplePoolPos()
{//获得样品池位置
    int bth = 0;
    int btl = 0;
    int iRet = 0;
    m_mtData.lock();
    if(m_baMachineInfo.size() >= 96 )
    {
        bth = m_baMachineInfo.at(40) & 0xFF;
        btl = m_baMachineInfo.at(41) & 0xFF;
    }
    m_mtData.unlock();
    iRet = bth * 256 + btl;
    return iRet;
}

double AppData::getMachineSamplePoolTemp()
{
    uint ih = 0;
    uint il = 0;
    double dRes = 0;
    double dRet = 0;
    m_mtData.lock();

    ih = (m_baMachineInfo.at(42) & 0xFF) * 256;
    il = m_baMachineInfo.at(43) & 0xFF;
    dRes = ih + il;
    dRet = dRes / 10.0f;
    m_mtData.unlock();

    return dRet;
}

double AppData::getMachineJYQTemp()
{
    uint ih = 0;
    uint il = 0;
    double dRes = 0;
    double dRet = 0;
    m_mtData.lock();

    ih = (m_baMachineInfo.at(44) & 0xFF) * 256;
    il = m_baMachineInfo.at(45) & 0xFF;
    dRes = ih + il;
    dRet = dRes / 10.0f;
    m_mtData.unlock();

    return dRet;
}

double AppData::getMachineMD()
{
    double dRet = 0;
    m_mtData.lock();
    dRet = m_mcInfo.dMdj;
/*
    double  dwResult = 0;
    int nCnt = m_vecMdj.size();
    for(int i = 0; i < nCnt; i++)
    {
        dwResult += m_vecMdj.at(i);
    }

    if( nCnt > 0 )
    {
        dRet = dwResult / nCnt;
    }
*/
    m_mtData.unlock();
    return dRet;
}

double AppData::getMachineMdjTemp()
{
    double dRet = 0;
    m_mtData.lock();
    dRet = m_mcInfo.dMdjTemp;
    m_mtData.unlock();
    return dRet;
}

int AppData::getMachineLightLevel()
{//获得机器光源强度
    int bth = 0;
    int btl = 0;
    int iRet = 0;
    m_mtData.lock();
    if(m_baMachineInfo.size() >= 96 )
    {
        bth = m_baMachineInfo.at(34) & 0xFF;
        btl = m_baMachineInfo.at(35) & 0xFF;
    }
    m_mtData.unlock();
    iRet = bth * 256 + btl;
    return iRet;
}

void AppData::getArmMirrorPos(int &x, int &y)
{//获得电镜xy位置
    m_mtData.lock();
    if(m_baMachineInfo.size() >= 96 )
    {
        x = CalcInt(m_baMachineInfo.at(10), m_baMachineInfo.at(11), m_baMachineInfo.at(12), m_baMachineInfo.at(13));
        y = CalcInt(m_baMachineInfo.at(14), m_baMachineInfo.at(15), m_baMachineInfo.at(16), m_baMachineInfo.at(17));
    }
    m_mtData.unlock();
}

void AppData::getSwitchState(bool &bSw1, bool &bSw2, bool &bSw3)
{
    bSw1 = true;
    bSw2 = true;
    bSw3 = true;
    char iState = 0;
    QByteArray ba;
    m_mtData.lock();
    if(m_baMachineInfo.size() >= 96 )
    {
        ba = m_baMachineInfo;
        iState = m_baMachineInfo.at(31) & 0xFF;
        if(( iState & 0x1 ) == 0 )
        {
            bSw1 = false;
        }
        if(( iState & 0x2 ) == 0 )
        {
            bSw2 = false;
        }
        if(( iState & 0x4 ) == 0 )
        {
            bSw3 = false;
        }
    }
    m_mtData.unlock();

    char szDbg[200] = { 0 };
    sprintf(szDbg,"key:%d sw1:%d sw2:%d sw3:%d ",iState, bSw1, bSw2, bSw3 );
    log("sw", szDbg);

    QString strResult;
    int nCnt = ba.size();
    sprintf(szDbg, "总数:%d\n", nCnt);
    strResult += szDbg;
    for(int i = 0; i < nCnt; i ++)
    {
        int iData = ba.at(i)  & 0xFF;
        sprintf(szDbg, "0x%02X,",iData);
        strResult += szDbg;
    }

    log("sw", strResult);
}

int AppData::CalcInt(char c1, char c2, char c3, char c4)
{
    int iKey = 0;
    char *pch = (char *)&iKey;
    pch[0] = c4;
    pch[1] = c3;
    pch[2] = c2;
    pch[3] = c1;
    return iKey;
}

void AppData::QueryInfoTask()
{
    if( !m_pSerialWorker->runStatus())
    {
        DataSerialTask task;
        task.m_iCmdCode = MACHINE_QUERY;
        m_pSerialWorker->SerialCmdTask(task);
    }
}

void AppData::test()
{
    qDebug("AppData::test()");

    DataSerialTask task;
    task.m_iCmdCode = SERIAL_TEST;
    m_pSerialWorker->SerialCmdTask(task);
}

void AppData::init(QString strPortCtrl, QString strPortColl)
{
    m_strPortCtrl = strPortCtrl;
    m_strPortColl = strPortColl;

    m_pSerialWorker = new ThreadSerialWorker();
    m_pSerialWorker->start();

    connect(m_pSerialWorker, SIGNAL(sigSerialSendCtrl(QByteArray)), SLOT(OnSerialSendCtrl(QByteArray)));
    connect(m_pSerialWorker, SIGNAL(sigSerialSendColl(QByteArray)), SLOT(OnSerialSendColl(QByteArray)));
    TestSerial();
    openSerial();
    connect( &m_SerialCtrl, SIGNAL(readyRead()),this, SLOT(OnSerialReadCtrl()));
    connect( &m_SerialColl, SIGNAL(readyRead()),this, SLOT(OnSerialReadColl()));

    connect(m_pSerialWorker, SIGNAL(sigSerialCmdMsg(QString)), SLOT(OnSerialCmdUI(QString)));
}

void AppData::initComInfo()
{
/*
    QFile file("./config/com.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        init("","");
        return;
    }

    int nPos = -1;
    QString strCom1, strCom2, strCom3,strCom4;//com1:控制 com2:数据 com3:密度计 com4:关机
    while(!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString strLine(line);

        if( strLine.contains("com1"))
        {
            nPos = strLine.indexOf(':');
            if( nPos > 0 )
            {
                strCom1 = strLine.left(nPos);
                qDebug("com--1-->%s", strCom1.toStdString().c_str());
            }
        }else if( strLine.contains("com2"))
        {
            nPos = strLine.indexOf(':');
            if( nPos > 0 )
            {
                strCom2 = strLine.left(nPos);
                qDebug("com--2-->%s", strCom2.toStdString().c_str());
            }
        }else if( strLine.contains("com3"))
        {
            nPos = strLine.indexOf(':');
            if( nPos > 0 )
            {
                strCom3 = strLine.left(nPos);
                qDebug("com--3-->%s", strCom3.toStdString().c_str());
            }
        }else if( strLine.contains("com4"))
        {
            nPos = strLine.indexOf(':');
            if( nPos > 0 )
            {
                strCom4 = strLine.left(nPos);
                qDebug("com--4-->%s", strCom4.toStdString().c_str());
            }
        }
    }

    m_strPortCtrl = strCom1;
    m_strPortColl = strCom2;
    m_strPortMdj  = strCom3;
    m_strPortPowerOff = strCom4;
*/

    m_strPortCtrl = "ttyS3";
    m_strPortColl = "ttyS4";
    m_strPortMdj  = "ttyS1";
    m_strPortPowerOff = "ttyS0";

    openSerial();
    //TestSerial();
}

void AppData::InitWorker()
{
    m_pSerialWorker = new ThreadSerialWorker();
    m_pSerialWorker->start();

    connect(m_pSerialWorker, SIGNAL(sigSerialSendCtrl(QByteArray)), SLOT(OnSerialSendCtrl(QByteArray)));
    connect(m_pSerialWorker, SIGNAL(sigSerialSendColl(QByteArray)), SLOT(OnSerialSendColl(QByteArray)));

    connect(m_pSerialWorker, SIGNAL(sigSerialCmdMsg(QString)), SLOT(OnSerialCmdUI(QString)));
}

void AppData::deInit()
{
    if( m_SerialCtrl.isOpen())
    {
        m_SerialCtrl.clear();
        m_SerialCtrl.close();
        qDebug("*** m_SerialCtrl close ***");
    }

    if( m_SerialColl.isOpen())
    {
        m_SerialColl.clear();
        m_SerialColl.close();
        qDebug("*** m_SerialColl close ***");
    }

    if( m_SerialMdj.isOpen())
    {
        m_SerialMdj.clear();
        m_SerialMdj.close();
    }

    if( m_SerialPO.isOpen())
    {
        m_SerialPO.clear();
        m_SerialPO.close();
    }
}

void AppData::ComDelay()
{
    QTimer timer;
    timer.setTimerType(Qt::PreciseTimer);
    timer.start(10);
    while(timer.remainingTime() > 0)
        QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
}

void AppData::TestSerial()
{
    int nCnt = m_vecUSBList.size();
    qDebug("-------->test com: %d", nCnt);
    for(int i = 0; i < nCnt; i ++ )
    {
        std::string strSerialName = m_vecUSBList.at(i);

        if( strSerialName.find("USB") == std::string::npos )
        {
            m_SerialTest.setPortName( strSerialName.data() );
            m_SerialPO.setBaudRate(9600);//设置波特率
            m_SerialPO.setDataBits(QSerialPort::Data8);//设置数据位数
            m_SerialPO.setParity(QSerialPort::NoParity);//设置奇偶校验
            m_SerialPO.setStopBits(QSerialPort::OneStop); //设置停止位
            m_SerialPO.setFlowControl(QSerialPort::NoFlowControl);  //设置流控制
            //m_SerialPO.setDataTerminalReady(true);//DTR
            //m_SerialPO.setRequestToSend(false);//RTS
        }else
        {
            m_SerialTest.setPortName( strSerialName.data() );
            m_SerialTest.setBaudRate(921600);//设置波特率
            m_SerialTest.setDataBits(QSerialPort::Data8);//设置数据位数
            m_SerialTest.setParity(QSerialPort::NoParity);//设置奇偶校验
            m_SerialTest.setStopBits(QSerialPort::OneStop); //设置停止位
            m_SerialTest.setFlowControl(QSerialPort::NoFlowControl);  //设置流控制
        }

        if(m_SerialTest.open(QIODevice::ReadWrite) )//打开串口
        {
            qDebug("com Test---------------------%s open", m_vecUSBList.at(i).c_str());
        }else{
            qDebug("com Test---------------------%s can't open", m_vecUSBList.at(i).c_str());
            continue;
        }

        connect( &m_SerialTest, SIGNAL(readyRead()),this, SLOT(OnSerialReadTest()));

        uchar szCmd1[] = { 0xAA, 0xBB, 0x00, 0xCC, 0xDD };
        QByteArray ba1((char *)szCmd1, 5 );
        m_SerialTest.write(ba1);

        for( int nOrder = 0; nOrder < 10; nOrder++ )
        {
            // QThread::sleep(1);
           ComDelay();
           if( m_baSerialTest.size() == 5 )
           {
               uchar *pBuff = (uchar *)m_baSerialTest.data();
               if(( pBuff[0] == 0xAA ) && ( pBuff[1] == 0xBB ) && ( pBuff[2] == 0x03 ) && ( pBuff[3] == 0xCC ) && ( pBuff[4] = 0xDD))
               {
                   qDebug("com power off is: %s", strSerialName.data() );
                   m_strPortPowerOff = strSerialName.data();
               }else if(( pBuff[0] == 0xAA ) && ( pBuff[1] == 0xBB ) && ( pBuff[2] == 0x01 ) && ( pBuff[3] == 0xCC ) && ( pBuff[4] = 0xDD))
               {
                    m_strPortCtrl = strSerialName.data();
                    qDebug("com control is: %s", strSerialName.data() );
               }else if(( pBuff[0] == 0xAA ) && ( pBuff[1] == 0xBB ) && ( pBuff[2] == 0x02 ) && ( pBuff[3] == 0xCC ) && ( pBuff[4] = 0xDD))
               {
                    m_strPortColl = strSerialName.data();
                    qDebug("com collect is: %s", strSerialName.data() );
               }
               break;
           }else if( m_baSerialTest.size() > 5 )
           {
               break;
           }
           //qDebug("%s-------->deleay: %d", QTime::currentTime().toString("HH:mm:ss_zzz").toStdString().c_str(), nOrder);
        }//for nOrder

        m_SerialTest.clear();
        m_SerialTest.close();
        m_SerialTest.disconnect();
        m_baSerialTest.clear();
    }//for i
}

void AppData::openSerial()
{
    m_SerialCtrl.setPortName(m_strPortCtrl);//设置串口名
    //m_SerialCtrl.setBaudRate(115200);//设置波特率
    m_SerialCtrl.setBaudRate(921600);//设置波特率
    m_SerialCtrl.setDataBits(QSerialPort::Data8);//设置数据位数
    m_SerialCtrl.setParity(QSerialPort::NoParity);//设置奇偶校验
    m_SerialCtrl.setStopBits(QSerialPort::OneStop); //设置停止位
    m_SerialCtrl.setFlowControl(QSerialPort::NoFlowControl);  //设置流控制
    m_SerialCtrl.open(QIODevice::ReadWrite);  //打开串口
    connect( &m_SerialCtrl, SIGNAL(readyRead()),this, SLOT(OnSerialReadCtrl()));

    m_SerialColl.setPortName(m_strPortColl);//设置串口名
    m_SerialColl.setBaudRate(921600);//设置波特率
    m_SerialColl.setDataBits(QSerialPort::Data8);//设置数据位数
    m_SerialColl.setParity(QSerialPort::NoParity);//设置奇偶校验
    m_SerialColl.setStopBits(QSerialPort::OneStop); //设置停止位
    m_SerialColl.setFlowControl(QSerialPort::NoFlowControl);  //设置流控制
    m_SerialColl.open(QIODevice::ReadWrite);  //打开串口
    connect( &m_SerialColl, SIGNAL(readyRead()),this, SLOT(OnSerialReadColl()));

    if( m_strPortMdj.length() > 0 )
    {
        m_SerialMdj.setPortName(m_strPortMdj);//设置串口名
        m_SerialMdj.setBaudRate(9600);//设置波特率
        m_SerialMdj.setDataBits(QSerialPort::Data7);//设置数据位数
        m_SerialMdj.setParity(QSerialPort::EvenParity);//设置奇偶校验
        m_SerialMdj.setStopBits(QSerialPort::OneStop); //设置停止位
        m_SerialMdj.setFlowControl(QSerialPort::NoFlowControl);  //设置流控制
        m_SerialMdj.open(QIODevice::ReadWrite);  //打开串口

        connect( &m_SerialMdj, SIGNAL(readyRead()),this, SLOT(OnSerialReadMdj()));
    }

    if( m_strPortPowerOff.length() > 0 )
    {
        m_SerialPO.setPortName(m_strPortPowerOff);//设置串口名
        m_SerialPO.setBaudRate(9600);//设置波特率
        m_SerialPO.setDataBits(QSerialPort::Data8);//设置数据位数
        m_SerialPO.setParity(QSerialPort::NoParity);//设置奇偶校验
        m_SerialPO.setStopBits(QSerialPort::OneStop); //设置停止位
        m_SerialPO.setFlowControl(QSerialPort::NoFlowControl);  //设置流控制
        m_SerialPO.setDataTerminalReady(true);//DTR
        m_SerialPO.setRequestToSend(false);//RTS
        m_SerialPO.open(QIODevice::ReadWrite);  //打开串口

        connect( &m_SerialPO, SIGNAL(readyRead()),this, SLOT(OnSerialReadPowerOff()));
    }

    if( !isSerialOpen())
    {
        qInfo("串口开启错误!");
    }else{
        qInfo("串口初始化完成!");
    }
}

void AppData::shutDown()//关闭系统电源
{
    QByteArray btData;
    uchar szCmd[100] = { 0xAA, 0x0A, 0xFF };

    btData = QByteArray((char *)szCmd, 3 );
    m_SerialPO.write(btData);
}

void AppData::OnSerialReadTest()
{
    QByteArray baBuffer = m_SerialTest.readAll();
    m_baSerialTest.append(baBuffer);
}

void AppData::OnSerialReadCtrl()
{
    //从接收缓冲区中读取数据
    QByteArray baBuffer = m_SerialCtrl.readAll();
    m_mtData.lock();
    m_baSerialCtrl.append(baBuffer);
    m_mtData.unlock();

    //以下是打印信息
    char *pBuff = baBuffer.data();
    int nLen = baBuffer.size();

    char szBuff[100] = { 0 };
    QString strResult;
    for(int i = 0; i < nLen; i++)
    {
        sprintf(szBuff," %02X", pBuff[i] & 0xFF);
        strResult += QString(szBuff);
    }

    char szInfo[100] = { 0 };
    sprintf(szInfo,"<-Ctrl Receiv:%d->Total:%d",nLen, m_baSerialCtrl.size() );
    armCommLog(szInfo);
    armCommLog(strResult);
    //qDebug("***OnSerialReadCtrl,总数:%d 收到:%d字节 ->%s", m_baSerialCtrl.size(), nLen, strResult.toStdString().c_str());
}

void AppData::OnSerialReadColl()
{
    //从接收缓冲区中读取数据
    QByteArray baBuffer = m_SerialColl.readAll();
    m_mtData.lock();
    m_baSerialColl.append(baBuffer);
    m_mtData.unlock();

    //以下是打印信息
    char *pBuff = baBuffer.data();
    int nLen = baBuffer.size();

    char szBuff[100] = { 0 };
    QString strResult;
    for(int i = 0; i < nLen; i++)
    {
        sprintf(szBuff," %02X", pBuff[i] & 0xFF);
        strResult += QString(szBuff);
    }

    char szInfo[100] = { 0 };
    sprintf(szInfo,"<-Coll Receive:%d->Total:%d",nLen, m_baSerialColl.size() );
    armCommLog(szInfo);
    armCommLog(strResult);
    //qDebug("***OnSerialReadColl,总数:%d 收到:%d字节 ->%s", m_baSerialColl.size(), nLen, strResult.toStdString().c_str());
}

void AppData::OnSerialReadMdj()//密度计
{
    //char szBuff[] = { 0x2D, 0x2D, 0x2D, 0x20, 0x20, 0x20, 0x33, 0x32, 0x2E, 0x35, 0x20, 0x20, 0x30, 0x2E, 0x30, 0x31, 0x35, 0x37, 0x0D, 0x0A, 0x1A};
    QByteArray baData = m_SerialMdj.readAll();

    armMdjLog("step 001");
    int nCnt = baData.size();
    double dmd = 0;
    double dwd = 0;
    if((nCnt >= 21 ) && (baData.at(0) == '-') && ( baData.at(1) == '-') && (baData.at(2) == '-') && ( baData.at(nCnt-3) == '\r') && ( baData.at(nCnt-2) == '\n') )
    {
        armMdjLog("step 002");
        QByteArray baTemp = baData.left(10);
        baTemp[0] = ' ';
        baTemp[1] = ' ';
        baTemp[2] = ' ';

        QString strWd = QString(baTemp);

        QByteArray baMdj = baData.right(nCnt - 10);
        int nMdj = baMdj.size();
        baMdj[nMdj-1] = '\0';
        baMdj[nMdj-2] = '\0';
        baMdj[nMdj-3] = '\0';
        QString strMd = QString(baMdj);

        dmd = strMd.toDouble();
        dwd = strWd.toDouble();
        armMdjLog("step 003");
        SetMDJInfo( dmd, dwd );
        armMdjLog("step 004");
    }
    armMdjLog("step 005");
    //以下是打印信息
    char *pBuff = baData.data();
    int nLen = baData.size();

    char szBuff[200] = { 0 };
    QString strResult;
    for(int i = 0; i < nLen; i++)
    {
        sprintf(szBuff," %02X", pBuff[i] & 0xFF);
        strResult += QString(szBuff);
    }
    armMdjLog("step 006");
    char szLog[400] = { 0 };
    sprintf(szLog,"wd:%f md:%f len:%d msg:%s",dwd,dmd, baData.size(), strResult.toStdString().c_str() );
    //log("密度计", szLog);
    armMdjLog(szLog);
}

void AppData::OnSerialReadPowerOff()//关机
{
    //从接收缓冲区中读取数据
    QByteArray baBuffer = m_SerialPO.readAll();
    m_mtData.lock();
    m_baSerialPO.append(baBuffer);
    m_mtData.unlock();

#if defined (WIN32)
#else
    uchar * pBuffPo = (uchar *)m_baSerialPO.data();
    if(( pBuffPo[0] == 0xBB ) && ( pBuffPo[1] == 0x0A ) && ( pBuffPo[2] = 0xFF))
    {
        QProcess pro;    //通过QProcess类来执行第三方程序
        QString cmd = QString("shutdown -h now");
        pro.start(cmd);    //执行命令cmd
        pro.waitForStarted();
        pro.waitForFinished();
    }
#endif
    //以下是打印信息
    char *pBuff = baBuffer.data();
    int nLen = baBuffer.size();

    char szBuff[100] = { 0 };
    QString strResult;
    for(int i = 0; i < nLen; i++)
    {
        sprintf(szBuff," %02X", pBuff[i] & 0xFF);
        strResult += QString(szBuff);
    }
    qDebug("***OnSerialReadPowerOff,总数:%d 收到:%d字节 ->%s", m_baSerialPO.size(), nLen, strResult.toStdString().c_str());
}

void AppData::OnSerialSendCtrl(QByteArray ba)
{
    if( m_SerialCtrl.isOpen() )
    {
        m_SerialCtrl.write(ba);
        //m_SerialCtrl.write(ba);
        //qDebug("-------AppData::OnSerialSendCtrl----3---");
       // m_SerialCtrl.waitForBytesWritten();
       // qDebug("-------AppData::OnSerialSendCtrl----4---");
    }else{
        return;
    }

    //以下是打印信息
    char *pBuff = ba.data();
    int nLen = ba.size();

    char szBuff[100] = { 0 };
    QString strResult;
    for(int i = 0; i < nLen; i++)
    {
        sprintf(szBuff," %02X", pBuff[i] & 0xFF);
        strResult += QString(szBuff);
    }

    char szInfo[100] = { 0 };
    sprintf(szInfo,"->Send ctrl cmd Total:%d", ba.size());
    armCommLog(szInfo);
    armCommLog(strResult);
    //QTime cur = QTime::currentTime();
    //qDebug("***OnSerialSendCtrl 发送总数:%d  %02d:%02d:%02d-%03d  ->\n%s \n", ba.size(), cur.hour(),cur.minute(),cur.second(),cur.msec(), strResult.toStdString().c_str());
}

void AppData::OnSerialSendColl(QByteArray ba)
{
    if( m_SerialColl.isOpen() )
    {
        m_SerialColl.write(ba);
    }

    //以下是打印信息
    char *pBuff = ba.data();
    int nLen = ba.size();

    char szBuff[100] = { 0 };
    QString strResult;
    for(int i = 0; i < nLen; i++)
    {
        sprintf(szBuff," %02X", pBuff[i] & 0xFF);
        strResult += QString(szBuff);
    }

    char szInfo[100] = { 0 };
    sprintf(szInfo,"->Send coll cmd Total:%d", ba.size());
    armCommLog(szInfo);
    armCommLog(strResult);
    //qDebug("***OnSerialSendColl 发送总数:%d  ->%s", ba.size(), strResult.toStdString().c_str());
}

void AppData::getSerialCtrl(QByteArray &ba)
{
    m_mtData.lock();
    ba.append(m_baSerialCtrl);
    m_mtData.unlock();
}

void AppData::getSerialColl(QByteArray &ba)
{
    m_mtData.lock();
    ba.append(m_baSerialColl);
    m_mtData.unlock();
}

int  AppData::getCtrlDataLen()
{
    int nCnt = 0;
    m_mtData.lock();
    nCnt = m_baSerialCtrl.size();
    m_mtData.unlock();
    return nCnt;
}

int  AppData::getCollDataLen()
{
    int nCnt = 0;
    m_mtData.lock();
    nCnt = m_baSerialColl.size();
    m_mtData.unlock();
    return nCnt;
}

void AppData::clearSerialCtrl()
{
    m_mtData.lock();
    m_baSerialCtrl.clear();
    m_mtData.unlock();
}

void AppData::clearSerialColl()
{
    m_mtData.lock();
    m_baSerialColl.clear();
    m_mtData.unlock();
}

//枚举所有串口
void AppData::ListSerialPort()
{
    QString description;
    QString manufacturer;
    QString serialNumber;
    QString portName;
    QString strInfo;
    qDebug(" ---------   List Serial Ports   ---------");
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
    {
        description = info.description();//串口描述
        manufacturer = info.manufacturer();//串口设备制造商
        serialNumber = info.serialNumber();//串口序列号
        portName = info.portName();//串口名

        strInfo = "描述: " + description + " 厂商: " + manufacturer + " 编号: " + serialNumber + " 端口: " + portName;
        std::string str = strInfo.toStdString();

        m_vecUSBList.push_back( portName.toStdString() );
        /*
        if( str.find("ttyUSB") != str.npos )
        {
            m_vecUSBList.push_back( portName.toStdString() );
        }*/
        qDebug("%s", str.c_str());
    }
    qDebug(" ---------   List Serial Ports done  ---------\n");
}

bool AppData::isSerialCtrlOpen()
{
    bool bResult = true;
    if( !m_SerialCtrl.isOpen())
    {
        bResult = false;
    }
    return bResult;
}

bool AppData::isSerialCollOpen()
{
    bool bResult = true;
    if( !m_SerialColl.isOpen())
    {
        bResult = false;
    }
    return bResult;
}

bool AppData::isSerialPowerOpen()
{
    if( m_strPortPowerOff.isEmpty())
    {
        return false;
    }
    return true;
}

bool AppData::isSerialOpen()
{
    bool bResult = true;
    if( !m_SerialCtrl.isOpen())
    {
        //qDebug("---->数据控制端口开启错误! [%s]", m_strPortCtrl.toStdString().c_str());
        bResult = false;
    }

    if( !m_SerialColl.isOpen())
    {
        //qDebug("---->数据采集端口开启错误! [%s]", m_strPortColl.toStdString().c_str());
        bResult = false;
    }

    return bResult;
}

void AppData::serialCmdInit()
{
    DataSerialTask task;
    task.m_iCmdCode = MACHINE_INIT;
    m_pSerialWorker->SerialCmdTask(task);
}

void AppData::serialCmdMeasure()
{
    DataSerialTask task;
    task.m_iCmdCode = m_iMeasureType;
    task.m_iCmdParam1 = m_iMeasureComp;

    m_pSerialWorker->SerialCmdTask(task);
}

void AppData::serialCmdMeasure2(QString strName,QString strType,int iType)
{
    DataSerialTask task;
    task.m_iCmdCode = MACHINE_MEASURE2;

    task.m_iCmdParam1 = iType;
    task.m_strParam1 = strName;
    task.m_strParam2 = strType;
    m_pSerialWorker->SerialCmdTask(task);
}

void AppData::armCmdInit()
{
    DataSerialTask task;
    task.m_iCmdCode = MACHINE_ARM_INIT;
    m_pSerialWorker->SerialCmdTask(task);
}

void AppData::armCmdMeasure()
{
    DataSerialTask task;
    task.m_iCmdCode = MACHINE_ARM_MEASURE;
    m_pSerialWorker->SerialCmdTask(task);
}

void AppData::armCmdWash(int nType,int nCnt)
{
    DataSerialTask task;
    task.m_iCmdCode = MACHINE_ARM_WASH;

    task.m_iCmdParam1 = nType;
    task.m_iCmdParam2 = nCnt;
    m_pSerialWorker->SerialCmdTask(task);
}

void AppData::armCmdMirrorInfo()
{
    DataSerialTask task;
    task.m_iCmdCode = MACHINE_ARM_MIRROR_QUERY;
    m_pSerialWorker->SerialCmdTask(task);
}

void AppData::armCmdMirrorSet(int x, int y)
{
    DataSerialTask task;
    task.m_iCmdCode = MACHINE_ARM_MIRROR_SET;

    task.m_iCmdParam1 = x;
    task.m_iCmdParam2 = y;
    m_pSerialWorker->SerialCmdTask(task);

}

void AppData::armCmdMirrorPower()
{//当前强度查询
    DataSerialTask task;
    task.m_iCmdCode = MACHINE_ARM_MIRROR_POWER;
    m_pSerialWorker->SerialCmdTask(task);
}

void AppData::armCmdMirrorAutoSet()
{//自动调整
    DataSerialTask task;
    task.m_iCmdCode = MACHINE_ARM_MIRROR_AUTO;
    m_pSerialWorker->SerialCmdTask(task);
}

void AppData::armCmdSelfCheck()
{//自检
    DataSerialTask task;
    task.m_iCmdCode = MACHINE_ARM_SELF_CHECK;
    task.m_iCmdParam1 = 1;//nType;
    m_pSerialWorker->SerialCmdTask(task);
}

void AppData::serialCmdMeasure2Sel(int iType)
{
    DataSerialTask task;
    task.m_iCmdCode = MACHINE_MEASURE_SEL;

    task.m_iCmdParam1 = iType;
    m_pSerialWorker->SerialCmdTask(task);
}

void AppData::serialCmdWash()
{
    DataSerialTask task;
    task.m_iCmdCode = MACHINE_WASH;
    m_pSerialWorker->SerialCmdTask(task);
}

void AppData::serialCmdEmpty()
{
    DataSerialTask task;
    task.m_iCmdCode = MACHINE_EMPTY;
    m_pSerialWorker->SerialCmdTask(task);
}

void AppData::serialCmdLight(int iCmd)
{
    DataSerialTask task;
    task.m_iCmdParam1 = iCmd;
    task.m_iCmdCode = MACHINE_LIGHT;
    m_pSerialWorker->SerialCmdTask(task);
}

void AppData::serialCmdMeasureX(int iCmd)
{
    //if( isSerialCtrlOpen() )
    {
        DataSerialTask task;
        task.m_iCmdCode = MACHINE_MEASURE_X;
        task.m_iCmdParam1 = iCmd;

        m_pSerialWorker->SerialCmdTask(task);
    }
}

void AppData::serialCmdMeasureX(int iCmd,double dParam)
{
    DataSerialTask task;
    task.m_iCmdCode = MACHINE_MEASURE_X;
    task.m_iCmdParam1 = iCmd;
    task.m_dCmdParam1 = dParam;
    m_pSerialWorker->SerialCmdTask(task);
}

void AppData::serialCmdMeasureXSel(int iCmd, int iSel)
{
    DataSerialTask task;
    task.m_iCmdCode = MACHINE_MEASURE_X;
    task.m_iCmdParam1 = iCmd;
    task.m_iCmdParam2 = iSel;
    m_pSerialWorker->SerialCmdTask(task);
}

void AppData::serialCmdMeasureX(int iCmd, int iType1, int iType2)
{
    DataSerialTask task;
    task.m_iCmdCode = MACHINE_MEASURE_X;
    task.m_iCmdParam1 = iCmd;
    task.m_iCmdParam2 = iType1;
    task.m_iCmdParam3 = iType2;
    m_pSerialWorker->SerialCmdTask(task);
}

void AppData::serialCmdMeasureTemp(bool bEnable, int nType, int nValue)
{
    if( isSerialCtrlOpen() )
    {
        DataSerialTask task;
        task.m_iCmdCode = MACHINE_TEMPERATURE;
        task.m_bEnable = bEnable;
        task.m_iCmdParam1 = nType;
        task.m_iCmdParam2 = nValue;

        m_pSerialWorker->SerialCmdTask(task);
    }
}

void AppData::serialCmdMeasureSPool()
{
    //if( isSerialOpen() )
    {
        DataSerialTask task;
        task.m_iCmdCode = MACHINE_SAMPLEPOOL;
        m_pSerialWorker->SerialCmdTask(task);
    }
}

void AppData::serialCmdPostion(int iTYpe, int iP1, int iP2)
{
    DataSerialTask task;
    task.m_iCmdCode = MACHINE_POSTION;
    task.m_iCmdParam1 = iTYpe;
    task.m_iCmdParam2 = iP1;
    task.m_iCmdParam3 = iP2;

    m_pSerialWorker->SerialCmdTask(task);
}

void AppData::serialCmdMirrorCmdRead()
{
    DataSerialTask task;
    task.m_iCmdCode = MACHINE_MIRROR_READ;
    m_pSerialWorker->SerialCmdTask(task);
}

void AppData::serialCmdMirrorCmdSet(int x, int y)
{
    DataSerialTask task;
    task.m_iCmdCode = MACHINE_MIRROR_SET;
    task.m_iCmdParam1 = x;
    task.m_iCmdParam2 = y;
    m_pSerialWorker->SerialCmdTask(task);
}

void AppData::debugCmd(int i)
{//MACHINE_ARM_DEBUG
    DataSerialTask task;
    task.m_iCmdCode = MACHINE_ARM_DEBUG;
    task.m_iCmdParam1 = i;
    m_pSerialWorker->SerialCmdTask(task);
}

bool AppData::isTaskRun()
{
    return m_pSerialWorker->runStatus();
}

void AppData::StopRun()
{
    m_pSerialWorker->setStopFlag(true);
}

void AppData::startRun()
{
    m_pSerialWorker->setStopFlag(false);
}

void AppData::serialCmdMirrorCmdQuery()
{
    DataSerialTask task;
    task.m_iCmdCode = MACHINE_MIRROR_QUERY;
    m_pSerialWorker->SerialCmdTask(task);
}

void AppData::serialCmdMirrorCmdAdjust(int iStep,int iRange1,int iRange2)
{
    DataSerialTask task;
    task.m_iCmdCode = MACHINE_MIRROR_ADJUST;
    task.m_iCmdParam1 = iStep;
    task.m_iCmdParam2 = iRange1;
    task.m_iCmdParam3 = iRange2;
    m_pSerialWorker->SerialCmdTask(task);
}

void AppData::serialCmdUITest()
{
    DataSerialTask task;
    task.m_iCmdCode = MACHINE_UI;
    m_pSerialWorker->SerialCmdTask(task);
}

void AppData::OnSerialCmdUI(QString strMsg)
{
    qDebug("AppData:: ++++ %s", strMsg.toStdString().c_str());
    emit sigMachineStatus(strMsg);
}

//校验
void AppData::InvertUint8(unsigned char *DesBuf, unsigned char *SrcBuf)
{
    int i;
    unsigned char temp = 0;
    for (i = 0; i < 8; i++)
    {
        if (SrcBuf[0] & (1 << i))
            temp |= 1 << (7 - i);
    }
    DesBuf[0] = temp;
}

void AppData::InvertUint16(unsigned short *DesBuf, unsigned short *SrcBuf)
{
    int i;
    unsigned short temp = 0;
    for (i = 0; i < 16; i++)
    {
        if (SrcBuf[0] & (1 << i))
            temp |= 1 << (15 - i);
    }
    DesBuf[0] = temp;
}

unsigned short AppData::CRC16_X25(unsigned char *puchMsg, unsigned int usDataLen)
{
    unsigned short wCRCin = 0xFFFF;
    unsigned short wCPoly = 0x1021;
    unsigned char wChar = 0;
    unsigned char i;
    while (usDataLen--)
    {
        wChar = *(puchMsg++);
        InvertUint8(&wChar, &wChar);
        wCRCin ^= (wChar << 8);

        for (i = 0; i < 8; i++)
        {
            if (wCRCin & 0x8000)
                wCRCin = (wCRCin << 1) ^ wCPoly;
            else
                wCRCin = wCRCin << 1;
        }
    }
    InvertUint16(&wCRCin, &wCRCin);
    return (wCRCin ^ 0xFFFF);
}

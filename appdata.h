#ifndef APPDATA_H
#define APPDATA_H

#include <QObject>
#include <QGlobalStatic>
#include "threadserialworker.h"
#include <QSerialPortInfo>
#include <QSerialPort>
#include "DataInfo.h"
#include "dataserialtask.h"
#include "inc.h"
#include "thdserialtask.h"

#define App AppData::instance()

class AppData : public QObject
{
    Q_OBJECT
public:
    explicit AppData(QObject *parent = nullptr);

signals:
    void sigAppTest();
    void sigCmd();
    void sigMachineStatus(QString);

public:
    int m_SPP_35um;
    int m_SPP_REF;
    int m_SPP_100um;

public:
    static AppData* instance();

private:
    QString m_strOilName;
    bool  m_bTempControl;

public:
    bool getTempControl();
    void setTempControl(bool bTemp);

public:
    void setOilName(QString);
    QString getOilName();

    void test();
    void shutDown();

    void SetInfo(QByteArray &);
    void SetInfo2(QString strIP);
    void SetMDJInfo(double, double);
    void getInfo(MachineInfo &);

    void setMeaTimesAdd(int i);
    int  getMeaTimes();

    //void setLightState(bool);
    //bool  getLightState();

    void setScene(int);
    int  getScene();

    void setInitState(bool bState);
    bool getInitState();
private:
    //bool m_lightSate;
    int  m_iScene;//场景 1：全虚拟  2：半虚拟  3：实际 0：未初始化
    bool m_bInitState;//是否进行过初始化

public slots:
    void OnSerialReadTest();//专用测试端口
//    void OnSerialRead();
    void OnSerialReadColl();
    void OnSerialReadCtrl();
    void OnSerialReadMdj();//密度计
    void OnSerialReadPowerOff();//关机

    void OnSerialSendCtrl(QByteArray ba);
    void OnSerialSendColl(QByteArray ba);
    void OnSerialCmdUI(QString);
    void QueryInfoTask();
public:
    ThreadSerialWorker *m_pSerialWorker;//主线程管理串口

private:
    QMutex m_mtData;//锁数据
    QMutex m_mtLog;//锁log
    MachineInfo m_mcInfo;

    //QVector<double> m_vecMdj;//密度计密度平滑数组
    double m_dMdjValue;//密度计密度
    double m_dMdjTemp;//密度计温度

    QString m_strPortCtrl;//控制串口名
    QString m_strPortColl;//采集串口名
    QString m_strPortMdj;//密度计
    QString m_strPortPowerOff;//关机

    QSerialPort m_SerialTest;//测试端口

    QSerialPort m_SerialCtrl;//控制串口
    QSerialPort m_SerialColl;//采集串口
    QSerialPort m_SerialMdj;//密度计
    QSerialPort m_SerialPO;//关机

    //ThdSerialTask *m_pSerialTask;//子线程管理串口

    QByteArray m_baMachineInfo;//96个字节的信息

    QByteArray m_baSerialCtrl;
    QByteArray m_baSerialColl;
    QByteArray m_baSerialMdj;
    QByteArray m_baSerialPO;

    QVector<std::string> m_vecUSBList;
    QByteArray m_baSerialTest;//收集测试的数据
    void ComDelay();
    //int m_MeasureTime;
public:
    void TestSerial();
    void openSerial();
    void ListSerialPort();

    void init(QString strPortCtrl, QString strPortColl);//控制和数据采集端口
    void initComInfo();
    void InitWorker();
    void deInit();

    void clearSerialCtrl();
    void clearSerialColl();
    void getSerialCtrl(QByteArray &);//获得串口控制缓存数据
    void getSerialColl(QByteArray &);//获得窗口采集缓存数据

    int  getCtrlDataLen();
    int  getCollDataLen();

    void armCmdInit();
    void armCmdMeasure();
    void armCmdWash(int,int);
    void armCmdMirrorInfo();
    void armCmdMirrorSet(int,int);
    void armCmdMirrorPower();
    void armCmdMirrorAutoSet();
    void armCmdSelfCheck();
    void serialCmdUITest();
    void serialCmdInit();
    void serialCmdMeasure();
    void serialCmdMeasure2(QString,QString,int);
    void serialCmdMeasure2Sel(int iType);
    void serialCmdWash();
    void serialCmdEmpty();//排空
    void serialCmdMeasureTemp(bool, int,int);//设置-温度设置测量
    void serialCmdMeasureSPool();//设置-样品池检查
    void serialCmdPostion(int, int, int);
    void serialCmdMirrorCmdRead();
    void serialCmdMirrorCmdSet(int, int);
    void serialCmdMirrorCmdQuery();
    void serialCmdMirrorCmdAdjust(int,int,int);
    void serialCmdMeasureX(int);
    void serialCmdMeasureX(int,double);
    void serialCmdMeasureX(int , int , int);
    void serialCmdMeasureXSel(int, int);
    bool isSerialOpen();
    bool isSerialCtrlOpen();
    bool isSerialCollOpen();
    bool isSerialPowerOpen();
    bool isTaskRun();
    void StopRun();
    void startRun();
    void serialCmdLight(int);
    void debugCmd(int);

    void setArmStatus(QByteArray &);//设置96字节数据
    int  getSamplePoolPos();//获得样品池位置
    double  getMachineSamplePoolTemp();//获得样品池温度

    double  getMachineJYQTemp();//获得进样器温度
    double  getMachineMD();//获得密度计密度
    double  getMachineMdjTemp();//获得密度计温度
    int  getMachineLightLevel();//获得光源强度
    void getArmMirrorPos(int &x, int &y);
    bool isMdjOnLine();//密度计是否在线
    void getSwitchState(bool &, bool &, bool &);
    int CalcInt(char c1, char c2, char c3, char c4);
    //校验
private:
    void InvertUint8(unsigned char *DesBuf, unsigned char *SrcBuf);
    void InvertUint16(unsigned short *DesBuf, unsigned short *SrcBuf);

public:
    int m_iMeasureType;//35,100, 35&100
    int m_iMeasureClass;//标准，精密
    int m_iMeasureComp;//参池比
    double m_dMdjCalcValue;
    //double m_dTempSetting;

    QString m_strMeaName;//测量名
    QString m_strMeaType;//汽油...

    void log(QString&);
    void logs(QString);
    void log(QString strFile, QString msg);
    void armCommLog(QString msg);//arm通讯日志
    void armMdjLog(QString);
    //QByteArray m_baReference;//参池比数据
    //QByteArray m_baMeasureRes;//测量结果

    //密度校正
    void setMdjCalc(double  dMdj);
    double getMdjCalc();

    //设定温度
    //void setTempture(double dTemp);
    //double getTempSetting();

    void readJsonCfg();
    void writeJsonCfg();
public:
    unsigned short CRC16_X25(unsigned char *puchMsg, unsigned int usDataLen);

public:
    ST_MEASUREINFO m_meaInfo;
};

#endif // APPDATA_H

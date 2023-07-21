#include "dlgdebug.h"
#include "ui_dlgdebug.h"
#include "appdata.h"

DlgDebug::DlgDebug(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgDebug)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    connect(App->m_pSerialWorker, SIGNAL(sigMachineMsg(QString)), this, SLOT(OnMsg(QString)));
    connect(App->m_pSerialWorker, SIGNAL(sigMachineInfo(QByteArray,int)), this, SLOT(OnRet(QByteArray,int)));

    ui->labSwitch->setText("");
    m_timerQuery = startTimer(500);
}

DlgDebug::~DlgDebug()
{
    delete ui;
}

void DlgDebug::timerEvent(QTimerEvent *event)
{
    if( event->timerId() == m_timerQuery )
    {
        bool sw1, sw2, sw3;
        App->getSwitchState(sw1, sw2, sw3);

        std::string strsw1,strsw2,strsw3;
        if( sw1 )
        {
            strsw1 = "开";
        }else{
            strsw1 = "关";
        }

        if( sw2 )
        {
            strsw2 = "开";
        }else{
            strsw2 = "关";
        }

        if( sw3 )
        {
            strsw3 = "开";
        }else{
            strsw3 = "关";
        }

        std::string strInfo = "sw1:" + strsw1 + " sw2:" + strsw2 + " sw3: " + strsw3;
        ui->labSwitch->setText(strInfo.c_str());
    }
}

void DlgDebug::OnMsg(QString strInfo)
{
    ui->label->setText(strInfo);
}

void DlgDebug::OnRet(QByteArray ba,int id)
{
    QString strResult;
    char szDebug[200] = { 0 };
    int nCnt = ba.size();
    if( id == 1 )
    {//缓存数据
        strResult = "";
        m_ba = ba;
        sprintf(szDebug, "总数:%d\n", nCnt);
        strResult += szDebug;
        for(int i = 0; i < nCnt; i ++)
        {
            if((( i % 5) == 0) && ( i != 0 ))
            {
                strResult += "\n";
            }

            int iData = m_ba.at(i)  & 0xFF;
            sprintf(szDebug, "%02d:[0x%02X] ", i+1, iData);
            strResult += szDebug;
        }
        strResult += "\n\n";
        for(int i = 0; i < nCnt; i ++)
        {
            int iData = m_ba.at(i)  & 0xFF;
            sprintf(szDebug, "0x%02X,",iData);
            strResult += szDebug;
        }
        ui->txInfo->setText(strResult);
    }else if( id == 2)
    {//比较上次数据
        int nCntSrc = m_ba.size();
        int nCntDst = ba.size();

        int nCntMin = 0;
        if( nCntSrc < nCntDst )
        {
            nCntMin = nCntSrc;
        }else{
            nCntMin = nCntDst;
        }
        strResult = "";
        sprintf(szDebug, "总数:%d\n", nCntDst);
        strResult += szDebug;
        for(int i = 0; i < nCntMin; i ++)
        {
            if( m_ba[i] != ba[i])
            {
                int j1 = m_ba[i] & 0xFF;
                int j2 = ba[i] & 0xFF;
                sprintf(szDebug,"->%02d  %02X:%02X\n", i, j1, j2);
                strResult += szDebug;
            }
        }
        ui->txInfo->setText(strResult);
    }
}

void DlgDebug::on_pushButton_clicked()
{//返回
    //accept();
    reject();
}

void DlgDebug::on_pB32_2_clicked()
{//缓存
    App->debugCmd(99);
}

void DlgDebug::on_pB32_3_clicked()
{//对比
    App->debugCmd(100);
}

void DlgDebug::on_pB11_clicked()
{
    App->debugCmd(1);
}

void DlgDebug::on_pB12_clicked()
{
    App->debugCmd(2);
}

void DlgDebug::on_pB21_clicked()
{
    App->debugCmd(3);
}

void DlgDebug::on_pB22_clicked()
{
    App->debugCmd(4);
}

void DlgDebug::on_pB31_clicked()
{
    App->debugCmd(5);
}

void DlgDebug::on_pB32_clicked()
{
    App->debugCmd(6);
}

void DlgDebug::on_pB41_clicked()
{//进样器复位
    App->debugCmd(7);
}

void DlgDebug::on_pB42_clicked()
{//进样器0
    App->debugCmd(8);
}

void DlgDebug::on_pB43_clicked()
{//进样器5500
    App->debugCmd(9);
}

void DlgDebug::on_pB44_clicked()
{//进样器22000
    App->debugCmd(10);
}

void DlgDebug::on_pB51_clicked()
{//快速测试
    App->debugCmd(11);
}

void DlgDebug::on_pB61_clicked()
{//初始化
    App->armCmdInit();
}

void DlgDebug::on_pB62_clicked()
{//35um
    App->debugCmd(12);
}

void DlgDebug::on_pB63_clicked()
{//ref
    App->debugCmd(13);
}

void DlgDebug::on_pB64_clicked()
{//100um
    App->debugCmd(14);
}

void DlgDebug::on_pB65_clicked()
{
    char szBuff[100] = { 0 };
    sprintf(szBuff,"样品池位置: %d", App->getSamplePoolPos());
    ui->txInfo->setText(szBuff);
}

void DlgDebug::on_pB90_clicked()
{
    qInfo("%d", 1/0);
}

void DlgDebug::on_pB91_clicked()
{//光源关闭
    App->debugCmd(15);
}

void DlgDebug::on_pB92_clicked()
{//光源自动
    App->debugCmd(16);
}

void DlgDebug::on_pB66_clicked()
{
    App->m_pSerialWorker->CleanREF();
}

void DlgDebug::on_pB67_clicked()
{
    App->debugCmd(17);
}

void DlgDebug::on_pB68_clicked()
{
    App->debugCmd(18);
}

void DlgDebug::on_pB68_1_clicked()
{
    App->debugCmd(19);
}

void DlgDebug::on_pB68_2_clicked()
{
    App->debugCmd(20);
}

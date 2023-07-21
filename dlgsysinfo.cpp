#include "dlgsysinfo.h"
#include "ui_dlgsysinfo.h"
#include "appdata.h"
#include <QtWidgets/qdesktopwidget.h>
#include <QHostAddress>
#include <QNetworkInterface>
DlgSysInfo::DlgSysInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgSysInfo)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    resize(800,1280);
    initSysInfo();
    InitInfo();
    m_timerID = startTimer(1000);

    QString dateTime = __DATE__;
    QString strTime = __TIME__;
    QString strVerison = "版本信息: " + dateTime + " " + strTime;

    ui->labelversion->setText(strVerison);
    this->setStyleSheet("QDialog { border-image: url(:/new/public/png/public/sysInfo.png); }");
    ui->pbTitle->setStyleSheet("border-image: url(:/new/public/png/public/title0.png)");
}

DlgSysInfo::~DlgSysInfo()
{
    delete ui;
}

void DlgSysInfo::InitInfo()
{
    MachineInfo mc;
    App->getInfo(mc);

    QDateTime dtCur = QDateTime::currentDateTime();
    int nSeconds = mc.dtMdj.secsTo(dtCur);

    ui->label_1->setText(QString::number(mc.iLightPower));
    ui->label_2->setText(QString::number(mc.iTempYpc,'f', 1));
    //ui->label_3->setText(QString::number(mc.dMdjTemp,'f', 1));
    ui->label_4->setText(QString::number(mc.iTempJyq,'f', 1));
    //ui->label_5->setText(QString::number(mc.dMdj,'f', 5));
    ui->label_6->setText( mc.strIP.c_str() );

    if( nSeconds >= 5 )
    {
        ui->label_3->setText("密度计未连接!");
        ui->label_5->setText("密度计未连接!");
    }else{
        ui->label_3->setText(QString::number(mc.dMdjTemp,'f', 1));
        ui->label_5->setText(QString::number(mc.dMdj,'f', 5));
    }
}

void DlgSysInfo::timerEvent(QTimerEvent *event)
{
    if( event->timerId() == m_timerID )
    {
        InitInfo();
    }
}

void DlgSysInfo::on_pbTitle_clicked()
{
    reject();
}

void DlgSysInfo::initSysInfo()
{
    QString strIp;
    QList<QHostAddress> list =QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list)
    {
       if(address.protocol() ==QAbstractSocket::IPv4Protocol)
       {
           strIp = address.toString();
           if( strIp == "127.0.0.1")
           {
               continue;
           }else{
               break;
           }
       }
    }

    App->SetInfo2( strIp );
}

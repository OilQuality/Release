#include "dlgclean.h"
#include "dlgsysinfo.h"
#include "ui_dlgclean.h"
#include <QtWidgets/qdesktopwidget.h>
#include <QTime>
#include "appdata.h"

DlgClean::DlgClean(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgClean)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    resize(800,1280);

    this->setStyleSheet("QDialog { border-image: url(:/new/page3/png/page3/clean.png); }");
    ui->pbTitle->setStyleSheet("border-image: url(:/new/page3/png/page3/title.png)");
    ui->pbHome->setStyleSheet("border-image: url(:/new/public/png/public/home.png)");
    ui->pbInfo->setStyleSheet("border-image: url(:/new/public/png/public/info.png)");

    ui->pbUp->setStyleSheet("QPushButton{border-image: url(:/new/public/png/public/up1.png);}"
                            "QPushButton:pressed{border-image: url(:/new/public/png/public/up2.png);}");

    ui->pbDown->setStyleSheet("QPushButton{border-image: url(:/new/public/png/public/dn1.png);}"
                              "QPushButton:pressed{border-image: url(:/new/public/png/public/dn2.png);}");

    ui->pbUp2->setStyleSheet("QPushButton{border-image: url(:/new/public/png/public/up1.png);}"
                            "QPushButton:pressed{border-image: url(:/new/public/png/public/up2.png);}");

    ui->pbDown2->setStyleSheet("QPushButton{border-image: url(:/new/public/png/public/dn1.png);}"
                              "QPushButton:pressed{border-image: url(:/new/public/png/public/dn2.png);}");

    ui->pbWash->setStyleSheet("border-image: url(:/new/page3/png/page3/btnWash.png)");
    ui->pbClean->setStyleSheet("border-image: url(:/new/page3/png/page3/btnClean.png)");
    ui->pbStop->setStyleSheet("border-image: url(:/new/page3/png/page3/btnStop2.png)");

    m_iWashTimes = 2;
    m_iCleanTimes = 2;
    ui->tvTimes->setNum(m_iWashTimes);
    ui->tvTimes2->setNum(m_iCleanTimes);

    m_timerID = startTimer(100);
    setTime();

    m_iStatus = 0;
    m_iTimeCur = 0;//当前计数
    m_iTimeCnt = 0;//总技术

    connect(App->m_pSerialWorker, SIGNAL(sigArmWashMsg(QString)), this, SLOT(OnWashTaskMsg(QString)));
    connect(App->m_pSerialWorker, SIGNAL(sigArmWashDone()), this, SLOT(OnWashTaskDone()));
}

DlgClean::~DlgClean()
{
    delete ui;
    killTimer(m_timerID);
}

void DlgClean::OnWashTaskMsg(QString strMsg)
{
    ui->txInfo->setText(strMsg);
}

void DlgClean::OnWashTaskDone()
{
    m_iStatus = 0;
    m_iTimeCnt = 0;
    ui->widget->setProgress(100);
    ui->pbWash->setStyleSheet("border-image: url(:/new/page3/png/page3/btnWash.png)");
    ui->pbClean->setStyleSheet("border-image: url(:/new/page3/png/page3/btnClean.png)");
    ui->pbStop->setStyleSheet("border-image: url(:/new/page3/png/page3/btnStop2.png)");
}

void DlgClean::setTime()
{
    QDate cd = QDate::currentDate();
    QTime ct = QTime::currentTime();
    QString strDate;
    strDate= QString("%1-%2-%3").arg(cd.year()).arg(cd.month(),2,10, QLatin1Char('0')).arg(cd.day(),2,10, QLatin1Char('0'));

    QString strTime = ct.toString();
    ui->labTime->setText(strTime);
    ui->labDate->setText(strDate);
}

void DlgClean::timerEvent(QTimerEvent *event)
{
    if( event->timerId() == m_timerID )
    {
        setTime();

        if( m_iTimeCnt > 0 )
        {
            m_iTimeCur ++;
            int nPercent = m_iTimeCur * 100 / m_iTimeCnt;
            if( nPercent > 99)
            {
                nPercent = 99;
            }
            ui->widget->setProgress(nPercent);
        }
    }
}

void DlgClean::on_pbTitle_clicked()
{
    if( m_iStatus != 0 )
    {
        ui->txInfo->setText("正在执行任务......");
    }else{
        reject();
    }
}

void DlgClean::on_pbHome_clicked()
{
    if( m_iStatus != 0 )
    {
        ui->txInfo->setText("正在执行任务......");
    }else{
        reject();
    }
}

void DlgClean::on_pbWash_clicked()
{//清洗
    if( m_iStatus != 0 )
    {
        ui->txInfo->setText("正在执行任务......");
    }else{
        App->armCmdWash(1, m_iWashTimes);
        ui->widget->setProgress(0);

        m_iStatus = 1;
        //计算时间
        m_iTimeCur = 0;
        m_iTimeCnt = 313 * m_iWashTimes;

        ui->pbWash->setStyleSheet("border-image: url(:/new/page3/png/page3/btnWash2.png)");
        ui->pbClean->setStyleSheet("border-image: url(:/new/page3/png/page3/btnClean2.png)");
        ui->pbStop->setStyleSheet("border-image: url(:/new/page3/png/page3/btnStop.png)");
    }
}

void DlgClean::on_pbClean_clicked()
{//排空
    if( m_iStatus != 0 )
    {
        ui->txInfo->setText("正在执行任务......");
    }else{
        App->armCmdWash(2, m_iCleanTimes);
        ui->widget->setProgress(0);

        m_iStatus = 2;
        //计算时间
        m_iTimeCur = 0;
        m_iTimeCnt = 253 * m_iCleanTimes;

        ui->pbWash->setStyleSheet("border-image: url(:/new/page3/png/page3/btnWash2.png)");
        ui->pbClean->setStyleSheet("border-image: url(:/new/page3/png/page3/btnClean2.png)");
        ui->pbStop->setStyleSheet("border-image: url(:/new/page3/png/page3/btnStop.png)");
    }
}

void DlgClean::on_pbUp_clicked()
{
    m_iWashTimes ++;
    if( m_iWashTimes > 20 )
    {
        m_iWashTimes = 20;
    }
    ui->tvTimes->setNum(m_iWashTimes);
}

void DlgClean::on_pbDown_clicked()
{
    m_iWashTimes --;
    if( m_iWashTimes < 1 )
    {
        m_iWashTimes = 1;
    }
    ui->tvTimes->setNum(m_iWashTimes);
}

void DlgClean::on_pbUp2_clicked()
{
    m_iCleanTimes ++;
    if( m_iCleanTimes > 20 )
    {
        m_iCleanTimes = 20;
    }
    ui->tvTimes2->setNum(m_iCleanTimes);
}

void DlgClean::on_pbDown2_clicked()
{
    m_iCleanTimes --;
    if( m_iCleanTimes < 1 )
    {
        m_iCleanTimes = 1;
    }
    ui->tvTimes2->setNum(m_iCleanTimes);
}

void DlgClean::on_pbStop_clicked()
{
    if( m_iStatus != 0 )
    {
        qInfo("set run stop...");
        App->StopRun();
    }else{
        ui->pbWash->setStyleSheet("border-image: url(:/new/page3/png/page3/btnWash.png)");
        ui->pbClean->setStyleSheet("border-image: url(:/new/page3/png/page3/btnClean.png)");
        ui->pbStop->setStyleSheet("border-image: url(:/new/page3/png/page3/btnStop2.png)");

        if( !App->isTaskRun())
        {
            App->startRun();
        }
    }
}

void DlgClean::on_pbInfo_clicked()
{
    DlgSysInfo dlg;
    dlg.move((QApplication::desktop()->width() - dlg.width()) / 2, (QApplication::desktop()->height() - dlg.height()) / 2);
    dlg.exec();
}

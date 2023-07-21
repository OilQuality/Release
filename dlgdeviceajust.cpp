#include "dlgdeviceajust.h"
#include "dlgsysinfo.h"
#include "dlgtemperaturesetting.h"
#include "ui_dlgdeviceajust.h"
#include <QDateTime>
#include <QtWidgets/qdesktopwidget.h>

DlgDeviceAjust::DlgDeviceAjust(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgDeviceAjust)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    this->setStyleSheet("QDialog { border-image: url(:/new/page4/png/page4/main113.png); }");

    ui->pb2->setStyleSheet("border-image: url(:/new/page4/png/page4/p11022.png)");
    ui->pbTitle->setStyleSheet("border-image: url(:/new/page4/png/page4/title5.png)");
    ui->pbHome->setStyleSheet("border-image: url(:/new/public/png/public/home.png)");
    ui->pbInfo->setStyleSheet("border-image: url(:/new/public/png/public/info.png)");

    m_timerID = startTimer(250);
}

DlgDeviceAjust::~DlgDeviceAjust()
{
    delete ui;
}

void DlgDeviceAjust::on_pb2_clicked()
{
    DlgTemperatureSetting dlg;
    dlg.move((QApplication::desktop()->width() - dlg.width()) / 2, (QApplication::desktop()->height() - dlg.height()) / 2);
    if( dlg.exec() == QDialog::Accepted )
    {
        accept();
    }
}

void DlgDeviceAjust::on_pbTitle_clicked()
{
    reject();
}

void DlgDeviceAjust::on_pbHome_clicked()
{
    accept();
}

void DlgDeviceAjust::on_pbInfo_clicked()
{
    //信息
    DlgSysInfo dlg;
    dlg.move((QApplication::desktop()->width() - dlg.width()) / 2, (QApplication::desktop()->height() - dlg.height()) / 2);
    dlg.exec();
}

void DlgDeviceAjust::setTime()
{
    QDate cd = QDate::currentDate();
    QTime ct = QTime::currentTime();
    QString strDate;
    strDate= QString("%1-%2-%3").arg(cd.year()).arg(cd.month(),2,10, QLatin1Char('0')).arg(cd.day(),2,10, QLatin1Char('0'));

    QString strTime = ct.toString();
    ui->labTime->setText(strTime);
    ui->labDate->setText(strDate);
}

void DlgDeviceAjust::timerEvent(QTimerEvent *event)
{
    if( event->timerId() == m_timerID )
    {
        setTime();
    }
}

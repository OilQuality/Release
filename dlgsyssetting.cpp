#include "dlgsysinfo.h"
#include "dlgsyssetting.h"
#include "dlgupdate.h"
#include "ui_dlgsyssetting.h"
#include <QDateTime>
#include <QtWidgets/qdesktopwidget.h>

DlgSysSetting::DlgSysSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgSysSetting)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);

    this->setStyleSheet("QDialog { border-image: url(:/new/page5/png/page5/main1.png); }");
    ui->pbTitle->setStyleSheet("border-image: url(:/new/page4/png/page4/title2.png)");
    ui->pbHome->setStyleSheet("border-image: url(:/new/public/png/public/home.png)");
    ui->pbInfo->setStyleSheet("border-image: url(:/new/public/png/public/info.png)");

    ui->pbTitle->move(0,0);
    ui->pbHome->move(718,0);
    ui->pbInfo->move(0,1160);
    ui->labTime->move(563,1179);
    ui->labDate->move(563,1225);

    ui->pb1->setStyleSheet("border-image: url(:/new/page5/png/page5/p01.png)");
    ui->pb2->setStyleSheet("border-image: url(:/new/page5/png/page5/p02.png)");
    ui->pb3->setStyleSheet("border-image: url(:/new/page5/png/page5/p07.png)");
    ui->pb4->setStyleSheet("border-image: url(:/new/page5/png/page5/p04.png)");
    ui->pb5->setStyleSheet("border-image: url(:/new/page5/png/page5/p05.png)");
    //ui->pb6->setStyleSheet("border-image: url(:/new/page5/png/page5/p06.png)");
    //ui->pb7->setStyleSheet("border-image: url(:/new/page5/png/page5/p07.png)");
    //ui->pb8->setStyleSheet("border-image: url(:/new/page5/png/page5/p08.png)");

    ui->pb1->setVisible(false);
    ui->pb2->setVisible(false);
    ui->pb4->setVisible(false);
    ui->pb5->setVisible(false);
    m_timerID = startTimer(250);
    setTime();
}

DlgSysSetting::~DlgSysSetting()
{
    delete ui;
}

void DlgSysSetting::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    QDate cd = QDate::currentDate();
    QTime ct = QTime::currentTime();
    QString strDate;
    strDate= QString("%1-%2-%3").arg(cd.year()).arg(cd.month(),2,10, QLatin1Char('0')).arg(cd.day(),2,10, QLatin1Char('0'));

    QString strTime = ct.toString();
    ui->labTime->setText(strTime);
    ui->labDate->setText(strDate);
}

void DlgSysSetting::setTime()
{
    QDate cd = QDate::currentDate();
    QTime ct = QTime::currentTime();
    QString strDate;
    strDate= QString("%1-%2-%3").arg(cd.year()).arg(cd.month(),2,10, QLatin1Char('0')).arg(cd.day(),2,10, QLatin1Char('0'));

    QString strTime = ct.toString();
    ui->labTime->setText(strTime);
    ui->labDate->setText(strDate);
}

void DlgSysSetting::on_pbTitle_clicked()
{
    reject();
}

void DlgSysSetting::on_pbHome_clicked()
{
    reject();
}

void DlgSysSetting::on_pbInfo_clicked()
{
    //信息
    DlgSysInfo dlg;
    dlg.move((QApplication::desktop()->width() - dlg.width()) / 2, (QApplication::desktop()->height() - dlg.height()) / 2);
    dlg.exec();
}

void DlgSysSetting::on_pb1_clicked()
{

}

void DlgSysSetting::on_pb2_clicked()
{

}

void DlgSysSetting::on_pb3_clicked()
{//系统升级
    DlgUpdate dlg;
    dlg.move((QApplication::desktop()->width() - dlg.width()) / 2, (QApplication::desktop()->height() - dlg.height()) / 2);
    if( dlg.exec() == QDialog::Accepted )
    {
        accept();
    }
}

void DlgSysSetting::on_pb4_clicked()
{

}

void DlgSysSetting::on_pb5_clicked()
{

}

void DlgSysSetting::on_pb6_clicked()
{

}

void DlgSysSetting::on_pb7_clicked()
{
}

void DlgSysSetting::on_pb8_clicked()
{
    qInfo("-------------");
}

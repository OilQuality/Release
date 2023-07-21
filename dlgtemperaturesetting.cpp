#include "dlgtemperaturesetting.h"
#include "ui_dlgtemperaturesetting.h"
#include "dlgnumpad.h"
# include <QtWidgets/qdesktopwidget.h>
#include "appdata.h"
#include "dlgsysinfo.h"
#include <QKeyEvent>

DlgTemperatureSetting::DlgTemperatureSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgTemperatureSetting)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    this->setStyleSheet("QDialog { border-image: url(:/new/page4/png/page4/main114.png); }");
    //ui->pb2->setStyleSheet("border-image: url(:/new/page4/png/page4/p11022.png)");
    ui->pbTitle->setStyleSheet("border-image: url(:/new/page4/png/page4/title6.png)");
    ui->pbHome->setStyleSheet("border-image: url(:/new/public/png/public/home.png)");
    ui->pbInfo->setStyleSheet("border-image: url(:/new/public/png/public/info.png)");

    m_timerID = startTimer(250);
    m_timerDataID = startTimer(1000);
    connect(App->m_pSerialWorker, SIGNAL(sigSerialTempMsg(double, double, double)), this, SLOT(OnMeasureTemp(double, double, double)));
}

void DlgTemperatureSetting::timerEvent(QTimerEvent *event)
{//温度查询
    if( event->timerId() == m_timerDataID )
    {
        App->serialCmdMeasureTemp(false, 0 , 0);
        MachineInfo mc;
        App->getInfo(mc);

       ui->leReal_1->setText(QString::number(mc.iTempYpc,'f', 1));
       ui->leReal_2->setText(QString::number(mc.iTempJyq,'f', 1));
       ui->leReal_3->setText(QString::number(mc.dMdjTemp,'f', 1));

       ui->le1->setText(QString::number(mc.iTempSetYpc,'f', 1));
       ui->le2->setText(QString::number(mc.iTempSetJyq,'f', 1));
       ui->le3->setText(QString::number(mc.iTempSetMdj,'f', 1));
    }

    if( event->timerId() == m_timerID )
    {
        setTime();
    }
}

void DlgTemperatureSetting::OnMeasureTemp(double db1, double db2, double db3)
{
    qDebug("temp: %02f %02f %02f",db1, db2, db3);
    ui->leReal_1->setText( QString::number(db1,10,1));
    ui->leReal_2->setText( QString::number(db2,10,1));
    ui->leReal_3->setText( QString::number(db3,10,1));
}

DlgTemperatureSetting::~DlgTemperatureSetting()
{
    delete ui;
}

void DlgTemperatureSetting::on_pushButton_clicked()
{
    DlgNumPad dlg;
    dlg.move((QApplication::desktop()->width() - dlg.width()) / 2, (QApplication::desktop()->height() - dlg.height()) / 2);
    if( dlg.exec() == QDialog::Accepted )
    {
        qDebug("click...Accepted");
        //ui->le1->setText(dlg.m_strNumKey);

        double dValue = dlg.m_strNumKey.toDouble();
        int nValue = dValue * 10;
        App->serialCmdMeasureTemp(true, 1 , nValue);
    }
}

void DlgTemperatureSetting::on_pushButton_2_clicked()
{
    DlgNumPad dlg;
    dlg.move((QApplication::desktop()->width() - dlg.width()) / 2, (QApplication::desktop()->height() - dlg.height()) / 2);
    if( dlg.exec() == QDialog::Accepted )
    {
        qDebug("click...Accepted");
        //ui->le2->setText(dlg.m_strNumKey);

        double dValue = dlg.m_strNumKey.toDouble();
        int nValue = dValue * 10;
        App->serialCmdMeasureTemp(true, 2 , nValue);
    }
}

void DlgTemperatureSetting::on_pushButton_3_clicked()
{
    DlgNumPad dlg;
    dlg.move((QApplication::desktop()->width() - dlg.width()) / 2, (QApplication::desktop()->height() - dlg.height()) / 2);
    if( dlg.exec() == QDialog::Accepted )
    {
        qDebug("click...Accepted");
        //ui->le3->setText(dlg.m_strNumKey);

        double dValue = dlg.m_strNumKey.toDouble();
        int nValue = dValue * 10;
        App->serialCmdMeasureTemp(true, 3 , nValue);
    }
}

void DlgTemperatureSetting::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Escape:
        break;
    default:
        QDialog::keyPressEvent(event);
    }
}

void DlgTemperatureSetting::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    App->StopRun();
}

void DlgTemperatureSetting::on_pbTitle_clicked()
{
    reject();
}

void DlgTemperatureSetting::on_pbHome_clicked()
{
    accept();
}

void DlgTemperatureSetting::on_pbInfo_clicked()
{
    //信息
    DlgSysInfo dlg;
    dlg.move((QApplication::desktop()->width() - dlg.width()) / 2, (QApplication::desktop()->height() - dlg.height()) / 2);
    dlg.exec();
}

void DlgTemperatureSetting::setTime()
{
    QDate cd = QDate::currentDate();
    QTime ct = QTime::currentTime();
    QString strDate;
    strDate= QString("%1-%2-%3").arg(cd.year()).arg(cd.month(),2,10, QLatin1Char('0')).arg(cd.day(),2,10, QLatin1Char('0'));

    QString strTime = ct.toString();
    ui->labTime->setText(strTime);
    ui->labDate->setText(strDate);
}

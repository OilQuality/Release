#include "dlgtimesetting.h"
#include "ui_dlgtimesetting.h"
#include <QDate>
#include <QTime>
#include "appdata.h"
#include <QKeyEvent>

DlgTimeSetting::DlgTimeSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgTimeSetting)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    resize(768,1024);

    m_timerID = startTimer(1000);

    QDate cd = QDate::currentDate();
    QTime ct = QTime::currentTime();
    QString strDate = QString("%1-%2-%3").arg(cd.year()).arg(cd.month(),2,10, QLatin1Char('0')).arg(cd.day(),2,10, QLatin1Char('0'));
    QString strTime = ct.toString();
    QString strKey = strDate  + " " + strTime;
    ui->lineEdit->setText(strKey);

    ui->leYear->setText(QString("%1").arg(cd.year()));
    ui->leMonth->setText(QString("%1").arg(cd.month()));
    ui->leDay->setText(QString("%1").arg(cd.day()));
    ui->leHour->setText(QString("%1").arg(ct.hour()));
    ui->leMinute->setText(QString("%1").arg(ct.minute()));
    ui->leSecond->setText(QString("%1").arg(ct.second()));
}

DlgTimeSetting::~DlgTimeSetting()
{
    delete ui;
}

void DlgTimeSetting::on_pushButton_2_clicked()
{
    reject();
}

void DlgTimeSetting::timerEvent(QTimerEvent *event)
{
    if( event->timerId() == m_timerID )
    {
        QDate cd = QDate::currentDate();
        QTime ct = QTime::currentTime();
        QString strDate = QString("%1-%2-%3").arg(cd.year()).arg(cd.month(),2,10, QLatin1Char('0')).arg(cd.day(),2,10, QLatin1Char('0'));
        QString strTime = ct.toString();
        QString strKey = strDate  + " " + strTime;
        ui->lineEdit->setText(strKey);
    }
}

//设置
void DlgTimeSetting::on_pushButton_clicked()
{
    int nYear,nMonth,nDay, nHour, nMinute, nSecond;

    nYear = ui->leYear->text().toInt();
    nMonth = ui->leMonth->text().toInt();
    nDay = ui->leDay->text().toInt();
    nHour = ui->leHour->text().toInt();
    nMinute = ui->leMinute->text().toInt();
    nSecond = ui->leSecond->text().toInt();

    QDateTime dt = QDateTime::currentDateTime();


    QString strTime = QString("%1-%2-%3 %4:%5:%6").arg(nYear).arg(nMonth).arg(nDay).arg(nHour).arg(nMinute).arg(nSecond);
    QDateTime dtTime = QDateTime::fromString(strTime, "yyyy-MM-dd hh:mm:ss");

    //QString strText = QString("%1.%2").arg( 10).arg(5);
    qDebug("strTime:%s",strTime.toStdString().c_str());
}

//年 -+
void DlgTimeSetting::on_pushButton_3_clicked()
{
    QString strKey = ui->leYear->text();
    int iValue = strKey.toInt();
    if( iValue > 0 )
    {
        iValue--;
        ui->leYear->setText(QString::number(iValue));
    }
}

void DlgTimeSetting::on_pushButton_4_clicked()
{
    QString strKey = ui->leYear->text();
    int iValue = strKey.toInt();
    iValue++;
    ui->leYear->setText(QString::number(iValue));
}
//月 -+
void DlgTimeSetting::on_pushButton_6_clicked()
{
    QString strKey = ui->leMonth->text();
    int iValue = strKey.toInt();
    if( iValue > 1 )
    {
        iValue--;
        ui->leMonth->setText(QString::number(iValue));
    }
}

void DlgTimeSetting::on_pushButton_5_clicked()
{
    QString strKey = ui->leMonth->text();
    int iValue = strKey.toInt();
    iValue++;
    if( iValue <= 12 )
    {
        ui->leMonth->setText(QString::number(iValue));
    }
}
//日 -+
void DlgTimeSetting::on_pushButton_8_clicked()
{
    QString strKey = ui->leDay->text();
    int iValue = strKey.toInt();
    if( iValue > 1 )
    {
        iValue--;
        ui->leDay->setText(QString::number(iValue));
    }
}

void DlgTimeSetting::on_pushButton_7_clicked()
{
    QString strKey = ui->leDay->text();
    int iValue = strKey.toInt();
    iValue++;
    if( iValue <= 31 )
    {
        ui->leDay->setText(QString::number(iValue));
    }
}
//时 -+
void DlgTimeSetting::on_pushButton_10_clicked()
{
    QString strKey = ui->leHour->text();
    int iValue = strKey.toInt();
    if( iValue > 0 )
    {
        iValue--;
        ui->leHour->setText(QString::number(iValue));
    }
}

void DlgTimeSetting::on_pushButton_9_clicked()
{
    QString strKey = ui->leHour->text();
    int iValue = strKey.toInt();
    iValue++;
    if( iValue <= 23 )
    {
        ui->leHour->setText(QString::number(iValue));
    }
}

//分 -+
void DlgTimeSetting::on_pushButton_12_clicked()
{
    QString strKey = ui->leMinute->text();
    int iValue = strKey.toInt();
    if( iValue > 0 )
    {
        iValue--;
        ui->leMinute->setText(QString::number(iValue));
    }
}

void DlgTimeSetting::on_pushButton_11_clicked()
{
    QString strKey = ui->leMinute->text();
    int iValue = strKey.toInt();
     iValue++;
    if( iValue <= 59 )
    {
        ui->leMinute->setText(QString::number(iValue));
    }
}
//秒
void DlgTimeSetting::on_pushButton_14_clicked()
{
    QString strKey = ui->leSecond->text();
    int iValue = strKey.toInt();
    if( iValue > 0 )
    {
        iValue--;
        ui->leSecond->setText(QString::number(iValue));
    }
}

void DlgTimeSetting::on_pushButton_13_clicked()
{
    QString strKey = ui->leSecond->text();
    int iValue = strKey.toInt();
    iValue++;
    if( iValue <= 59 )
    {
        ui->leSecond->setText(QString::number(iValue));
    }
}

void DlgTimeSetting::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Escape:
        break;
    default:
        QDialog::keyPressEvent(event);
    }
}

void DlgTimeSetting::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    App->StopRun();
}

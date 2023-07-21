#include "widget.h"
#include "ui_widget.h"
#include <qpainter.h>
#include <QDate>
#include <QTime>
#include <QtWidgets/qdesktopwidget.h>
#include "dlgmeasure.h"
#include "dlgwash.h"
#include "dlgresult.h"
#include "dlgsetup.h"
#include "appdata.h"
#include <QProcess>
#include <QDir>
#include <QDebug>
#include "appdata.h"
#include "dlginfo.h"
#include "dlgmeasurex.h"
#include "dlgmeasure2.h"
#include "dlgsysinfo.h"
#include <QHostInfo>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include "dlgmeasurepreset.h"
#include "dlgclean.h"
#include "dlgresults.h"
#include "dlgshutdown.h"
#include "dlgdebug.h"
#include "dlgmaintain.h"
#include "dlgsyssetting.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    qInfo("Widget start---");
    setWindowFlags(Qt::FramelessWindowHint);

    App->setScene(3);
    //ui->pbTest->setVisible(false);

    int nWidth = QApplication::desktop()->width();
    int nHeight = QApplication::desktop()->height();
    if(( nWidth == 800 ) && ( nHeight == 1280))
    {
        this->showFullScreen();
    }else{
        resize(800,1280);
    }

    m_timerID = startTimer(250);
    //m_timerCheck = startTimer(500);
    //m_timerQuery = startTimer(600);
    //m_timerTask  = startTimer(13*1000);

    ui->pushButton->setStyleSheet("border-image: url(:/new/page1/png/page1/p8.png)");
    ui->pushButton_1->setStyleSheet("border-image: url(:/new/page1/png/page1/p12.png)");
    ui->pushButton_1->setEnabled(false);
    ui->pushButton_2->setStyleSheet("border-image: url(:/new/page1/png/page1/p22.png)");
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setStyleSheet("border-image: url(:/new/page1/png/page1/p32.png)");
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setStyleSheet("border-image: url(:/new/page1/png/page1/p41.png)");
    //ui->pushButton_5->setStyleSheet("border-image: url(:/new/prefix1/png/btn52.png)");
    //ui->pushButton_5->setEnabled(false);

    ui->pushButton_5->setStyleSheet("border-image: url(:/new/page1/png/page1/p51.png)");
    ui->pushButton_5->setEnabled(true);

    ui->pushButton_6->setStyleSheet("border-image: url(:/new/page1/png/page1/p61.png)");
    ui->pbInfo->setStyleSheet("border-image: url(:/new/public/png/public/info.png)");

    /*
    if( App->isSerialPowerOpen() )
    {
        App->serialCmdInit();
    }else{
        ui->labInfo->setText("电源控制端口通讯异常!");
    }
    */

    //ui->labTime->installEventFilter(this);
    initSysInfo();
    App->initComInfo();
    App->InitWorker();
    ui->labInfo->setText("检查通讯.");

    connect( App->m_pSerialWorker, SIGNAL(sigArmInitDone()), SLOT(OnInitDone()));
    connect( App->m_pSerialWorker, SIGNAL(sigArmInitMsg(QString)), SLOT(OnInitMsg(QString)) );

    App->readJsonCfg();
    qInfo("Widget end***");
}

Widget::~Widget()
{
    delete ui;
    App->deInit();
}

void Widget::initSysInfo()
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

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(rect(), QPixmap(":/new/page1/png/page1/main.png"), QRect());
}

void Widget::timerEvent(QTimerEvent *event)
{
    if( event->timerId() == m_timerID )
    {
        QDate cd = QDate::currentDate();
        QTime ct = QTime::currentTime();
        QString strDate;
        strDate= QString("%1-%2-%3").arg(cd.year()).arg(cd.month(),2,10, QLatin1Char('0')).arg(cd.day(),2,10, QLatin1Char('0'));

        QString strTime = ct.toString();
        ui->labTime->setText(strTime);
        ui->labDate->setText(strDate);
    }
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == this->ui->labTime)
    {
        //判断事件类型是否为鼠标事件
        if (event->type() == QEvent::MouseButtonPress)
        {
            /*
            int i = App->getScene();
            if( i == 0 )
            {
                App->setScene(1);
                ui->labInfo->setText("检查通讯.");
            }else if( i == 1 )
            {
                App->setScene(2);
                ui->labInfo->setText("检查通讯..");
            }else if( i == 2 )
            {
                App->setScene(3);
                ui->labInfo->setText("检查通讯...");
            }else if( i == 3 )
            {
                App->setScene(1);
                ui->labInfo->setText("检查通讯.");
            }
            */
            return true;
        }
    }
    return QWidget::eventFilter(watched, event);
}

void Widget::OnInitMsg(QString strMsg)//初始化中的消息
{
    ui->labInfo->setText(strMsg);
}

void Widget::OnInitDone()//初始化完成
{
    ui->pushButton_1->setEnabled(true);
    ui->pushButton_1->setStyleSheet("border-image: url(:/new/page1/png/page1/p11.png)");

    ui->pushButton_2->setEnabled(true);
    ui->pushButton_2->setStyleSheet("border-image: url(:/new/page1/png/page1/p21.png)");

    ui->pushButton_3->setEnabled(true);
    ui->pushButton_3->setStyleSheet("border-image: url(:/new/page1/png/page1/p31.png)");
}

void Widget::OnMachineStatus(QString strMsg)
{
    qDebug("Widget:: %s", strMsg.toStdString().c_str());
}

void Widget::on_pushButton_1_clicked()
{//测量
    dlgMeasurePreset dlg;
    //DlgMeasure2 dlg;
    dlg.move((QApplication::desktop()->width() - dlg.width()) / 2, (QApplication::desktop()->height() - dlg.height()) / 2);
    if( dlg.exec() == QDialog::Accepted )
    {
        if( dlg.m_rtnHome == 1 )
        {
            qDebug("click...Accepted .............弹出结果界面...... %s", App->m_pSerialWorker->m_curMeaFile.toStdString().c_str());
            DlgInfo dlg(App->m_pSerialWorker->m_curMeaFile, nullptr);
            dlg.move((QApplication::desktop()->width() - dlg.width()) / 2, (QApplication::desktop()->height() - dlg.height()) / 2);
            dlg.exec();
        }else{

        }
    }
}

void Widget::on_pushButton_2_clicked()
{//清洗
    //DlgWash dlg;
    DlgClean dlg;
    dlg.move((QApplication::desktop()->width() - dlg.width()) / 2, (QApplication::desktop()->height() - dlg.height()) / 2);
    if( dlg.exec() == QDialog::Accepted )
    {
        qDebug("click...Accepted");
    }
}

void Widget::on_pushButton_3_clicked()
{//测量按钮 维护校正
    //DlgMeasureX dlg;
    DlgMaintain dlg;
    dlg.move((QApplication::desktop()->width() - dlg.width()) / 2, (QApplication::desktop()->height() - dlg.height()) / 2);
    if( dlg.exec() == QDialog::Accepted )
    {
        qDebug("click...Accepted");
    }
}

void Widget::on_pushButton_4_clicked()
{//结果
    qDebug("click...4");
    DlgResult dlg;
    //DlgResults dlg;
    dlg.move((QApplication::desktop()->width() - dlg.width()) / 2, (QApplication::desktop()->height() - dlg.height()) / 2);
    if( dlg.exec() == QDialog::Accepted )
    {
        qDebug("click...Accepted");
    }
}

void Widget::on_pushButton_5_clicked()
{//设置
    //DlgSetup dlg;
    DlgSysSetting dlg;
    dlg.move((QApplication::desktop()->width() - dlg.width()) / 2, (QApplication::desktop()->height() - dlg.height()) / 2);
    if( dlg.exec() == QDialog::Accepted )
    {
        qDebug("click...Accepted");
    }
}

void Widget::on_pushButton_6_clicked()
{//关机

    //关闭上位机
 #if defined (WIN32)
    QMessageBox msgBox;
    msgBox.setText("确实要关机吗?");
    //msgBox.setInformativeText("确实要关机吗?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.setStyleSheet("QMessageBox{ border:1px solid black; border-radius:4px } QPushButton{ min-width: 200px; min-height: 80px; font: 20pt} QLabel{min-width: 200px; min-height: 100px; font: 20pt};");
    int ret = msgBox.exec();
    if(ret == QMessageBox::Ok){
        qApp->quit();
    }
     //system("shutdown -s -t 00");
 #else
     qDebug("quit linux...............");

     //linux关机
     /*
     QProcess pro;    //通过QProcess类来执行第三方程序
     QString cmd = QString("shutdown -h now");
     pro.start(cmd);    //执行命令cmd
     pro.waitForStarted();
     pro.waitForFinished();
     */

     QMessageBox msgBox;
     msgBox.setText("确实要关机吗?");

     //msgBox.setInformativeText("确实要关机吗?");
     msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
     msgBox.setDefaultButton(QMessageBox::Ok);
     msgBox.setStyleSheet("QMessageBox{ border:1px solid black; border-radius:4px } QPushButton{ min-width: 200px; min-height: 80px; font: 20pt} QLabel{min-width: 200px; min-height: 100px; font: 20pt};");
     int ret = msgBox.exec();
     if(ret == QMessageBox::Ok){
         App->shutDown();
         DlgShutDown dlg;
         dlg.move((QApplication::desktop()->width() - dlg.width()) / 2, (QApplication::desktop()->height() - dlg.height()) / 2);
         dlg.exec();
     }
#endif
     //close();//qApp->quit();
}

void Widget::OnCheckDone()
{
    //qDebug("***** Widget::OnCheckDone() *****");
}

void Widget::on_pbInfo_clicked()
{
    DlgSysInfo dlg;
    dlg.move((QApplication::desktop()->width() - dlg.width()) / 2, (QApplication::desktop()->height() - dlg.height()) / 2);
    dlg.exec();
}

void Widget::on_pushButton_clicked()
{
    QDir dirRoot;
    if(dirRoot.exists("./dbg"))
    {
        DlgDebug dlg;
        dlg.move((QApplication::desktop()->width() - dlg.width()) / 2, (QApplication::desktop()->height() - dlg.height()) / 2);
        if( dlg.exec() == QDialog::Accepted )
        {
            //qDebug("click...Accepted");
        }
    }
}

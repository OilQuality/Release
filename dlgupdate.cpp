#include "dlgsysinfo.h"
#include "dlgupdate.h"
#include "ui_dlgupdate.h"

#include <QDir>
#include <QFileInfo>
#include <QProcess>
#include <QStorageInfo>
#include <QTime>
# include <QtWidgets/qdesktopwidget.h>

DlgUpdate::DlgUpdate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgUpdate)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);

    ui->pushButton3->setEnabled(false);

    ui->pbTitle->setStyleSheet("border-image: url(:/new/page7/png/page7/titile.png)");
    ui->pbHome->setStyleSheet("border-image: url(:/new/public/png/public/home.png)");
    ui->pbInfo->setStyleSheet("border-image: url(:/new/public/png/public/info.png)");

    this->setStyleSheet("QDialog { border-image: url(:/new/page7/png/page7/main1.png); }");

    ui->pushButton1->setStyleSheet("border-image: url(:/new/page7/png/page7/pb1.png)");
    ui->pushButton3->setStyleSheet("border-image: url(:/new/page7/png/page7/pb2.png)");

    m_timerID = startTimer(250);
}

DlgUpdate::~DlgUpdate()
{
    delete ui;
}
//检测
void DlgUpdate::on_pushButton1_clicked()
{
    ui->pushButton3->setEnabled(false);
    QString strInfo;
    strInfo = "升级检测...";
    ui->tbInfo->setText("");
    ui->tbInfo->append(strInfo);


    QDir dir("./update");
    if(dir.exists())
    {
        //清除文件
        QProcess procCls;
        procCls.start("./sh/cls.sh");
        procCls.waitForFinished();
    }

    //查找u盘
    QString UDiskPath = "";
    foreach (const QStorageInfo &storage, QStorageInfo::mountedVolumes())
    {
        qDebug("->%s", storage.rootPath().toStdString().c_str());
        if (storage.isValid() && storage.isReady())
        {
            if(storage.rootPath().contains("media")){
               UDiskPath = storage.rootPath();
               break;
            }
        }
    }

    if( UDiskPath.isEmpty() )
    {
        qDebug("没有u盘!");
        ui->tbInfo->append("没有u盘!");
        return;
    }else{
        ui->tbInfo->append("u盘已准备...");
    }

    QString strSrcFile = UDiskPath + QDir::separator() + "update.zip";
    QFile file(strSrcFile);
    if( !file.exists())
    {
        qDebug("升级文件不存在!");
        ui->tbInfo->append("升级文件不存在!");
        return;
    }else{
        ui->tbInfo->append("升级文件已准备...");
    }

    //新建文件夹
    QString strDstPath = QCoreApplication::applicationDirPath() + QDir::separator()  + "update";
    QDir dirRoot;
    if(!dirRoot.exists(strDstPath))
    {
        dirRoot.mkpath(strDstPath);
    }

    //复制文件
    QString strDstFile = strDstPath + QDir::separator() + "update.zip";
    bool ok = QFile::copy(strSrcFile, strDstFile);
    if( !ok )
    {
        qDebug("复制文件错误!");
        ui->tbInfo->append("复制文件错误!");
    }else{
        ui->tbInfo->append("复制文件...");
    }

    //解压文件
    ui->tbInfo->append("解压文件...");
    QProcess procUnzip;
    procUnzip.start("./sh/uz.sh");
    procUnzip.waitForFinished();

    QByteArray btArr = procUnzip.readAllStandardOutput();
    strInfo = QString::fromLocal8Bit(btArr);
    ui->tbInfo->append(strInfo);

    //判断主文件是否存在
    QFileInfo fileInfo("./update/update.sh");
    if( !fileInfo.isFile())
    {
        qDebug("无法找到升级文件...");
        ui->tbInfo->append("无法找到升级文件...");
    }else{
        ui->tbInfo->append("升级准备完成...");
        ui->pushButton3->setEnabled(true);
    }
}

void DlgUpdate::on_pushButton2_clicked()
{
    accept();
}

void DlgUpdate::on_pushButton3_clicked()
{
    QString strInfo;
    QProcess procUpdate;
    procUpdate.start("./update/update.sh");
    procUpdate.waitForFinished();
    QByteArray btUpdate = procUpdate.readAllStandardOutput();
    strInfo = QString::fromLocal8Bit(btUpdate);

    ui->tbInfo->append(strInfo);
    qDebug("runCmd---->%s", strInfo.toStdString().c_str());
}

void DlgUpdate::on_pbTitle_clicked()
{
    reject();
}

void DlgUpdate::on_pbHome_clicked()
{
    accept();
}

void DlgUpdate::on_pbInfo_clicked()
{
    //信息
    DlgSysInfo dlg;
    dlg.move((QApplication::desktop()->width() - dlg.width()) / 2, (QApplication::desktop()->height() - dlg.height()) / 2);
    dlg.exec();
}

void DlgUpdate::setTime()
{
    QDate cd = QDate::currentDate();
    QTime ct = QTime::currentTime();
    QString strDate;
    strDate= QString("%1-%2-%3").arg(cd.year()).arg(cd.month(),2,10, QLatin1Char('0')).arg(cd.day(),2,10, QLatin1Char('0'));

    QString strTime = ct.toString();
    ui->labTime->setText(strTime);
    ui->labDate->setText(strDate);
}

void DlgUpdate::timerEvent(QTimerEvent *event)
{
    if( event->timerId() == m_timerID )
    {
        setTime();
    }
}

#include "widget.h"

#include <QApplication>
#include <QtWidgets/qdesktopwidget.h>
#include <QTextCodec>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QMutex>
#include <QDir>
#include "appdata.h"
#include <string>

void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(context);
    static QMutex mutex;
    mutex.lock();

    QString strPath;
    switch(type)
    {
    case QtDebugMsg:
        strPath = QString("./log/Debug");
        break;

    case QtWarningMsg:
        strPath = QString("./log/Warning");
        break;

    case QtCriticalMsg:
        strPath = QString("./log/Critical");
        break;

    case QtFatalMsg:
        strPath = QString("./log/Fatal");
        break;

    case QtInfoMsg:
        strPath = QString("./log/info");
        break;
    }

    QString timestr=QDateTime::currentDateTime().toString("yyyy-MM-dd_HH");
    QString fileName = timestr + ".txt";//假设指定文件夹路径为D盘根目录

    //写入日志
    //检查路径
    QDir dirRoot;
    if(!dirRoot.exists(strPath))
    {
        dirRoot.mkpath(strPath);
    }

    //检查文件
    QFile file;
    file.setFileName(strPath + QDir::separator() + fileName);
    if( !file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        qDebug("file cannot create!");
        return;
    }

    std::string strLog;
    strLog += msg.toStdString();

    file.write(strLog.c_str(), strLog.length());
    file.write("\r\n");
    file.flush();
    file.close();
    mutex.unlock();
}

int main(int argc, char *argv[])
{
    //QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    //QTextCodec::setCodecForLocale(codec);

    QApplication a(argc, argv);
#ifndef WIN32
    QApplication::setOverrideCursor(Qt::BlankCursor);
    qInstallMessageHandler(outputMessage);
#endif

    Widget w;
    w.move((a.desktop()->width() - w.width()) / 2, (a.desktop()->height() - w.height()) / 2);
    w.show();
    return a.exec();
}

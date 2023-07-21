#include "threadreadinfo.h"
#include <QFile>
#include <QTextStream>

ThreadReadInfo::ThreadReadInfo()
{

}

QString ThreadReadInfo::readFileToString(QString strName)
{
    QString strResult;
    QString strPath = "./数据/" + m_strPath + "/" + strName;
    QFile file(strPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug("***************read file error************* %s", strPath.toStdString().c_str());
        return nullptr;
    }
    while(!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString str(line);
        strResult.append(str);
    }
    file.close();

    return strResult;
}

void ThreadReadInfo::run()
{
    QString strDisp1,strDisp2,strDisp3,strDisp4,strDisp5,strDisp6,strDisp7;
    strDisp1 = readFileToString("信噪比数据.txt");
    strDisp2 = readFileToString("结果数据.txt");
    strDisp3 = readFileToString("预热背景干涉图.txt");
    strDisp4 = readFileToString("背景光谱.txt");
    strDisp5 = readFileToString("样品干涉图.txt");
    strDisp6 = readFileToString("样品光谱.txt");
    strDisp7 = readFileToString("吸光度谱.txt");

    emit sigReadTxt( strDisp1, strDisp2,strDisp3, strDisp4,strDisp5, strDisp6,strDisp7);

    /*****************************************************************************************/
}

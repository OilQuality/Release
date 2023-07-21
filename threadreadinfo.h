#ifndef THREADREADINFO_H
#define THREADREADINFO_H

#include <QObject>
#include <QThread>

class ThreadReadInfo: public QThread
{
    Q_OBJECT
public:
    ThreadReadInfo();

    void run();

signals:
    void sigReadTxt(QString,QString,QString,QString,QString,QString,QString);

public:
    QString m_strPath;

private:
    QString readFileToString(QString strName);
};

#endif // THREADREADINFO_H

#ifndef DLGSYSINFO_H
#define DLGSYSINFO_H

#include <QDialog>

namespace Ui {
class DlgSysInfo;
}

class DlgSysInfo : public QDialog
{
    Q_OBJECT

public:
    explicit DlgSysInfo(QWidget *parent = nullptr);
    ~DlgSysInfo();

private slots:
    void on_pbTitle_clicked();

private:
    Ui::DlgSysInfo *ui;
    int m_timerID;

    void initSysInfo();
    void InitInfo();
    void timerEvent(QTimerEvent *);
};

#endif // DLGSYSINFO_H

#ifndef DLGCLEAN_H
#define DLGCLEAN_H

#include <QDialog>

namespace Ui {
class DlgClean;
}

class DlgClean : public QDialog
{
    Q_OBJECT

public:
    explicit DlgClean(QWidget *parent = nullptr);
    ~DlgClean();

private slots:
    void on_pbTitle_clicked();
    void on_pbHome_clicked();
    void on_pbWash_clicked();
    void on_pbClean_clicked();
    void on_pbUp_clicked();
    void on_pbDown_clicked();
    void on_pbUp2_clicked();
    void on_pbDown2_clicked();
    void on_pbStop_clicked();
    void on_pbInfo_clicked();

private:
    Ui::DlgClean *ui;

    int m_iCleanTimes;
    int m_iWashTimes;

    int m_iStatus;//状态 0:空闲 1: 清洗 2: 排空
private slots:
    void OnWashTaskMsg(QString);
    void OnWashTaskDone();


private:
    int m_timerID;

    int m_iTimeCur;
    int m_iTimeCnt;
    void setTime();

    // QObject interface
protected:
    void timerEvent(QTimerEvent *event);
};

#endif // DLGCLEAN_H

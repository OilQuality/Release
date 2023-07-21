#ifndef DLGSYSSETTING_H
#define DLGSYSSETTING_H

#include <QDialog>

namespace Ui {
class DlgSysSetting;
}

class DlgSysSetting : public QDialog
{
    Q_OBJECT

public:
    explicit DlgSysSetting(QWidget *parent = nullptr);
    ~DlgSysSetting();

private slots:
    void on_pbTitle_clicked();
    void on_pbHome_clicked();
    void on_pbInfo_clicked();
    void on_pb1_clicked();
    void on_pb2_clicked();
    void on_pb3_clicked();
    void on_pb4_clicked();
    void on_pb5_clicked();
    void on_pb6_clicked();
    void on_pb7_clicked();
    void on_pb8_clicked();

private:
    Ui::DlgSysSetting *ui;

private:
    int m_timerID;//设置显示时间
    void setTime();

    // QObject interface
protected:
    void timerEvent(QTimerEvent *event);
};

#endif // DLGSYSSETTING_H

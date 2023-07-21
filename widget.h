#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include "threadcheckstate.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void initSysInfo();
private slots:


    void OnMachineStatus(QString);
private:
    Ui::Widget *ui;
/*
    QPushButton *m_pBtn1;
    QPushButton *m_pBtn2;
    QPushButton *m_pBtn3;
    QPushButton *m_pBtn4;
    QPushButton *m_pBtn5;
    QPushButton *m_pBtn6;
    QPushButton *m_pBtn7;
    QPushButton *m_pBtn8;
*/
private:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);

    int m_timerID;//设置显示时间
    int m_timerCheck;
    int m_timerQuery;
    int m_timerTask;//延迟显示任务时间
    ThreadCheckState *m_pthreadCheck;

private slots:
    void OnCheckDone();
    void OnInitDone();//初始化完成
    void OnInitMsg(QString);//初始化中的消息
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pbInfo_clicked();
    //void on_pbTest_clicked();
    void on_pushButton_clicked();

    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event);
};
#endif // WIDGET_H

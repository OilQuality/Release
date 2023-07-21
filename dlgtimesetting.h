#ifndef DLGTIMESETTING_H
#define DLGTIMESETTING_H

#include <QDialog>

namespace Ui {
class DlgTimeSetting;
}

class DlgTimeSetting : public QDialog
{
    Q_OBJECT

public:
    explicit DlgTimeSetting(QWidget *parent = nullptr);
    ~DlgTimeSetting();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_13_clicked();

private:
    Ui::DlgTimeSetting *ui;

private:
    int m_timerID;

    // QWidget interface
protected:
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *event);
};

#endif // DLGTIMESETTING_H

#ifndef DLGDEBUG_H
#define DLGDEBUG_H

#include <QDialog>

namespace Ui {
class DlgDebug;
}

class DlgDebug : public QDialog
{
    Q_OBJECT

public:
    explicit DlgDebug(QWidget *parent = nullptr);
    ~DlgDebug();

private slots:
    void OnMsg(QString);
    void OnRet(QByteArray,int);

    void on_pushButton_clicked();
    void on_pB11_clicked();
    void on_pB32_2_clicked();
    void on_pB32_3_clicked();
    void on_pB12_clicked();
    void on_pB21_clicked();
    void on_pB22_clicked();
    void on_pB31_clicked();
    void on_pB32_clicked();
    void on_pB41_clicked();
    void on_pB42_clicked();
    void on_pB43_clicked();
    void on_pB44_clicked();
    void on_pB51_clicked();
    void on_pB61_clicked();
    void on_pB62_clicked();
    void on_pB63_clicked();
    void on_pB64_clicked();
    void on_pB65_clicked();
    void on_pB90_clicked();
    void on_pB91_clicked();
    void on_pB92_clicked();
    void on_pB66_clicked();
    void on_pB67_clicked();
    void on_pB68_clicked();

    void on_pB68_1_clicked();

    void on_pB68_2_clicked();

private:
    Ui::DlgDebug *ui;

private:
    int m_timerQuery;
    QByteArray m_ba;

    // QObject interface
protected:
    void timerEvent(QTimerEvent *event);
};

#endif // DLGDEBUG_H

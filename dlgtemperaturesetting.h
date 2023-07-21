#ifndef DLGTEMPERATURESETTING_H
#define DLGTEMPERATURESETTING_H

#include <QDialog>

namespace Ui {
class DlgTemperatureSetting;
}

class DlgTemperatureSetting : public QDialog
{
    Q_OBJECT

public:
    explicit DlgTemperatureSetting(QWidget *parent = nullptr);
    ~DlgTemperatureSetting();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void OnMeasureTemp(double, double, double);

    void on_pbTitle_clicked();

    void on_pbHome_clicked();

    void on_pbInfo_clicked();

private:
    Ui::DlgTemperatureSetting *ui;

private:
    int m_timerID;
    int m_timerDataID;
    void setTime();
    // QWidget interface
protected:
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *event);
};

#endif // DLGTEMPERATURESETTING_H

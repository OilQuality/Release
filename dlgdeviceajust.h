#ifndef DLGDEVICEAJUST_H
#define DLGDEVICEAJUST_H

#include <QDialog>

namespace Ui {
class DlgDeviceAjust;
}

class DlgDeviceAjust : public QDialog
{
    Q_OBJECT

public:
    explicit DlgDeviceAjust(QWidget *parent = nullptr);
    ~DlgDeviceAjust();

private slots:
    void on_pb2_clicked();
    void on_pbTitle_clicked();
    void on_pbHome_clicked();
    void on_pbInfo_clicked();

private:
    Ui::DlgDeviceAjust *ui;

private:
    int m_timerID;//设置显示时间
    void setTime();

    // QObject interface
protected:
    void timerEvent(QTimerEvent *event);
};

#endif // DLGDEVICEAJUST_H

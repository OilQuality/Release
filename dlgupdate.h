#ifndef DLGUPDATE_H
#define DLGUPDATE_H

#include <QDialog>

namespace Ui {
class DlgUpdate;
}

class DlgUpdate : public QDialog
{
    Q_OBJECT

public:
    explicit DlgUpdate(QWidget *parent = nullptr);
    ~DlgUpdate();

private slots:
    void on_pushButton1_clicked();
    void on_pushButton2_clicked();
    void on_pushButton3_clicked();
    void on_pbTitle_clicked();
    void on_pbHome_clicked();
    void on_pbInfo_clicked();

private:
    Ui::DlgUpdate *ui;

private:
    int m_timerID;
    void setTime();

    // QObject interface
protected:
    void timerEvent(QTimerEvent *event);
};

#endif // DLGUPDATE_H

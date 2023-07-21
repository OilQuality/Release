#ifndef DLGWASH_H
#define DLGWASH_H

#include <QDialog>

namespace Ui {
class DlgWash;
}

class DlgWash : public QDialog
{
    Q_OBJECT

public:
    explicit DlgWash(QWidget *parent = nullptr);
    ~DlgWash();

private:
    Ui::DlgWash *ui;

private:
    void paintEvent(QPaintEvent *);

private slots:
    //void OnBtn1Clicked();
    //void OnBtn2Clicked();
    void OnBtn3Clicked();
    void OnBtn4Clicked();
    void OnBtn5Clicked();

    void OnWashTaskMsg(QString);
    void OnWashTaskDone();

    void on_pbWash_clicked();
    void on_pbEmpty_clicked();

private:
    QPushButton *m_pBtn1;//清洗
    QPushButton *m_pBtn2;//排空

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *event);
};

#endif // DLGWASH_H

#ifndef BTNSWICH_H
#define BTNSWICH_H

#include <QWidget>

class btnSwich : public QWidget
{
    Q_OBJECT
public:
    explicit btnSwich(QWidget *parent = nullptr);

signals:


    // QWidget interface
private:
    bool m_bState;

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
public:
    void setState(bool);
    bool getState();
};

#endif // BTNSWICH_H

#ifndef WNDPROGRESS_H
#define WNDPROGRESS_H

#include <QWidget>

class wndProgress : public QWidget
{
    Q_OBJECT
public:
    explicit wndProgress(QWidget *parent = nullptr);

signals:

public:
    void setProgress(int i);

private:
    int m_nPercent;
    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // WNDPROGRESS_H

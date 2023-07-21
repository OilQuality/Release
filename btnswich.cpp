#include "btnswich.h"

#include <QPainter>

btnSwich::btnSwich(QWidget *parent) : QWidget(parent)
{
    m_bState = true;
}

void btnSwich::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    if( m_bState )
    {
        painter.drawPixmap(rect(), QPixmap(":/new/public/png/public/p2sw1.png"), QRect());
    }else{
        painter.drawPixmap(rect(), QPixmap(":/new/public/png/public/p2sw2.png"), QRect());
    }
}

void btnSwich::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_bState = !m_bState;
    update();
}

void btnSwich::setState(bool bState)
{
    m_bState = bState;
    update();
}

bool btnSwich::getState()
{
    return m_bState;
}

#include "wndprogress.h"

#include <QPainter>
#include <QPainterPath>

wndProgress::wndProgress(QWidget *parent) : QWidget(parent)
{
    m_nPercent = 0;
}

void wndProgress::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    int nWidth = this->size().width();
    int nHeight = this->size().height();

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    QFont wordFont = QFont(QString("黑体"), 14);
    painter.setFont(wordFont);

    painter.setClipping(true);
    QPainterPath path; // 能画上的区域
    path.addRoundedRect(rect(), 20, 20);
    path.setFillRule(Qt::WindingFill); // 多块区域组合填充模式
    painter.setClipPath(path);

    painter.setPen(QColor(0,0,0));
    QRect rec(0,0,nWidth - 1, nHeight - 1);
    painter.fillRect(0,0,nWidth,nHeight,QColor(220,220,220));

    int nPtWidth = (nWidth * m_nPercent) / 100;
    painter.fillRect(0,0,nPtWidth,nHeight,QColor(0,255,0));

    painter.drawText( 0, 0, nWidth, nHeight,Qt::AlignCenter, QString("%1%").arg(m_nPercent));
}

void wndProgress::setProgress(int i)
{
    m_nPercent = i;
    update();
}

#include "xchart.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDir>
#include <QTime>

XChart::XChart(QWidget *parent) : QWidget(parent)
{
    m_xPos = -1;
    m_yPos = -1;

    m_igapLeft = 50;
    m_igapRight = 15;//右边距
    m_igapTop = 32;
    m_igapBottom = 48;//底边距离

    m_strTitle = "标题";

    m_MinData = 0;
    m_MaxData = 0;

    m_bTag = false;
    m_iXRulerMin = 0;
    m_iXRulerMax = 0;

    m_bSpec = false;
    m_iSpecID = 0;

    //m_updown = 1;
    //this->setMouseTracking(true);
}

void XChart::setSpec(bool bspec, int id)
{
    m_bSpec = bspec;
    m_iSpecID = id;
}

void XChart::setXRuler(int min, int max)
{
    if( min < max)
    {
        m_iXRulerMin = min;
        m_iXRulerMax = max;
    }else{
        m_iXRulerMin = max;
        m_iXRulerMax = min;
    }
}

void XChart::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    if( m_bSpec)
    {
        if( m_iSpecID == 1)
        {
           DrawSpec1();
        }else if( m_iSpecID == 2)
        {
            DrawSpec2();
        }
    }else{
        DrawNormal();
    }
}

void XChart::mousePressEvent(QMouseEvent *et)
{
    return QWidget::mousePressEvent(et);
    //qDebug("**** mousePressEvent **** %d:%d",et->x(), et->globalX());
    m_xPos = et->x();
    m_yPos = et->y();

    update();
    return QWidget::mousePressEvent(et);
}

void XChart::mouseMoveEvent(QMouseEvent *et)
{
    Q_UNUSED(et);
    //qDebug("**** mouseMoveEvent ****");

}

void XChart::mouseReleaseEvent(QMouseEvent *et)
{
    Q_UNUSED(et);
    //qDebug("**** mouseReleaseEvent ****");
}
/*
void XChart::setUpDown(int i)
{
    //m_updown = i;
    update();
}*/

void XChart::setTag(bool bTag)
{
    m_bTag = bTag;
}

void XChart::setTitle(QString strTitle)
{
    m_strTitle = strTitle;
}

void XChart::addData(double &d)
{
    if( m_dVecData.size() == 0 )
    {
        m_MinData = d;
        m_MaxData = d;
    }

    if( d < m_MinData )
    {
        m_MinData = d;
    }else if(d > m_MaxData)
    {
        m_MaxData = d;
    }
    m_dVecData.append(d);
}

void XChart::clearData()
{
    setTitle("");
    //m_iVecData.clear();
    m_dVecData.clear();

    m_MinData = 0;
    m_MaxData = 0;

    m_iXRulerMin = 0;
    m_iXRulerMax = 0;

    m_bSpec = false;
    m_iSpecID = 0;
}

void XChart::DrawSpec1()
{
    char szBuff[200] = { 0 };
    int nWidth = this->size().width();
    int nHeight = this->size().height();

    int nDrawWidth = nWidth - m_igapRight - m_igapLeft;
    int nDrawHeight = nHeight - m_igapBottom - m_igapTop;

    QString strTemp;
    QPainter painter(this);
    //painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(QColor(0,0,0));//painter.setPen(QColor("#FF000000"));//字体颜色
    //painter.setBrush(brush);    //设置关联画刷
    //painter在设备的窗口上绘制边框
    QRect rec(0,0,nWidth - 1, nHeight - 1);
    painter.drawRect(rec);

    QRect recCoord( m_igapLeft, m_igapTop, nDrawWidth, nDrawHeight);
    painter.drawRect(recCoord);
    if( m_xPos > 0 )
    {
        painter.drawLine(m_xPos, 0, m_xPos, nHeight - 1);
    }

    //
    double dbGap = 0;

    //水平位置划度
    dbGap = (double)nDrawWidth / 10;
    for(int i = 0; i < 11; i++)
    {
        painter.drawLine( m_igapLeft + dbGap * i, nHeight - m_igapBottom + 4, m_igapLeft + dbGap * i,nHeight - m_igapBottom -4);
    }
    dbGap = (double)nDrawWidth / 50;
    for(int i = 0; i < 50; i++)
    {
        painter.drawLine(m_igapLeft + dbGap * i, nHeight - m_igapBottom + 2, m_igapLeft + dbGap * i,nHeight - m_igapBottom -2);
    }

    dbGap = (double)nDrawWidth / 10;
    int dwRulerWidth = 0;
    dwRulerWidth = (m_iXRulerMax - m_iXRulerMin)/10;
    for(int i = 0; i < 11; i++)
    {
        qDebug("ruler: %d w:%d gap:%d", (int)(m_igapLeft + dbGap * i - 25), nDrawWidth, (int)dbGap );
        if( i == 0 )
        {
            painter.drawText(m_igapLeft + dbGap * i - 6,nHeight - m_igapBottom + 4, 100, 20,Qt::AlignLeft, QString("%1").arg(dwRulerWidth * i + m_iXRulerMin));//位置和内容
            /*if( m_updown == 1)
            {
                painter.drawText(m_igapLeft + dbGap * i - 6,nHeight - m_igapBottom + 4, 100, 20,Qt::AlignLeft, QString("%1").arg(dwRulerWidth * i + m_iXRulerMin));//位置和内容
            }else if( m_updown == 2)
            {
                painter.drawText(m_igapLeft + dbGap * i - 4,nHeight - m_igapBottom + 4, 100, 20,Qt::AlignLeft, QString("%1").arg(dwRulerWidth * i + m_iXRulerMin));//位置和内容
            }else{
                painter.drawText(m_igapLeft + dbGap * i - 2,nHeight - m_igapBottom + 4, 100, 20,Qt::AlignLeft, QString("%1").arg(dwRulerWidth * i + m_iXRulerMin));//位置和内容
            }*/
        }else if( i == 10 )
        {
            painter.drawText(m_igapLeft + dbGap * i - 25,nHeight - m_igapBottom + 4, 100, 20,Qt::AlignLeft, QString("%1").arg(dwRulerWidth * i + m_iXRulerMin));//位置和内容
        }else{
            painter.drawText(m_igapLeft + dbGap * i - 8,nHeight - m_igapBottom + 4, 100, 20,Qt::AlignLeft, QString("%1").arg(dwRulerWidth * i + m_iXRulerMin));//位置和内容
        }
    }

    sprintf(szBuff, "%.5f", m_MinData );
    painter.drawText( 4, m_igapTop + nDrawHeight - 10, m_igapLeft - 6, 25,Qt::AlignRight, szBuff);
    sprintf(szBuff, "%.5f", m_MaxData );
    painter.drawText( 4, m_igapTop, m_igapLeft - 6, 25,Qt::AlignRight, szBuff);


    QFont font; // 需要设置的字体
    font.resolve(QFont::AllPropertiesResolved);
    painter.setFont(font);//设置字体
    if( !m_strTitle.isNull() && !m_strTitle.isEmpty() )
    {
        painter.drawText(0,0,nWidth, m_igapTop,Qt::AlignCenter, m_strTitle);//位置和内容
    }

    //最大最小值
    sprintf(szBuff,"最大值:%f", m_MaxData);
    painter.drawText(m_igapLeft + 3, m_igapTop + 3,  nDrawWidth - 6, 20,Qt::AlignRight, szBuff);
    sprintf(szBuff,"最小值:%f", m_MinData);
    painter.drawText(m_igapLeft + 3, m_igapTop + 20,  nDrawWidth - 6, 20,Qt::AlignRight, szBuff);

    double dMaxData = 100.0f /( m_MaxData - m_MinData );

    //绘制数据
    int x1,x2,y1,y2;
    painter.setPen(QColor(99,125,166));
    if( m_dVecData.size() > 0 )
    {
        int nCnt = m_dVecData.size();
        for( int i = 0; i < nCnt - 1; i++ )
        {
            x1 = i*nDrawWidth / nCnt;
            x2 = (i + 1) * nDrawWidth / nCnt;
            y1 = ( (m_dVecData.at(i) - m_MinData ) * dMaxData) * nDrawHeight / 100.0f;
            y2 = (( m_dVecData.at(i + 1) - m_MinData ) * dMaxData ) * nDrawHeight / 100.0f;
            painter.setPen(QColor(99,125,166));
            painter.drawLine( m_igapLeft + x1, m_igapTop + nDrawHeight - y1, m_igapLeft + x2,m_igapTop + nDrawHeight - y2);
        }
    }
}

void XChart::DrawSpec2()
{
}

void XChart::DrawNormal()
{
    char szBuff[200] = { 0 };
    int nWidth = this->size().width();
    int nHeight = this->size().height();

    int nDrawWidth = nWidth - m_igapRight - m_igapLeft;
    int nDrawHeight = nHeight - m_igapBottom - m_igapTop;

    QString strTemp;
    QPainter painter(this);
    //painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(QColor(0,0,0));//painter.setPen(QColor("#FF000000"));//字体颜色
    //painter.setBrush(brush);    //设置关联画刷
    //painter在设备的窗口上绘制边框
    QRect rec(0,0,nWidth - 1, nHeight - 1);
    painter.drawRect(rec);

    QRect recCoord( m_igapLeft, m_igapTop, nDrawWidth, nDrawHeight);
    painter.drawRect(recCoord);
    if( m_xPos > 0 )
    {
        painter.drawLine(m_xPos, 0, m_xPos, nHeight - 1);
    }

    //
    double dbGap = 0;

    //水平位置划度
    dbGap = (double)nDrawWidth / 10;
    for(int i = 0; i < 11; i++)
    {
        painter.drawLine( m_igapLeft + dbGap * i, nHeight - m_igapBottom + 4, m_igapLeft + dbGap * i,nHeight - m_igapBottom -4);
    }
    dbGap = (double)nDrawWidth / 20;
    //sprintf(szBuff,"gap:%d , width:%d", (int)dbGap, nDrawWidth);
    //logt( "hex", szBuff);
    for(int i = 0; i < 20; i++)
    {
        sprintf(szBuff,"i:%d x:%d", i, (int)(m_igapLeft + dbGap * i));
        //logt( "hex", szBuff);
        //painter.drawLine(m_igapLeft + dbGap * i, nHeight - m_igapBottom + 2, m_igapLeft + dbGap * i,nHeight - m_igapBottom -2);
    }

    QFont font; // 需要设置的字体
    font.resolve(QFont::AllPropertiesResolved);
    painter.setFont(font);//设置字体
    //char szDbg[100] = { 0 };
    //sprintf(szDbg, "数据点: %d", m_dVecData.size());
    //m_strTitle = szDbg;
    if( !m_strTitle.isNull() && !m_strTitle.isEmpty() )
    {
        painter.drawText(0,0,nWidth, m_igapTop,Qt::AlignCenter, m_strTitle);//位置和内容
    }

    //最大最小值
    sprintf(szBuff,"最大值:%8d", (int)m_MaxData);
    painter.drawText(m_igapLeft + 3, m_igapTop + 3,  nDrawWidth - 6, 20,Qt::AlignRight, szBuff);
    sprintf(szBuff,"最小值:%8d", (int)m_MinData);
    painter.drawText(m_igapLeft + 3, m_igapTop + 20,  nDrawWidth - 6, 20,Qt::AlignRight, szBuff);
    //painter.drawRect(m_igapLeft + 3, m_igapTop + 3, nDrawWidth - 6, 25);
    //painter.drawRect(m_igapLeft + 3, m_igapTop + 30, nDrawWidth - 6, 25);
    //水平数字划度
    dbGap = (double)nDrawWidth / 10;
    int dwRulerWidth = 0;
    if( m_iXRulerMax > 0 )
    {
        dwRulerWidth = (m_iXRulerMax - m_iXRulerMin)/10;
    }else if( m_dVecData.size() > 0 )
    {
        dwRulerWidth = m_dVecData.size() / 10;
    }else{
        dwRulerWidth = 1;
    }

    for(int i = 0; i < 11; i++)
    {
        if( i == 0 )
        {

            painter.drawText(m_igapLeft + dbGap * i - 6,nHeight - m_igapBottom + 4, 100, 20,Qt::AlignLeft, QString("%1").arg(dwRulerWidth * i + m_iXRulerMin));//位置和内容
            /*if( m_updown == 1)
            {
                painter.drawText(m_igapLeft + dbGap * i - 6,nHeight - m_igapBottom + 4, 100, 20,Qt::AlignLeft, QString("%1").arg(dwRulerWidth * i + m_iXRulerMin));//位置和内容
            }else if( m_updown == 2)
            {
                painter.drawText(m_igapLeft + dbGap * i - 4 ,nHeight - m_igapBottom + 4, 100, 20,Qt::AlignLeft, QString("%1").arg(dwRulerWidth * i + m_iXRulerMin));//位置和内容
            }else{
                painter.drawText(m_igapLeft + dbGap * i - 2 ,nHeight - m_igapBottom + 4, 100, 20,Qt::AlignLeft, QString("%1").arg(dwRulerWidth * i + m_iXRulerMin));//位置和内容
            }*/
        }else if( i == 10 )
        {
            painter.drawText(m_igapLeft + dbGap * i - 25,nHeight - m_igapBottom + 4, 100, 20,Qt::AlignLeft, QString("%1").arg(dwRulerWidth * i + m_iXRulerMin));//位置和内容
        }else{
            painter.drawText(m_igapLeft + dbGap * i - 8,nHeight - m_igapBottom + 4, 100, 20,Qt::AlignLeft, QString("%1").arg(dwRulerWidth * i + m_iXRulerMin));//位置和内容
        }

        //painter.drawLine( m_igapLeft + dbGap * i, nHeight - m_igapBottom + 4, m_igapLeft + dbGap * i,nHeight - m_igapBottom -4);
    }
    //垂直数字划度
    //qDebug("min:%f; max:%f", m_MinData, m_MaxData );
    //painter.drawRect( 2, m_igapTop + 10,  m_igapLeft - 6, 100);

    //1. 计算刻度值
    //2. 绘制0轴
    if( m_MinData < 0 )
    {
        m_ZeroData = m_MinData * (-1);
    }else{
        m_ZeroData = 0;
    }

    double x1,x2,y1,y2;
    double dMaxData = ( m_MaxData + m_ZeroData ) * 1.1; //最大值

    //绘制0轴
    if( m_ZeroData > 0 )
    {
        y1 = m_ZeroData * nDrawHeight / (dMaxData) ;
        painter.drawLine( m_igapLeft, m_igapTop + nDrawHeight - y1, m_igapLeft + nDrawWidth, m_igapTop + nDrawHeight - y1);
        painter.drawText(m_igapLeft - 15,m_igapTop + nDrawHeight - y1 -8, 15, m_igapTop,Qt::AlignLeft, "0");
    }
    //绘制垂直位置划度, nDrawHeight分成50个小刻度
    double dPer50 = nDrawHeight / 50;//每个刻度像素数
    y1 = m_ZeroData * nDrawHeight / (dMaxData);//0轴到底轴有多少像素
    int nMarkDown = y1 / dPer50 + 1;//0轴到底边有多少刻度
    for(int i = 0; i < nMarkDown; i++)//y轴下半部分
    {
        y2 = y1 - dPer50 * i;
        if( i%5 == 0 )
        {
            painter.drawLine(m_igapLeft - 4, m_igapTop + nDrawHeight - y2, m_igapLeft + 4, m_igapTop + nDrawHeight - y2);

            if( i != 0)
            {
                double  nPer = dMaxData * i / 50;
                double nPerkey = 0;
                if( nPer > 1000000)
                {
                    nPerkey = nPer / 1000000;
                    sprintf( szBuff, "-%.1fM", nPerkey);
                }else if( nPer > 1000 )
                {
                    nPerkey = nPer/ 1000;
                    sprintf( szBuff, "-%.1fK", nPerkey);
                }else{
                    nPerkey = nPer;
                    sprintf( szBuff, "-%.1f", nPerkey);
                }
                //painter.drawRect( 2, m_igapTop + nDrawHeight - y2 -10,  m_igapLeft - 6, 20);
                painter.drawText( 2, m_igapTop + nDrawHeight - y2 -10, m_igapLeft - 6, 20,Qt::AlignRight, szBuff);
            }
        }else{
            painter.drawLine(m_igapLeft - 2, m_igapTop + nDrawHeight - y2, m_igapLeft + 2, m_igapTop + nDrawHeight - y2);
        }
    }

    y2 = nDrawHeight - y1;
    nMarkDown = y2 / dPer50 + 1;
    for(int i = 0; i < nMarkDown; i++)//y轴上半部分
    {
        y2 = y1 + dPer50 * i;
        if( i%5 == 0 )
        {
            painter.drawLine(m_igapLeft - 4, m_igapTop + nDrawHeight - y2, m_igapLeft + 4, m_igapTop + nDrawHeight - y2);

            if( i != 0)
            {
                double  nPer = dMaxData * i / 50;
                double nPerkey = 0;
                if( nPer > 1000000)
                {
                    nPerkey = nPer / 1000000;
                    sprintf( szBuff, "%.1fM", nPerkey);
                }else if( nPer > 1000 )
                {
                    nPerkey = nPer/ 1000;
                    sprintf( szBuff, "%.1fK", nPerkey);
                }else{
                    nPerkey = nPer;
                    sprintf( szBuff, "%.1f", nPerkey);
                }
                //painter.drawRect( 2, m_igapTop + nDrawHeight - y2 -10,  m_igapLeft - 6, 20);
                painter.drawText( 2, m_igapTop + nDrawHeight - y2 -10, m_igapLeft - 6, 20,Qt::AlignRight, szBuff);
            }
        }else{
            painter.drawLine(m_igapLeft - 2, m_igapTop + nDrawHeight - y2, m_igapLeft + 2, m_igapTop + nDrawHeight - y2);
        }
    }

    //绘制数据
    painter.setPen(QColor(99,125,166));
    if(m_bTag)
    {
        if( m_dVecData.size() > 0 )
        {
            int nCnt = m_dVecData.size();
            //sprintf(szBuff,"nCnt:%d , width:%d",  nCnt, nDrawWidth);
            //logt( "hex", szBuff);
            for( int i = 0; i < nCnt - 1; i++ )
            {
                x1 = (i)*nDrawWidth / (nCnt - 1);
                x2 = (i + 1) * nDrawWidth / (nCnt - 1);
                y1 = ( m_dVecData.at(i) + m_ZeroData ) * nDrawHeight / ( dMaxData);
                y2 = ( m_dVecData.at(i + 1) + m_ZeroData ) * nDrawHeight / (dMaxData);
                painter.setPen(QColor(99,125,166));
                painter.drawLine( m_igapLeft + x1, m_igapTop + nDrawHeight - y1, m_igapLeft + x2,m_igapTop + nDrawHeight - y2);

                painter.setPen(QColor(255,0,0));
                painter.drawEllipse(m_igapLeft + x1,m_igapTop + nDrawHeight - y1,2,2);

                //sprintf(szBuff,"c-- i:%d x1:%d x2:%d", i, (int)x1, (int)x2);
                //logt( "hex", szBuff);
            }
        }
    }else{
        if( m_dVecData.size() > 0 )
        {
            int nCnt = m_dVecData.size();
            for( int i = 0; i < nCnt - 1; i++ )
            {
                x1 = i*nDrawWidth / (nCnt - 1);
                x2 = (i + 1) * nDrawWidth / (nCnt - 1);
                y1 = ( m_dVecData.at(i) + m_ZeroData ) * nDrawHeight / ( dMaxData);
                y2 = ( m_dVecData.at(i + 1) + m_ZeroData ) * nDrawHeight / (dMaxData);
                painter.setPen(QColor(99,125,166));
                painter.drawLine( m_igapLeft + x1, m_igapTop + nDrawHeight - y1, m_igapLeft + x2,m_igapTop + nDrawHeight - y2);
            }
        }
    }
}

void XChart::logt(string strFile, string msg)
{
    QString fileName = strFile.c_str();
    fileName.append(".txt");

    QString strPath = "./log";

    //写入日志
    //检查路径
    QDir dirRoot;
    if(!dirRoot.exists(strPath))
    {
        dirRoot.mkpath(strPath);
    }

    //检查文件
    QFile file;
    file.setFileName(strPath + QDir::separator() + fileName);
    if( !file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        qDebug("file cannot create!");
        return;
    }

    QString strLog;
    strLog = QString("%1").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"));

    file.write(strLog.toStdString().c_str(), strLog.length());
    file.write(msg.c_str(),msg.length());
    file.write("\r\n");
    file.flush();
    file.close();
}

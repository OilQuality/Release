#ifndef XCHART_H
#define XCHART_H

#include <QObject>
#include <QWidget>
#include <QVector>
#include <string>
using namespace std;
class XChart : public QWidget
{
    Q_OBJECT
public:
    explicit XChart(QWidget *parent = nullptr);

private:
    void DrawSpec1();
    void DrawSpec2();
    void DrawNormal();
    void logt(string strFile, string msg);
signals:

private:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    int m_xPos;
    int m_yPos;

    int m_igapLeft;
    int m_igapRight;
    int m_igapTop;
    int m_igapBottom;

    //int m_updown;


    bool m_bTag;
    QString m_strTitle;
    //QVector<int> m_iVecData;
    QVector<double> m_dVecData;
public:
    //void setUpDown(int);
    void setTag(bool);
    void setTitle(QString strTitle);
    void addData(double &d);
    //void addData(int &i);
    void clearData();
    void setSpec(bool, int);
    void setXRuler(int min, int max);
private:
    bool m_bSpec;
    int  m_iSpecID;
    bool m_bDataReal;
    double m_MinData;
    double m_MaxData;
    double m_ZeroData;

    //int m_iRulerMin;
   // int m_iRulerMax;
    int m_iXRulerMin;
    int m_iXRulerMax;
};

#endif // XCHART_H

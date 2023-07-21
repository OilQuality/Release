#ifndef INC_H
#define INC_H

#include <QString>

struct ST_MEASUREINFO
{
    QString m_strOilName;//样品名称
    QString m_strOilType;//样品类型
    QString m_strPoolType;//样品池
    //QString m_strOilCnt;//样品数量
    int  m_iCleanTimes;//清洗次数
    int  m_iScanTimes;//进样次数
    int  m_iCollectTimes;//采集次数
    //bool m_bDilution;//稀释

    //int  m_iPoolType;//样品池类型  0:ref 1:35 2:100 3:35&100
};

#endif // INC_H

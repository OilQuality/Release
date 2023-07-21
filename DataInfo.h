#ifndef DATAINFO_H
#define DATAINFO_H
#include <QDateTime>
#include <string>

struct MirrorMeaInfo{
    int xPos;
    int yPos;
    int nMax;
};

struct MachineInfo{
    int iLightPower;//光强
    double iTempMdj;//密度计
    double iTempJyq;//进样器
    double iTempYpc;//样品池

    double iTempSetMdj;
    double iTempSetJyq;
    double iTempSetYpc;

    double dMdjOriginal;//原始
    double dMdj;
    double dMdjTemp;
    QDateTime dtMdj;//密度计更新时间
    std::string strIP;
};
#endif // DATAINFO_H

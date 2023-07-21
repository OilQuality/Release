#ifndef CMDMANAGER_H
#define CMDMANAGER_H
#include <QString>

#define CMD_TYPE_INIT_COLL            100
#define CMD_TYPE_MEASURE              101


#define CMD_TYPE_MEASURE_DONE         201
#define CMD_TYPE_QUERY_SAMPLEPOOL     304
#define CMD_TYPE_QUERY_SAMPLEPOS      305
#define CMD_TYPE_STABLE_TEMPERATURE   306
//样品池位置
#define CMD_TYPE_QUERY_SPPOS      401
//动镜电机位置-复位
#define CMD_TYPE_QUERY_MotorRST   402
//动镜电机位置-测量
#define CMD_TYPE_QUERY_MotorPOS   403
//测量-数据开始采集, 采集结束判断，参池比数据,目标数据
#define CMD_TYPE_COLLECT          501
#define CMD_TYPE_COLL_CHECK       502
#define CMD_TYPE_COLL_DATA        503

#define CMD_TYPE_SLEEP            601
#define CMD_TYPE_SLEEP2           602

//协调密度计温度
#define CMD_TYPE_MDJSET           701

class CmdManager
{
public:
    CmdManager();

public:
    char * m_pCmd;
    int m_nCmdLen;
    int m_nCmdType;
    int m_nCmdOpt;
    QString m_strMsg;
};

#endif // CMDMANAGER_H

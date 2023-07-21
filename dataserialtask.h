#ifndef DATASERIALTASK_H
#define DATASERIALTASK_H

#include <QString>


#define SERIAL_TEST         0
#define MACHINE_INIT        1
#define MACHINE_MEASURE     2
#define MACHINE_WASH        3
#define MACHINE_EMPTY       4
#define MACHINE_MEA_35      5
#define MACHINE_MEA_100     6
#define MACHINE_MEA_35_100  7
#define MACHINE_TEMPERATURE 8
#define MACHINE_SAMPLEPOOL  9
#define MACHINE_POSTION     10
#define MACHINE_MIRROR_QUERY 11
#define MACHINE_MIRROR_SET   12
#define MACHINE_MIRROR_READ 13
#define MACHINE_MIRROR_ADJUST 14
#define MACHINE_LIGHT         15

#define MACHINE_MEASURE_X     20

#define MACHINE_MEASURE2      21
#define MACHINE_MEASURE2_35   22
#define MACHINE_MEASURE2_100  23
#define MACHINE_MEASURE2_35_100 24
#define MACHINE_MEASURE2_REF  25
#define MACHINE_MEASURE_SEL   26

#define MACHINE_QUERY       40
#define MACHINE_AAA         41
#define MACHINE_UI          99

#define MACHINE_ARM_INIT     50
#define MACHINE_ARM_MEASURE  51
#define MACHINE_ARM_WASH     52
#define MACHINE_ARM_MIRROR_QUERY 53
#define MACHINE_ARM_MIRROR_SET   54
#define MACHINE_ARM_MIRROR_POWER 55
#define MACHINE_ARM_MIRROR_AUTO  56
#define MACHINE_ARM_SELF_CHECK   57

#define MACHINE_ARM_DEBUG    61
class DataSerialTask
{
public:
    DataSerialTask();

public:
    int m_iCmdCode;
    int m_iCmdParam1;
    int m_iCmdParam2;
    int m_iCmdParam3;

    bool m_bEnable;

    float m_fCmdParam1;
    float m_fCmdParam2;
    float m_fCmdParam3;

    double m_dCmdParam1;

    QString m_strParam1;
    QString m_strParam2;
};

#endif // DATASERIALTASK_H

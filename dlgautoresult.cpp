#include "dlgautoresult.h"
#include "ui_dlgautoresult.h"
#include "appdata.h"
#include <string>
DlgAutoResult::DlgAutoResult(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgAutoResult)
{
    ui->setupUi(this);
    this->setWindowTitle("一键操作结果");

    char szBuff[200] = { 0 };
    if(( App->m_pSerialWorker->m_vecMeaXD1.size() >= 3 ) && (  App->m_pSerialWorker->m_vecMeaXD2.size() >= 3  ))
    {
        sprintf(szBuff, "测试1 600：%.2f  5000：%.2f", App->m_pSerialWorker->m_vecMeaXD1[0],App->m_pSerialWorker->m_vecMeaXD2[0]);
        ui->label_1->setText(szBuff);
        sprintf(szBuff, "测试2 600：%.2f  5000：%.2f", App->m_pSerialWorker->m_vecMeaXD1[1],App->m_pSerialWorker->m_vecMeaXD2[1]);
        ui->label_2->setText(szBuff);
        sprintf(szBuff, "测试3 600：%.2f  5000：%.2f", App->m_pSerialWorker->m_vecMeaXD1[2],App->m_pSerialWorker->m_vecMeaXD2[2]);
        ui->label_3->setText(szBuff);
    }

    if( App->m_pSerialWorker->m_vecMeaXD3.size() >= 5 )
    {
        sprintf(szBuff, "测试1: %.2f", App->m_pSerialWorker->m_vecMeaXD3[0]);
        ui->label_4->setText(szBuff);
        sprintf(szBuff, "测试2: %.2f", App->m_pSerialWorker->m_vecMeaXD3[1]);
        ui->label_5->setText(szBuff);
        sprintf(szBuff, "测试3: %.2f", App->m_pSerialWorker->m_vecMeaXD3[2]);
        ui->label_6->setText(szBuff);
        sprintf(szBuff, "测试4: %.2f", App->m_pSerialWorker->m_vecMeaXD3[3]);
        ui->label_7->setText(szBuff);
        sprintf(szBuff, "测试5: %.2f", App->m_pSerialWorker->m_vecMeaXD3[4]);
        ui->label_8->setText(szBuff);
    }
}

DlgAutoResult::~DlgAutoResult()
{
    delete ui;
}

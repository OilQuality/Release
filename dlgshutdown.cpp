#include "dlgshutdown.h"
#include "ui_dlgshutdown.h"

DlgShutDown::DlgShutDown(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgShutDown)
{
    ui->setupUi(this);
    setWindowTitle("关机等待中...");
}

DlgShutDown::~DlgShutDown()
{
    delete ui;
}

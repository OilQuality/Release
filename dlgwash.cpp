#include "dlgwash.h"
#include "ui_dlgwash.h"
#include <qpainter.h>
#include <QPushButton>
#include "appdata.h"
#include "dlgsysinfo.h"
#include <QtWidgets/qdesktopwidget.h>
#include <QKeyEvent>

DlgWash::DlgWash(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgWash)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    resize(768,1024);
/*
    m_pBtn1 = new QPushButton("清洗",this);
    m_pBtn1->resize(99,58);
    m_pBtn1->move(395,298);
    m_pBtn1->setStyleSheet("QPushButton{ font-family:'Microsoft YaHei';font-size:20px;color:#666666;}");
    //m_pBtn1->setText("清洗");
    connect(m_pBtn1, SIGNAL(clicked()), this, SLOT(OnBtn1Clicked()) );

    m_pBtn2 = new QPushButton("排空",this);
    m_pBtn2->resize(99,58);
    m_pBtn2->move(395,424);
    //m_pBtn2->setText("排空");
    m_pBtn2->setStyleSheet("QPushButton{ font-family:'Microsoft YaHei';font-size:20px;color:#666666;}");
    connect(m_pBtn2, SIGNAL(clicked()), this, SLOT(OnBtn2Clicked()) );
*/
    QPushButton *m_pBtn3;
    m_pBtn3 = new QPushButton("",this);
    m_pBtn3->resize(67,67);
    m_pBtn3->move(100,930);
    m_pBtn3->setStyleSheet("border-image: url(:/new/prefix1/png/btn71.png)");
    connect(m_pBtn3, SIGNAL(clicked()), this, SLOT(OnBtn3Clicked()) );

    QPushButton *m_pBtn4;
    m_pBtn4 = new QPushButton("",this);
    m_pBtn4->resize(67,67);
    m_pBtn4->move(350,930);
    m_pBtn4->setStyleSheet("border-image: url(:/new/prefix1/png/N2.png)");
    connect(m_pBtn4, SIGNAL(clicked()), this, SLOT(OnBtn4Clicked()) );

    QPushButton *m_pBtn5;
    m_pBtn5 = new QPushButton("",this);
    m_pBtn5->resize(67,67);
    m_pBtn5->move(601,930);
    m_pBtn5->setStyleSheet("border-image: url(:/new/prefix1/png/N3.png)");
    connect(m_pBtn5, SIGNAL(clicked()), this, SLOT(OnBtn5Clicked()) );

    ui->label->setText("");
    connect(App->m_pSerialWorker, SIGNAL(sigSerialWashMsg(QString)), this, SLOT(OnWashTaskMsg(QString)));
    connect(App->m_pSerialWorker, SIGNAL(sigSerialWashDone()), this, SLOT(OnWashTaskDone()));
}

DlgWash::~DlgWash()
{
    delete ui;
}

void DlgWash::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(rect(), QPixmap(":/new/prefix1/png/bg2.png"), QRect());
}
/*
void DlgWash::OnBtn1Clicked()
{
}
void DlgWash::OnBtn2Clicked()
{
}
*/
//信息按钮
void DlgWash::OnBtn3Clicked()
{
    DlgSysInfo dlg;
    dlg.move((QApplication::desktop()->width() - dlg.width()) / 2, (QApplication::desktop()->height() - dlg.height()) / 2);
    dlg.exec();
}

//主页按钮
void DlgWash::OnBtn4Clicked()
{
    if(( ui->pbWash->text() == "清洗") && ( ui->pbEmpty->text() == "排空"))
    {
        accept();
    }
}

//返回按钮
void DlgWash::OnBtn5Clicked()
{
    if(( ui->pbWash->text() == "清洗") && ( ui->pbEmpty->text() == "排空"))
    {
        reject();
    }
}

void DlgWash::OnWashTaskMsg(QString strMsg)
{
    ui->label->setText(strMsg);
}

void DlgWash::OnWashTaskDone()
{
    ui->pbWash->setText("清洗");
    ui->pbEmpty->setText("排空");
    ui->pbWash->setEnabled(true);
    ui->pbEmpty->setEnabled(true);
}

void DlgWash::on_pbWash_clicked()//清洗
{
    if( ui->pbWash->text() == "清洗")
    {
        App->serialCmdWash();
        ui->pbWash->setText("停止");
        ui->pbEmpty->setEnabled(false);
    }else{
        App->StopRun();
        ui->pbWash->setText("清洗");
        ui->pbEmpty->setEnabled(true);
    }
}

void DlgWash::on_pbEmpty_clicked()//排空
{
    if( ui->pbEmpty->text() == "排空")
    {
        App->serialCmdEmpty();
        ui->pbEmpty->setText("停止");
        ui->pbWash->setEnabled(false);
    }else{
        App->StopRun();
        ui->pbEmpty->setText("排空");
        ui->pbWash->setEnabled(true);
    }
}

void DlgWash::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Escape:
        break;
    default:
        QDialog::keyPressEvent(event);
    }
}

void DlgWash::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    App->StopRun();
}

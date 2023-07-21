#ifndef DLGSHUTDOWN_H
#define DLGSHUTDOWN_H

#include <QDialog>

namespace Ui {
class DlgShutDown;
}

class DlgShutDown : public QDialog
{
    Q_OBJECT

public:
    explicit DlgShutDown(QWidget *parent = nullptr);
    ~DlgShutDown();

private:
    Ui::DlgShutDown *ui;
};

#endif // DLGSHUTDOWN_H

#ifndef DLGAUTORESULT_H
#define DLGAUTORESULT_H

#include <QDialog>

namespace Ui {
class DlgAutoResult;
}

class DlgAutoResult : public QDialog
{
    Q_OBJECT

public:
    explicit DlgAutoResult(QWidget *parent = nullptr);
    ~DlgAutoResult();

private:
    Ui::DlgAutoResult *ui;
};

#endif // DLGAUTORESULT_H

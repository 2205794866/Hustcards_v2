#ifndef FAIL_H
#define FAIL_H

#include <QDialog>

namespace Ui {
class fail;
}

class fail : public QDialog
{
    Q_OBJECT

public:
    explicit fail(QWidget *parent = nullptr);
    ~fail();

private:
    Ui::fail *ui;
};

#endif // FAIL_H

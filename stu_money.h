#ifndef STU_MONEY_H
#define STU_MONEY_H

#include <QDialog>
#include <QPushButton>
#include "canteen.h"
#include "std.h"
#include "cardmanager.h"


namespace Ui {
class stu_money;
}

class stu_money : public QDialog
{
    Q_OBJECT

public:
    explicit stu_money(CardManager *CM, QWidget *parent = nullptr);
    ~stu_money();

private slots:

    void on_pushButton_clicked();

private:
    Ui::stu_money *ui;
    CardManager *CM;

};

#endif // STU_MONEY_H

#ifndef ADD_MONEY_H
#define ADD_MONEY_H

#include <QDialog>
#include "std.h"
#include "cardmanager.h"
#include "succeed.h"
#include "fail.h"


namespace Ui {
class add_money;
}

class add_money : public QDialog
{
    Q_OBJECT

public:
    explicit add_money(CardManager *CM, QWidget *parent = nullptr);
    ~add_money();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::add_money *ui;
    CardManager *CM;
};

#endif // ADD_MONEY_H

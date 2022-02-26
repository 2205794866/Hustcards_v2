#include "add_money.h"
#include "ui_add_money.h"

add_money::add_money(CardManager *CM, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_money)
{
    ui->setupUi(this);
    this->CM = CM;
}

add_money::~add_money()
{
    delete ui;
}




void add_money::on_buttonBox_accepted()
{
    std::string stu_ID = ui->stu_ID->toPlainText().toStdString();
    int money = ui->money->toPlainText().toInt() * 100;
//    std::cout << money <<std::endl;
    if(this->CM->add_money(logger.time,stu_ID, money) == true)
    {
        succeed *ui_succeed = new succeed(this);
        ui_succeed->show();
    }
    else
    {
        fail *ui_fail = new fail(this);
        ui_fail->show();
    }

}


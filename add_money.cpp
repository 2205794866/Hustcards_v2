#include "add_money.h"
#include "ui_add_money.h"

add_money::add_money(CardManager *CM, QWidget *parent) : QDialog(parent),
                                                         ui(new Ui::add_money)
{
    ui->setupUi(this);
    // 初始化
    this->CM = CM;
    this->setWindowIconText("账户充值");
}

add_money::~add_money()
{
    delete ui;
}

void add_money::on_buttonBox_accepted()
{
    // 获取学号
    std::string stu_ID = ui->stu_ID->toPlainText().toStdString();
    // 获取充值金额
    int money = ui->money->toPlainText().toInt() * 100;
    // 充值
    if (this->CM->add_money(logger.get_time(), stu_ID, money) == true)
    // 若成功
    {
        succeed *ui_succeed = new succeed(this);
        ui_succeed->show();
    }
    else
    // 若失败
    {
        fail *ui_fail = new fail(this);
        ui_fail->show();
    }
}

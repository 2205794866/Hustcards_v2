#include "new_stu.h"
#include "ui_new_stu.h"

new_stu::new_stu(CardManager *CM, QWidget *parent) : QDialog(parent),
                                                     ui(new Ui::new_stu)
{
    ui->setupUi(this);
    this->setWindowTitle("开户");
    this->CM = CM;
}

new_stu::~new_stu()
{
    delete ui;
}

void new_stu::on_buttonBox_accepted()
{
    // 获取姓名学号
    std::string name = ui->name->toPlainText().toStdString();
    std::string stu_ID = ui->stu_ID->toPlainText().toStdString();
    // 开户
    if (name.length() > 0 && stu_ID.length() == 10 && CM->open_account(logger.get_time(), stu_ID, name) == true)
    {
        succeed *ui_succeed = new succeed(this);
        ui_succeed->show();
    }
    else
    {
        fail *ui_fail = new fail(this);
        ui_fail->show();
        this->show();
    }
}

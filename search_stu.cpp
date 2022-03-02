#include "search_stu.h"
#include "ui_search_stu.h"

search_stu::search_stu(CardManager *CM, int func_num, QWidget *parent) : QDialog(parent),
                                                                         ui(new Ui::search_stu)
{
    ui->setupUi(this);
    this->CM = CM;
    this->func_num = func_num;
}

search_stu::~search_stu()
{
    delete ui;
}

void search_stu::on_buttonBox_accepted()
{
    // 获取学号
    std::string stu_ID = ui->stu_ID->toPlainText().toStdString();
    // 寻找人
    std::unordered_map<std::string, Person *>::iterator iter = this->CM->Map_IDtoPerson.find(stu_ID);
    if (iter != this->CM->Map_IDtoPerson.end())
    // 若找不到账户
    {
        if (iter->second->is_valid() == false && func_num != 2)
        // 账户无效且不为恢复账户操作
        {
            fail *ui_fail = new fail(this);
            ui_fail->show();
        }
        else
        {
            // 显示信息
            stu_info *ui_stu_info_func = new stu_info(this->CM, func_num, iter->second->get_stu_ID(), this);
            ui_stu_info_func->show();
        }
    }
    else
    {
        fail *ui_fail = new fail(this);
        ui_fail->show();
    }
}

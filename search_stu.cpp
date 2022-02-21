#include "search_stu.h"
#include "ui_search_stu.h"

search_stu::search_stu(CardManager *CM,int func_num, QWidget *parent) :
    QDialog(parent),
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
    std::string stu_ID = ui->stu_ID->toPlainText().toStdString();
    std::unordered_map<std::string, Person *>::iterator iter = this->CM->Map_IDtoPerson.find(stu_ID);
    if(iter != this->CM->Map_IDtoPerson.end())
    {
        stu_info_func *ui_stu_info_func = new stu_info_func(this->CM, func_num, iter->second, this);
        ui_stu_info_func->show();
    }
    else
    {
        fail *ui_fail = new fail(this);
        ui_fail->show();
    }
}

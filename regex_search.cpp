#include "regex_search.h"
#include "ui_regex_search.h"

regex_search::regex_search(CardManager *CM, int func_num, QWidget *parent) : QDialog(parent),
                                                                             ui(new Ui::regex_search)
{
    ui->setupUi(this);
    this->setWindowTitle("模糊查找");
    this->CM = CM;
    this->func_num = func_num;
    if (func_num == 0)
        ui->tips->setText("请输入模糊学号");
    else
    {
        ui->tips->setText("请输入模糊姓名");
    }
}

regex_search::~regex_search()
{
    delete ui;
}

void regex_search::on_buttonBox_accepted()
{
    // 获取模糊信息
    str = ui->str->toPlainText().toStdString();
    search_result *ui_res = new search_result(this->CM, this->str, this->func_num, this);
    ui_res->show();
}

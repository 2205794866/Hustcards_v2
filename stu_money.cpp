#include "stu_money.h"
#include "ui_stu_money.h"

stu_money::stu_money(CardManager *CM, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stu_money)
{
    ui->setupUi(this);
    this->CM = CM;
}

stu_money::~stu_money()
{
    delete ui;
}


void stu_money::on_pushButton_clicked()
{
    int money = 0;
    std::string stu_ID = ui->stu_ID->toPlainText().toStdString();
    std::string begin = ui->begin_time->date().toString("yyyyMMdd").toStdString();
    std::string end = ui->end_time->date().toString("yyyyMMdd").toStdString();
    auto iter = this->CM->Map_IDtoPerson.find(stu_ID);
    if(iter != this->CM->Map_IDtoPerson.end())
    {
        Person *owner = iter->second;
        if(owner->is_valid() == true)
        {
            for(auto record:owner->record_list)
            {
                if(record->time.substr(0, 8) > begin && record->time.substr(0, 8) < end)
                {
                    money+=record->money;
                }
            }
            ui->res->setText(QString::asprintf("%s(学号:%s) 共消费: %d.%02d元",owner->get_name().c_str(), owner->get_stu_ID().c_str(), money/100, money%100));
        }
        else
        {
            ui->res->setText("该账户已销户");
        }
    }
    else
    {
        ui->res->setText("未找到该账户");
    }
}


#include "stu_info_func.h"
#include "ui_stu_info_func.h"

stu_info_func::stu_info_func(CardManager *CM,int func_num,std::string stu_ID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stu_info_func)
{
    ui->setupUi(this);
    this->setWindowTitle("学生信息");
    this->CM = CM;
    this->stu_ID = stu_ID;
    Person *one = nullptr;
    auto iter = this->CM->Map_IDtoPerson.find(stu_ID);
    if(iter != this->CM->Map_IDtoPerson.end())
    {
        one = iter->second;
    }

    this->func_num = func_num;
    this->card_model = new QStandardItemModel;

    ui->name_3->setText(QString::fromStdString(one->get_name()));
    ui->stu_ID_3->setText(QString::fromStdString(one->get_stu_ID()));
    ui->func->setStyleSheet("color:red;");

    ui->card_list->setModel(card_model);
    ui->card_list->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->card_list->setSelectionMode( QAbstractItemView::SingleSelection);


    //card list
    card_model->setHorizontalHeaderItem(0, new QStandardItem(tr("卡号")));
    Card *p = one->head->next;
    int i = 0;
    while(p != nullptr)
    {
        QStandardItem *item = new QStandardItem(QString::fromStdString(p->get_card_ID()));
        if(p->is_valid() == true)
        {
            item->setBackground(Qt::green);
        }
        else
        {
            item->setBackground(Qt::red);
        }
        card_model->setItem(i, item);
        p = p->next;
        i++;
    }
    // func_num = 0 销户
    if(func_num == 0)
    {
        ui->func->setText(tr("是否进行销户操作:"));
    }
    // func_num = 1 补卡
    else if(func_num == 1)
    {
        ui->func->setText(tr("是否进行补卡操作:"));
    }
    // func_num = 2 挂失
    else if(func_num == 2)
    {
        ui->func->setText(tr("是否进行挂失操作:"));
    }
    // func_num = 3 解挂
    else if(func_num == 3)
    {
        ui->func->setText(tr("是否进行解挂操作:"));
    }
}

stu_info_func::~stu_info_func()
{
    delete ui;
}

void stu_info_func::on_buttonBox_accepted()
{
    if(this->func_num == 0)
    {
        if(this->CM->cancel_account(logger.time, stu_ID) == true)
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
    else if(this->func_num == 1)
    {
        if(this->CM->reissue_card(logger.time, stu_ID) == true)
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
    else if(this->func_num == 2)
    {
        if(this->CM->report_lost(logger.time,stu_ID) == true)
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
    else if(this->func_num == 3)
    {
        if(this->CM->remove_lost(logger.time, stu_ID) == true)
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

}


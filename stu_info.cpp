#include "stu_info.h"
#include "ui_stu_info.h"

stu_info::stu_info(CardManager *CM, std::string stu_ID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stu_info)
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

    this->card_model = new QStandardItemModel;

    ui->name->setText(QString::fromStdString(one->get_name()));
    ui->stu_ID->setText(QString::fromStdString(one->get_stu_ID()));



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

}

stu_info::~stu_info()
{
    delete ui;
}

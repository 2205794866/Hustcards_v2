#include "stu_info.h"
#include "ui_stu_info.h"

stu_info::stu_info(CardManager *CM, Person *one, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stu_info)
{
    ui->setupUi(this);
    this->setWindowTitle("学生信息");
    this->CM = CM;
    this->one = one;

    this->card_model = new QStandardItemModel;

    ui->name->setText(QString::fromStdString(one->get_name()));
    ui->stu_ID->setText(QString::fromStdString(one->get_stu_ID()));



    ui->card_list->setModel(card_model);
    ui->card_list->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->card_list->setSelectionMode( QAbstractItemView::SingleSelection);


    //card list
    card_model->setHorizontalHeaderItem(0, new QStandardItem(tr("卡号")));
    for(unsigned int i = 0; i<one->cardlist->size(); i++)
    {
//        std::cout << i << std::endl;
        Card *new_one = (*one->cardlist)[i];
        QStandardItem *item = new QStandardItem(QString::fromStdString(new_one->get_card_ID()));
        if(new_one->is_valid() == true)
        {
            item->setBackground(Qt::green);
        }
        else
        {
//            std::cout << 1 << std::endl;
            item->setBackground(Qt::red);
        }
        card_model->setItem(i, item);
    }


}

stu_info::~stu_info()
{
    delete ui;
}

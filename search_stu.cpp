#include "search_stu.h"
#include "ui_search_stu.h"

search_stu::search_stu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::search_stu)
{
    ui->setupUi(this);
}

search_stu::~search_stu()
{
    delete ui;
}

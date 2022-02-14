#include "succeed.h"
#include "ui_succeed.h"

succeed::succeed(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::succeed)
{
    ui->setupUi(this);
}

succeed::~succeed()
{
    delete ui;
}

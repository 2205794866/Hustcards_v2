#include "cancel_account.h"
#include "ui_cancel_account.h"

cancel_account::cancel_account(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cancel_account)
{
    ui->setupUi(this);
}

cancel_account::~cancel_account()
{
    delete ui;
}

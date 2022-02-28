#include "get_password.h"
#include "ui_get_password.h"

get_password::get_password(std::string &pass_word, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::get_password),
    pass_word(pass_word)
{
    ui->setupUi(this);

}

get_password::~get_password()
{
    delete ui;
}

void get_password::on_buttonBox_accepted()
{
    this->pass_word = ui->plainTextEdit->toPlainText().toStdString();
}


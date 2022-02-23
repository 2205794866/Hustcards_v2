#include "consume.h"
#include "ui_consume.h"

consume::consume(canteen *CT,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::consume)
{
    ui->setupUi(this);
    this->CT = CT;
    this->setWindowTitle("消费界面");
}

consume::~consume()
{
    delete ui;
}

void consume::on_buttonBox_accepted()
{
    std::string time = logger.time;
    std::string card_ID = ui->card_ID->toPlainText().toStdString();
    int canteen_ID = ui->canteen_ID->value();
    int money = 0;
    char buff[20];
    sprintf(buff, "%.2lf", ui->money->value());

    int i = 0;
    while(buff[i] != '\0')
    {
        if(buff[i] >= '0' && buff[i] <= '9')
        {
            money *= 10;
            money += buff[i] - '0';
        }
        i++;
    }
    std::cout << time << card_ID << money << std::endl;
    bool flag = CT->consume(new record(time, canteen_ID, card_ID, money));
    if(flag == true)
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


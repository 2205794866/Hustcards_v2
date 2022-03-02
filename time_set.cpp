#include "time_set.h"
#include "ui_time_set.h"

extern Logger logger;

time_set::time_set(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::time_set)
{
    //
    ui->setupUi(this);
    this->setWindowTitle("设置时间");
    // 显示当前时间
    std::string tm = logger.get_time();
    int ff = std::stoi(tm.substr(14, 2));
    tm = tm.substr(0, 14);
    QDateTime Qtm = QDateTime::fromString(QString::fromStdString(tm), "yyyyMMddhhmmss");
    // 
    ui->curren_time->setDateTime(Qtm);
    ui->cureent_ff->setValue(ff);
    ui->now_time->setDateTime(Qtm);
    ui->now_ff->setValue(ff);
}

time_set::~time_set()
{
    delete ui;
}

void time_set::on_buttonBox_accepted()
{
    // 获取新时间
    std::string tm = ui->now_time->dateTime().toString("yyyyMMddhhmmss").toStdString();
    tm += QString::asprintf("%02d", ui->now_ff->value()).toStdString();
    // 设置时间
    if(logger.set_time(tm) == true)
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


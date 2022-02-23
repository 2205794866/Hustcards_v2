#include "log.h"
#include "ui_log.h"


extern Logger logger;
log::log(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::log)
{
    ui->setupUi(this);
    this->setWindowTitle("日志");
    operation_model = new QStandardItemModel;
    consume_model = new QStandardItemModel;

    operation_model->setHorizontalHeaderLabels(QStringList()<<"时间"<<"学号"<<"姓名"<<"操作内容"<<"状态");
    consume_model->setHorizontalHeaderLabels(QStringList() << "时间" << "窗口号" << "卡号" << "金额" << "状态");

    ui->operation_list->horizontalHeader()->setVisible(true);//显示或隐藏表头
    ui->operation_list->verticalHeader()->setVisible(true);//显示或隐藏序列行
    ui->operation_list->setAutoScroll(true);//自动滚动条
    ui->operation_list->resizeColumnsToContents(); //根据内容调整大小
    ui->operation_list->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//根据容器调整大小
    ui->operation_list->setEditTriggers(QAbstractItemView::NoEditTriggers);//只读
    ui->operation_list->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选中模式为选中行
    ui->operation_list->setSelectionMode( QAbstractItemView::SingleSelection); //设置选中单行

    ui->consume_list->horizontalHeader()->setVisible(true);//显示或隐藏表头
    ui->consume_list->verticalHeader()->setVisible(true);//显示或隐藏序列行
    ui->consume_list->setAutoScroll(true);//自动滚动条
    ui->consume_list->resizeColumnsToContents(); //根据内容调整大小
    ui->consume_list->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//根据容器调整大小
    ui->consume_list->setEditTriggers(QAbstractItemView::NoEditTriggers);//只读
    ui->consume_list->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选中模式为选中行
    ui->consume_list->setSelectionMode( QAbstractItemView::SingleSelection); //设置选中单行

    ui->operation_list->setModel(operation_model);
    ui->consume_list->setModel(consume_model);


    for(auto iter = logger.operation_list.begin(); iter < logger.operation_list.end(); iter ++)
    {
        insert_operation_record(*iter);
    }

    for(auto iter = logger.consume_list.begin(); iter < logger.consume_list.end(); iter ++)
    {
        insert_consume_record(*iter);
    }
}

log::~log()
{
    delete ui;
}

void log::insert_operation_record(operation_record *record)
{
    QString Qtime = QString::fromStdString(record->time);
    QString Qstu_ID = QString::fromStdString(record->stu_ID);
    QString Qname = QString::fromStdString(record->name);
    QString Qoperation = QString::fromStdString(record->operation);
    QString Qflag;
    if(record->succeed == true)
        Qflag = tr("成功");
    else
        Qflag = tr("失败");
    int row_num = operation_model->rowCount();
    operation_model->setItem(row_num, 0, new QStandardItem(Qtime));
    operation_model->setItem(row_num, 1, new QStandardItem(Qstu_ID));
    operation_model->setItem(row_num, 2, new QStandardItem(Qname));
    operation_model->setItem(row_num, 3, new QStandardItem(Qoperation));
    operation_model->setItem(row_num, 4, new QStandardItem(Qflag));
}

void log::insert_consume_record(consume_record *record)
{
    QString Qtime = QString::fromStdString(record->time);
    QString Qcanteen_ID = QString::asprintf("%d", record->canteen_ID);
    QString Qcard_ID = QString::fromStdString(record->card_ID);
    QString Qmoney = QString::asprintf("%d", record->money);
    QString Qflag;
    if(record->succeed == true)
        Qflag = tr("成功");
    else
        Qflag = tr("失败");
    int row_num = consume_model->rowCount();
    consume_model->setItem(row_num, 0, new QStandardItem(Qtime));
    consume_model->setItem(row_num, 1, new QStandardItem(Qcanteen_ID));
    consume_model->setItem(row_num, 2, new QStandardItem(Qcard_ID));
    consume_model->setItem(row_num, 4, new QStandardItem(Qmoney));
    consume_model->setItem(row_num, 5, new QStandardItem(Qflag));
}

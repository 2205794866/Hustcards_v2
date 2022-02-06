#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //初始化
    this->setWindowTitle("HUSTCards");


    //界面信息


    //display stu_info
    // setModel
    ui->stus_info->setModel(stu_model);

    //set headers
    stu_model->setHorizontalHeaderItem(0, new QStandardItem("序号"));
    stu_model->setHorizontalHeaderItem(1, new QStandardItem(tr("学号")));
    stu_model->setHorizontalHeaderItem(2, new QStandardItem(tr("姓名")));
    stu_model->setHorizontalHeaderItem(3, new QStandardItem(tr("余额")));

    //basic set
    ui->stus_info->horizontalHeader()->setVisible(true);//显示或隐藏表头
    ui->stus_info->verticalHeader()->setVisible(false);//显示或隐藏序列行
    ui->stus_info->setAutoScroll(true);//自动滚动条
    ui->stus_info->resizeColumnsToContents(); //根据内容调整大小
    ui->stus_info->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//根据容器调整大小
    ui->stus_info->setEditTriggers(QAbstractItemView::NoEditTriggers);//只读
    ui->stus_info->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选中模式为选中行
    ui->stus_info->setSelectionMode( QAbstractItemView::SingleSelection); //设置选中单行

    //menu bar
    ui->search_menu->addAction(ui->search_person);



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_search_person_triggered()
{

}


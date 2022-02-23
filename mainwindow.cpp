#include "mainwindow.h"
#include "ui_mainwindow.h"

Logger logger;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //初始化
    this->setWindowTitle("HUSTCards");
    this->CM = new CardManager;
    this->CT = new canteen(this->CM);
    //界面信息

    stu_model = new QStandardItemModel;
    operation_model = new QStandardItemModel;
    consume_model = new QStandardItemModel;

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


    //menu bar
    ui->search_menu->addAction(ui->search_person);


    ui->all_menu->addAction(ui->Input_all);
    ui->all_menu->addAction(ui->issue_all_card);


    ui->stu_menu->addAction(ui->open_account);
    ui->stu_menu->addAction(ui->remove_person);
    ui->stu_menu->addAction(ui->add_money);

    ui->card_menu->addAction(ui->issue_card);
    ui->card_menu->addAction(ui->report_lost);
    ui->card_menu->addAction(ui->remove_lost);

    ui->canteen_menu->addAction(ui->consume);
    ui->log_menu->addAction(ui->open_log);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::insert_data(unsigned int row_num, std::string stu_ID, std::string name, int money)
{
    QString QrowNum = QString::asprintf("%d", row_num);
    QString Qstu_ID = QString::fromStdString(stu_ID);
    QString Qname = QString::fromStdString(name);
    QString Qmoney = QString::asprintf("%d.%02d", money/100, money%100);
    stu_model->setItem(row_num, 0, new QStandardItem(QrowNum));
    stu_model->setItem(row_num, 1, new QStandardItem(Qstu_ID));
    stu_model->setItem(row_num, 2, new QStandardItem(Qname));
    stu_model->setItem(row_num, 3, new QStandardItem(Qmoney));
}

void MainWindow::insert_operation_record(operation_record *record)
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

void MainWindow::insert_consume_record(consume_record *record)
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
    consume_model->setItem(row_num, 3, new QStandardItem(Qmoney));
    consume_model->setItem(row_num, 4, new QStandardItem(Qflag));
}



void MainWindow::on_show_data_clicked()
{
    for(unsigned int i = 0; i<CM->personlist.size(); i++)
    {
        Person *one = CM->personlist[i];
        if(one->is_valid() == true)
        this->insert_data(i, one->get_stu_ID(), one->get_name(), one->get_money());
    }
}


void MainWindow::on_Input_all_triggered()
{
    std::ifstream afile("d:\\Study\\Project\\Hustcards_v2\\Data\\v3\\kh001.txt");
    char buff[255];
    std::string str;
    afile.getline(buff, 255);
    str = buff;
    if(str == "KH")
    {
        while (!afile.eof())
        {
            if(afile.getline(buff, 255).good())
            {
                str = buff;
                str.pop_back();
                std::string stu_ID, name;
                stu_ID = str.substr(0, 10);
                name = str.substr(11);
                this->CM->open_account(stu_ID, name);
            }
            else
            {
                break;
            }
        }
    }
}


void MainWindow::on_clear_data_clicked()
{
    stu_model->removeRows(0, stu_model->rowCount());
}


void MainWindow::on_stus_info_doubleClicked(const QModelIndex &index)
{
    std::string stu_ID = stu_model->item(index.row(), 1)->text().toStdString();
    Person *one = this->CM->Map_IDtoPerson.find(stu_ID)->second;
    stu_info *ui_stu_info = new stu_info(this->CM,one,this);
    ui_stu_info->show();
}



void MainWindow::on_open_account_triggered()
{
    new_stu *ui_new_stu = new new_stu(this->CM, this);
    ui_new_stu->show();
}




void MainWindow::on_issue_all_card_triggered()
{
    CM->issue_card();
}


void MainWindow::on_remove_person_triggered()
{
    search_stu *ui_search_stu = new search_stu(this->CM, 0, this);
    ui_search_stu->show();
}

void MainWindow::on_issue_card_triggered()
{
    search_stu *ui_search_stu = new search_stu(this->CM, 1, this);
    ui_search_stu->show();
}


void MainWindow::on_report_lost_triggered()
{
    search_stu *ui_search_stu = new search_stu(this->CM, 2, this);
    ui_search_stu->show();
}


void MainWindow::on_remove_lost_triggered()
{
    search_stu *ui_search_stu = new search_stu(this->CM, 3, this);
    ui_search_stu->show();
}


void MainWindow::on_add_money_triggered()
{
    add_money *ui_add_money = new add_money(this->CM, this);
    ui_add_money->show();
}


void MainWindow::on_open_log_triggered()
{
    for(auto iter = logger.operation_list.begin(); iter < logger.operation_list.end(); iter ++)
    {
        insert_operation_record(*iter);
    }

    for(auto iter = logger.consume_list.begin(); iter < logger.consume_list.end(); iter ++)
    {
        insert_consume_record(*iter);
    }
}


void MainWindow::on_consume_triggered()
{
    consume *ui_consume = new consume(this->CT, this);
    ui_consume->show();
}


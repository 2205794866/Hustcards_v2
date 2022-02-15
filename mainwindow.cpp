#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //初始化
    this->setWindowTitle("HUSTCards");
    this->CM = new CardManager;

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
    ui->all_menu->addAction(ui->Input_all);



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





void MainWindow::on_show_data_clicked()
{
    for(unsigned int i = 0; i<CM->personlist.size(); i++)
    {
        Person *one = CM->personlist[i];
        this->insert_data(i, one->get_stu_ID(), one->get_name(), one->get_money());
    }
}


void MainWindow::on_Input_all_triggered()
{
    std::ifstream afile("d:\\Study\\Project\\Hustcards_v2\\Data\\v2\\kh001.txt");
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


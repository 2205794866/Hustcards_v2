#include "mainwindow.h"
#include "ui_mainwindow.h"

Logger logger;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //窗口名
    this->setWindowTitle("HUSTCards");
    ui->tabWidget->setCurrentIndex(0);
    //初始化
    this->CM = new CardManager;
    this->CT = new canteen(this->CM);
    //界面信息
    //model
    stu_model = new QStandardItemModel;
    record_model = new QStandardItemModel;

    // 输出学生信息
    ui->stus_info->setModel(stu_model);

    //设置表头
    stu_model->setHorizontalHeaderLabels(QStringList() << "序号" << "学号" << "姓名" << "余额");
    //基本设置
    ui->stus_info->horizontalHeader()->setVisible(true);//显示或隐藏表头
    ui->stus_info->verticalHeader()->setVisible(false);//显示或隐藏序列行
    ui->stus_info->setAutoScroll(true);//自动滚动条
    ui->stus_info->resizeColumnsToContents(); //根据内容调整大小
    ui->stus_info->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//根据容器调整大小
    ui->stus_info->setEditTriggers(QAbstractItemView::NoEditTriggers);//只读
    ui->stus_info->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选中模式为选中行
    ui->stus_info->setSelectionMode( QAbstractItemView::SingleSelection); //设置选中单行
    //设置日志
    ui->record_list->setModel(record_model);
    record_model->setHorizontalHeaderLabels(QStringList() << "序号" << "时间" << "卡号" << "金额");
    //设置

    ui->record_list->horizontalHeader()->setVisible(true);//显示或隐藏表头
    ui->record_list->verticalHeader()->setVisible(false);//显示或隐藏序列行
    ui->record_list->setAutoScroll(true);//自动滚动条
    ui->record_list->resizeColumnsToContents(); //根据内容调整大小
    ui->record_list->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//根据容器调整大小
    ui->record_list->setEditTriggers(QAbstractItemView::NoEditTriggers);//只读
    ui->record_list->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选中模式为选中行
    ui->record_list->setSelectionMode( QAbstractItemView::SingleSelection); //设置选中单行

    //menu bar
    //搜索
    ui->search_menu->addAction(ui->search_person);
    //学生操作
    ui->stu_menu->addAction(ui->open_account);
    ui->stu_menu->addAction(ui->remove_person);
    ui->stu_menu->addAction(ui->add_money);
    //卡操作
    ui->card_menu->addAction(ui->issue_card);
    ui->card_menu->addAction(ui->report_lost);
    ui->card_menu->addAction(ui->remove_lost);
    //食堂操作
    ui->canteen_menu->addAction(ui->consume);
    //批量操作
    ui->all_menu->addAction(ui->Input_all);
    ui->all_menu->addAction(ui->issue_all_card);
    ui->all_menu->addAction(ui->operate_all);
    //日志操作
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::insert_data(unsigned int row_num, std::string stu_ID, std::string name, int money)
//插入学生信息表格
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


void MainWindow::insert_record(unsigned int row_num, record *one)
{
    QString Qrow_num = QString::asprintf("%d", row_num);
    QString Qtm = QString::fromStdString(one->time);
    QString Qcard_ID = QString::fromStdString(one->card_ID);
    QString Qmoney = QString::asprintf("%d.%02d", one->money/100, one->money%100);;
    QList<QStandardItem *> list;
    list.append(new QStandardItem(Qrow_num));
    list.append(new QStandardItem(Qtm));
    list.append(new QStandardItem(Qcard_ID));
    list.append(new QStandardItem(Qmoney));
    record_model->appendRow(list);
}


void MainWindow::on_show_data_clicked()
{
    this->on_clear_data_clicked();
    int num = 0;
    for(auto one: this->CM->personlist)
    //遍历账户表
    {
        if(one->is_valid() == true)
            this->insert_data(num++, one->get_stu_ID(), one->get_name(), one->get_money());
    }
}


void MainWindow::on_Input_all_triggered()
{
    //打开文件
    std::ifstream afile("d:\\Study\\Project\\Hustcards_v2\\Data\\v4\\kh001.txt");
    char buff[255];
    std::string str;
    //获取第一行
    afile.getline(buff, 255);
    str = buff;
    if(str == "KH")
    //判断是否为KH
    {
        while (!afile.eof())
        //若未到结尾
        {
            if(afile.getline(buff, 255).good())
            {
                str = buff;
                //获取姓名学号
                std::string stu_ID, name;
                stu_ID = str.substr(0,str.find(","));
                name = str.substr(str.find(",")+1, str.find(";") - str.find(",") -1);
                //开户
                this->CM->open_account(logger.time, stu_ID, name);
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
    //清空表格
    stu_model->removeRows(0, stu_model->rowCount());
}


void MainWindow::on_stus_info_doubleClicked(const QModelIndex &index)
//打开账户信息
{
    std::string stu_ID = stu_model->item(index.row(), 1)->text().toStdString();
    Person *one = this->CM->Map_IDtoPerson.find(stu_ID)->second;
    stu_info *ui_stu_info = new stu_info(this->CM, 0, one->get_stu_ID(),this);
    ui_stu_info->show();
}



void MainWindow::on_open_account_triggered()
//开户
{
    new_stu *ui_new_stu = new new_stu(this->CM, this);
    ui_new_stu->show();
}


void MainWindow::on_issue_all_card_triggered()
//批量发卡
{
    CM->issue_card(logger.time);
}


void MainWindow::on_search_person_triggered()
//查找
{
    search_stu *ui_search_stu = new search_stu(this->CM, 0, this);
    ui_search_stu->show();
}

void MainWindow::on_remove_person_triggered()
//销户
{
    search_stu *ui_search_stu = new search_stu(this->CM, 1, this);
    ui_search_stu->show();
}

void MainWindow::on_recover_account_triggered()
//恢复账户
{
    search_stu *ui_search_stu = new search_stu(this->CM, 2, this);
    ui_search_stu->show();
}

void MainWindow::on_issue_card_triggered()
//补卡
{
    search_stu *ui_search_stu = new search_stu(this->CM, 3, this);
    ui_search_stu->show();
}


void MainWindow::on_report_lost_triggered()
//挂失
{
    search_stu *ui_search_stu = new search_stu(this->CM, 4, this);
    ui_search_stu->show();
}


void MainWindow::on_remove_lost_triggered()
//解挂
{
    search_stu *ui_search_stu = new search_stu(this->CM, 5, this);
    ui_search_stu->show();
}


void MainWindow::on_add_money_triggered()
//充值
{
    add_money *ui_add_money = new add_money(this->CM, this);
    ui_add_money->show();
}


void MainWindow::on_consume_triggered()
//消费
{
    consume *ui_consume = new consume(this->CT, this);
    ui_consume->show();
}

Operation* MainWindow::get_operation(std::string str)
{
    std::string tm, func, stu_ID, name, card_ID;
    int func_num, money;
    Operation *one = nullptr;
    tm = str.substr(0, str.find(","));
    str = str.substr(str.find(",") + 1);
    func = str.substr(0, str.find(","));
    str = str.substr(str.find(",") + 1);
    if(func == "销户")
        func_num = 1;
    else if(func == "补卡")
        func_num = 2;
    else if(func == "挂失")
        func_num = 3;
    else if(func == "解挂")
        func_num = 4;
    else if(func == "充值")
        func_num = 5;
    else
        func_num = -1;
    switch (func_num) {
    case 1:
    case 2:
    case 3:
    case 4:
        stu_ID = str.substr(0, str.find(";"));
        money = 0;
        one = new Operation(tm,stu_ID, func_num);
        break;
    case 5:
        stu_ID = str.substr(0, str.find(","));
        str = str.substr(str.find(",")+1);
        money = std::stoi(str.substr(0, str.find(";"))) * 100;
        one = new Operation(tm, stu_ID, money, func_num);
        break;
    }
//    std::cout << tm << " " << stu_ID << " " << money <<" "<< func_num << std::endl;
    return one;

}




Operation *MainWindow::get_consume_operation(std::string str, int canteen_ID)
{
    std::string card_ID;
    std::string tm = "";
    std::string str_money;
    int money = 0;
    card_ID = str.substr(0, str.find(","));
    str = str.substr(str.find(",") + 1);
    tm += str.substr(0, str.find(","));
    str = str.substr(str.find(",") + 1);
    tm += str.substr(0, str.find(","));
    str = str.substr(str.find(",") + 1);
    str_money = str.substr(0, str.find(";"));
    str_money.erase(str_money.find("."), 1);
    money = std::stoi(str_money);
//    std::cout << tm << " " << card_ID << canteen_ID << money << std::endl;
    return new Operation(tm, canteen_ID, card_ID ,money, 6);
}

void MainWindow::execute(Operation *one)
{
    if(one->func_num == 6)
    {
        this->CT->consume(new record(one->tm, one->canteen_ID,one->card_ID, one->money));
        return;
    }
    else
    {
        switch (one->func_num) {
        case 1:
            this->CM->cancel_account(one->tm, one->stu_ID);break;
        case 2:
            this->CM->reissue_card(one->tm, one->stu_ID);break;
        case 3:
            this->CM->report_lost(one->tm, one->stu_ID);
            break;
        case 4:
                this->CM->remove_lost(one->tm,one->stu_ID);
            break;
        case 5:
            this->CM->add_money(one->tm, one->stu_ID, one->money);
            break;
        case 6: this->CT->consume(new record(one->tm, one->canteen_ID,one->card_ID, one->money));
            break;
        }
    }
    return;
}


void MainWindow::on_operate_all_triggered()
{
    std::vector<Operation *> ans;
    std::queue<Operation *> data[100];
    //读入数据
    char buff[255];
    std::string str;
    std::ifstream fp;
    clock_t start1 = clock();
    fp.open("d:\\Study\\Project\\Hustcards_v2\\Data\\v4\\cz002.txt"); 
    fp.getline(buff, 255);
    str = buff;
    if(str == "CZ")
    {
        while(!fp.eof())
        {
            if(fp.getline(buff, 255).good())
            {
                str = buff;
                data[0].push(get_operation(str));
            }
            else
            {
                break;
            }
        }
    }
    fp.close();
    clock_t finish1 = clock();
    std::cout << "read CZ takes:" << (double)(finish1 - start1) / CLOCKS_PER_SEC << std::endl;

    //
    clock_t start2 = clock();
    fp.open("d:\\Study\\Project\\Hustcards_v2\\Data\\v4\\wz003.txt");
    fp.getline(buff, 255);
    str = buff;
    if(str == "WZ")
    {
        while(!fp.eof())
        {
            if(fp.getline(buff, 255).good())
            {
                int canteen_ID, nums;
                str = buff;
                if(str == "")
                    continue;
                canteen_ID = std::stoi(str.substr(0, str.find(",")));
                nums = std::stoi(str.substr(str.find(",") +1, str.find(";") - str.find(",")));
                this->CT->recordlist[canteen_ID].assign(nums, nullptr);
//                std::cout << canteen_ID << ":" << this->CT->recordlist[canteen_ID].size() << std::endl;
            }
        }
    }
    fp.close();
    clock_t finish2 = clock();
    std::cout << "read WZ takes:" << (double)(finish2 - start2) / CLOCKS_PER_SEC << std::endl;

    //
    clock_t start3 = clock();
    FILE *fp1;
    // fp.open("d:\\Study\\Project\\Hustcards_v2\\Data\\v4\\xf014.txt");
    fp1 = fopen("d:\\Study\\Project\\Hustcards_v2\\Data\\v4\\xf014.txt", "r");
    fgets(buff, 255, fp1);

    str = buff;
    str.pop_back();
    std::cout << str << std::endl;
    if(str == "XF")
    {
        int canteen_ID = 0;
        while(feof(fp1) == 0)
        {
            if(fgets(buff, 255, fp1) != NULL)
            {
                str = buff;
                str.pop_back();
                if(str == "")
                    continue;
                else if(str[0] == 'W')
                {
                    canteen_ID = std::stoi(str.substr(1));
//                    std::cout << canteen_ID << std::endl;
                }
                else
                {
                    data[canteen_ID].push(get_consume_operation(str, canteen_ID));
                }
            }
        }
    }
    fclose(fp1);
    clock_t finish3 = clock();
    std::cout << "read XF takes:" << (double)(finish3 - start3) / CLOCKS_PER_SEC << std::endl;
    //多路归并
    clock_t start4 = clock();
    ans.reserve(2000000);
    std::priority_queue<Operation *, std::vector<Operation *>, cmp1> que;
    for(int i = 0; i<100; i++)
    {
        if(!data[i].empty())
        {
            que.push(data[i].front());
            data[i].pop();
        }
    }
    while(!que.empty())
    {
        Operation *one = que.top();
        que.pop();
        int canteen_ID = one->canteen_ID;
        ans.emplace_back(one);
        if(!data[canteen_ID].empty())
        {
            que.push(data[canteen_ID].front());
            data[canteen_ID].pop();
        }
    }
    //clear
    for(int i = 0; i<100; i++)
        std::queue<Operation *>().swap(data[i]);

    clock_t finish4 = clock();
    std::cout << "merged takes:" << (double)(finish4 - start4) / CLOCKS_PER_SEC << std::endl;
    clock_t start5 = clock();
    for(auto one: ans)
    {
        execute(one);
        delete one;
    }
    std::vector<Operation *>().swap(ans);
    clock_t finish5 = clock();
    std::cout << "operation takes:" << (double)(finish5 - start5) / CLOCKS_PER_SEC << std::endl;
}


void MainWindow::on_to_begin_clicked()
{
    ui->canteen_ID->setValue(1);
}


void MainWindow::on_to_end_clicked()
{
    ui->canteen_ID->setValue(99);
}


void MainWindow::on_sub_one_clicked()
{
    int canteen_ID = ui->canteen_ID->value();
    if(canteen_ID > 1)
    {
        ui->canteen_ID->setValue(canteen_ID - 1);
    }
}


void MainWindow::on_add_one_clicked()
{
    int canteen_ID = ui->canteen_ID->value();
    if(canteen_ID < 99)
    {
        ui->canteen_ID->setValue(canteen_ID + 1);
    }
}


void MainWindow::on_canteen_ID_valueChanged(int arg1)
{
    this->record_model->removeRows(0, record_model->rowCount());
    int canteen_ID = arg1;
    unsigned int nums = CT->recordlist[canteen_ID].size();
    QString str = QString::asprintf("%d号窗口消费记录数为%d", canteen_ID, nums);
    ui->nums->setText(str);
    for(unsigned int i = 0; i< nums; i++)
    {
        record *one = CT->recordlist[canteen_ID][i];
        if(one != nullptr)
            insert_record(i, one);
    }
}


void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    if(index == 1)
        ui->canteen_ID->setValue(1);
}





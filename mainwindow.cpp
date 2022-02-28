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
    this->AL = new Analyser(this->CM, this->CT);
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
    ui->search_menu->addAction(ui->regex_ID_search);
    ui->search_menu->addAction(ui->regex_name_search);
    //学生操作
    ui->stu_menu->addAction(ui->open_account);
    ui->stu_menu->addAction(ui->remove_person);
    ui->stu_menu->addAction(ui->recover_account);
    ui->stu_menu->addAction(ui->add_money);
    //卡操作
    ui->card_menu->addAction(ui->issue_card);
    ui->card_menu->addAction(ui->report_lost);
    ui->card_menu->addAction(ui->remove_lost);
    //食堂操作
    //批量操作
    ui->all_menu->addAction(ui->Input_all);
    ui->all_menu->addAction(ui->issue_all_card);
    ui->all_menu->addAction(ui->operate_all);
    //分析操作
    ui->al_menu->addAction(ui->summary);
    ui->al_menu->addAction(ui->stu_money);
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


void MainWindow::reflesh_time()
{
    std::string tm = logger.time;
    int ff = std::stoi(tm.substr(14, 2));
    tm = tm.substr(0, 14);
    QDateTime Qtm = QDateTime::fromString(QString::fromStdString(tm), "yyyyMMddhhmmss");
    ui->now_time->setDateTime(Qtm);
    ui->now_ff->setValue(ff);
    ui->time->setDateTime(Qtm);
}


void MainWindow::on_show_data_clicked()
{
    this->on_clear_data_clicked();
    int num = 0, card_nums = 0, record_nums = 0;
    for(auto one: this->CM->personlist)
    //遍历账户表
    {
        if(one->is_valid() == true)
            this->insert_data(num++, one->get_stu_ID(), one->get_name(), one->get_money());
    }
    this->reflesh_time();
    ui->account_num->setText(QString::asprintf("总账户数为%d",CM->personlist.size()));
    ui->valid_acc_num->setText(QString::asprintf("总有效账户数为:%d", num));
    ui->card_num->setText(QString::asprintf("总卡数为:%d",CM->cardlist.size()));
    for(auto card:CM->cardlist)
    {
        if(card->is_valid() == true)
        {
            card_nums++;
        }
    }
    ui->valid_card_num->setText(QString::asprintf("总有效卡数为:%d", card_nums));
    for(int i = 1; i<100; i++)
    {
        record_nums += CT->recordlist[i].size();
    }
    ui->record_num->setText(QString::asprintf("总消费记录数为:%d", record_nums));
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
                this->CT->nums[canteen_ID] = nums;
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
    // std::cout << str << std::endl;
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
    QString str = QString::asprintf("%d号窗口有效消费记录数为%d", canteen_ID, nums);
    QString str1 = QString::asprintf("总消费记录数:%d", CT->nums[canteen_ID]);
    ui->nums->setText(str);
    ui->total_nums->setText(str1);
    for(unsigned int i = 0; i< nums; i++)
    {
        record *one = CT->recordlist[canteen_ID][i];
        if(one != nullptr)
            insert_record(i, one);
    }
}


void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    if(index == 2)
        ui->canteen_ID->setValue(1);
    else if(index ==1)
        this->reflesh_time();
}




void MainWindow::on_regex_ID_search_triggered()
{
    regex_search *ui_regex_search = new regex_search(this->CM, 0, this);
    ui_regex_search->show();

}




void MainWindow::on_regex_name_search_triggered()
{
    regex_search *ui_regex_search = new regex_search(this->CM, 1, this);
    ui_regex_search->show();
}


void MainWindow::on_summary_triggered()
{
    this->AL->summary();
}


void MainWindow::on_time_set_clicked()
{
    time_set *ui_time_set = new time_set(this);
    ui_time_set->exec();
    reflesh_time();
}


void MainWindow::on_clear_clicked()
{
    ui->canteen_ID_cons->setValue(0);
    ui->money->setValue(0.0);
    ui->card_ID->clear();
}

bool MainWindow::is_pass(Person *owner, std::string now_time, int money)
{
    if(money >= 2000)
        return true;
    std::vector<std::string> str_list = {"07","09", "11", "13","17","19"};
    if(!owner->record_list.empty())
    {
        record *current = owner->record_list.back();
        if(current->time.substr(0, 8) == now_time.substr(0, 8))
        {
            std::string now_hour = now_time.substr(8,2);
            std::string current_hour = current->time.substr(8,2);
            int i=1, j=1;
            while(i<=5 && now_hour>=str_list[i] )
            i+=2;
            while(j<=5 && current_hour >=str_list[j])
            j+=2;
            if(i < 7 && now_hour >= str_list[i-1] && current_hour >= str_list[i-1])
            {
                if(i == j)
                {
                    return (owner->today_money+money)>=2000;
                }
            }
        }
    }
    return false;

}


void MainWindow::on_consume_clicked()
{
    //获取时间、卡号、密码
   std::string time = logger.time;
   std::string card_ID = ui->card_ID->toPlainText().toStdString();
   int canteen_ID = ui->canteen_ID_cons->value();
   int money = 0;
   char buff[20];
//   std::cout << ui->money->value() << std::endl;
   sprintf(buff, "%.2lf", ui->money->value());
//   std::cout << buff << std::endl;
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
    
   //密码检查
   bool need_pass, flag = false;
   //得到的pass_word
   std::string pass_word;
   auto iter = CM->Map_CIDtoCard.find(card_ID);
   if(iter != CM->Map_CIDtoCard.end())
    //卡是否存在
   {
       //若存在
       Person *owner = iter->second->owner;
       if(owner->is_valid() == true && iter->second->is_valid() == true)
           //判断人或卡是否有效
       {
           //判断是否需要密码
            need_pass = is_pass(owner, time, money);
            if(need_pass == true)
            {
                 get_password * ui_get_password = new get_password(pass_word, this);
                 ui_get_password->exec();
                 if(iter->second->get_password() == pass_word)
                 {
                    flag = CT->consume(new record(time, canteen_ID, card_ID, money));
                    owner->today_money = 0;
                 }
                 else
                 {
                     flag = false;
                 }
            }
            else
            {
                flag = CT->consume(new record(time, canteen_ID, card_ID, money));
            }
       }
       else
       {
            flag = CT->consume(new record(time, canteen_ID, card_ID, money));
       }
   }

   //显示
   if(flag == true)
   {
       succeed *ui_succeed = new succeed(this);
       ui_succeed->show();
       sprintf(buff, "%d号窗口%s年%s月%s日消费%d笔,共计%d.%02d元", canteen_ID, time.substr(0,4).c_str(), time.substr(4,2).c_str(),time.substr(6,2).c_str(), CT->today_nums[canteen_ID], CT->today_money[canteen_ID]/100, CT->today_money[canteen_ID]%100);
       ui->tips->setText(buff);
   }
   else
   {
       CT->consume(new record(time, canteen_ID, card_ID, money));
       fail *ui_fail = new fail(this);
       ui_fail->show();
   }
}


void MainWindow::on_stu_money_triggered()
{
    stu_money *ui_stu_money = new stu_money(this->CM, this);
    ui_stu_money->exec();
}


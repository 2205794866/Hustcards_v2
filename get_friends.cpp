#include "get_friends.h"
#include "ui_get_friends.h"

get_friends::get_friends(Analyser *AL, CardManager *CM, QWidget *parent) : QDialog(parent),
                                                                           ui(new Ui::get_friends)
{
    ui->setupUi(this);
    // 初始化
    this->AL = AL;
    this->CM = CM;
    // 设置模组
    stu_model = new QStandardItemModel;
    ui->stu_table->setModel(this->stu_model);

    stu_model->setHorizontalHeaderLabels(QStringList() << "序号"
                                                       << "学号"
                                                       << "姓名");
    ui->stu_table->horizontalHeader()->setVisible(true);                           //显示或隐藏表头
    ui->stu_table->verticalHeader()->setVisible(false);                            //显示或隐藏序列行
    ui->stu_table->setAutoScroll(true);                                            //自动滚动条
    ui->stu_table->resizeColumnsToContents();                                      //根据内容调整大小
    ui->stu_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //根据容器调整大小
    ui->stu_table->setEditTriggers(QAbstractItemView::NoEditTriggers);             //只读
    ui->stu_table->setSelectionBehavior(QAbstractItemView::SelectRows);            //设置选中模式为选中行
    ui->stu_table->setSelectionMode(QAbstractItemView::SingleSelection);           //设置选中单行
}

get_friends::~get_friends()
{
    delete ui;
}

void get_friends::on_pushButton_clicked()
{
    // 清空列表
    this->stu_model->removeRows(0, this->stu_model->rowCount());
    // 获取学号
    std::string stu_ID = ui->stu_ID->toPlainText().toStdString();
    // 查找到账户
    auto iter = CM->Map_IDtoPerson.find(stu_ID);
    if (iter == CM->Map_IDtoPerson.end())
    {
        ui->tips->setText("无此账户");
        return;
    }

    //获得姓名
    std::string name = iter->second->get_name();

    //获得朋友列表
    std::vector<std::string> friends = AL->get_friends(stu_ID);

    // 构建表格
    std::vector<Person *> personlist;
    for (auto str : friends)
    {
        if (str != stu_ID)
        {
            personlist.push_back(CM->Map_IDtoPerson.find(str)->second);
        }
    }
    // 总人数
    int nums = 0;
    // 插入表格
    for (auto one : personlist)
    {
        QList<QStandardItem *> list;
        list.append(new QStandardItem(QString::asprintf("%d", ++nums)));
        list.append(new QStandardItem(QString::fromStdString(one->get_stu_ID())));
        list.append(new QStandardItem(QString::fromStdString(one->get_name())));
        stu_model->appendRow(list);
    }
    // 设置提示信息
    QString res = QString::asprintf("%s(学号:%s)共有朋友%d人", CM->Map_IDtoPerson.find(stu_ID)->second->get_name().c_str(), stu_ID.c_str(), nums);
    ui->tips->setText(res);
}

void get_friends::on_stu_table_doubleClicked(const QModelIndex &index)
{
    // 双击打开
    std::string stu_ID = stu_model->item(index.row(), 1)->text().toStdString();
    Person *one = this->CM->Map_IDtoPerson.find(stu_ID)->second;
    stu_info *ui_stu_info = new stu_info(this->CM, 0, one->get_stu_ID(), this);
    ui_stu_info->show();
}

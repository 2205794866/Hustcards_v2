#include "search_result.h"
#include "ui_search_result.h"

search_result::search_result(CardManager *CM, std::string str, int func_num, QWidget *parent) : QDialog(parent),
                                                                                                ui(new Ui::search_result)
{
    ui->setupUi(this);
    this->setWindowTitle("查询结果");
    this->CM = CM;
    this->str = str;
    this->func_num = func_num;
    stu_model = new QStandardItemModel;
    ui->result_table->setModel(this->stu_model);

    stu_model->setHorizontalHeaderLabels(QStringList() << "序号"
                                                       << "学号"
                                                       << "姓名");

    ui->result_table->horizontalHeader()->setVisible(true);                           //显示或隐藏表头
    ui->result_table->verticalHeader()->setVisible(false);                            //显示或隐藏序列行
    ui->result_table->setAutoScroll(true);                                            //自动滚动条
    ui->result_table->resizeColumnsToContents();                                      //根据内容调整大小
    ui->result_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //根据容器调整大小
    ui->result_table->setEditTriggers(QAbstractItemView::NoEditTriggers);             //只读
    ui->result_table->setSelectionBehavior(QAbstractItemView::SelectRows);            //设置选中模式为选中行
    ui->result_table->setSelectionMode(QAbstractItemView::SingleSelection);           //设置选中单行

    int nums = 0;
    for (auto one : CM->personlist)
    {
        if (one->is_valid() == true)
        {
            if (func_num == 0)
            // func_num == 0 为学号模糊
            {
                if (match_0(str, one->get_stu_ID()) == true)
                {
                    QList<QStandardItem *> list;
                    list.append(new QStandardItem(nums++));
                    list.append(new QStandardItem(QString::fromStdString(one->get_stu_ID())));
                    list.append(new QStandardItem(QString::fromStdString(one->get_name())));
                    stu_model->appendRow(list);
                }
            }
            else if (func_num == 1)
            // func_num == 1 为姓名模糊
            {
                if (match_1(str, one->get_name()) == true)
                {
                    QList<QStandardItem *> list;
                    list.append(new QStandardItem(QString::asprintf("%d", ++nums)));
                    list.append(new QStandardItem(QString::fromStdString(one->get_stu_ID())));
                    list.append(new QStandardItem(QString::fromStdString(one->get_name())));
                    stu_model->appendRow(list);
                }
            }
        }
    }
    ui->str->setText(QString::fromStdString(this->str));
    QString res = QString::asprintf("查询结果共有%d条", nums);
    ui->nums->setText(res);
}

search_result::~search_result()
{
    delete ui;
}

bool search_result::match_0(std::string str, std::string stu_ID)
{
    std::string pattern = "^";
    for (auto c : str)
    {
        if (c >= '0' && c <= '9')
            pattern += c;
        else if (c == '?')
            pattern += "\\d?";
        else if (c == '*')
            pattern += "\\d*";
    }
    std::regex re(pattern);
    return std::regex_match(stu_ID, re);
}

bool search_result::match_1(std::string str, std::string name)
{
    std::string pattern = "^";
    for (auto c : str)
    {
        if (c == '?')
            pattern += "([^\\w]{3})";
        else if (c == '*')
            pattern += "([^\\w]{0,})";
        else
        {
            pattern += c;
        }
    }
    std::regex re(pattern);
    return std::regex_match(name, re);
}

void search_result::on_result_table_doubleClicked(const QModelIndex &index)
{
    // 双击显示信息
    std::string stu_ID = stu_model->item(index.row(), 1)->text().toStdString();
    Person *one = this->CM->Map_IDtoPerson.find(stu_ID)->second;
    stu_info *ui_stu_info = new stu_info(this->CM, 0, one->get_stu_ID(), this);
    ui_stu_info->show();
}

#include "logger.h"

Logger::Logger()
{
    this->time = "2021090100000000";
    afile.open("d:\\Study\\Project\\Hustcards_v2\\Data\\v4\\log\\oper_log.txt", std::ios::out);
    bfile.open("d:\\Study\\Project\\Hustcards_v2\\Data\\v4\\log\\cons_log.txt", std::ios::out);
}

bool Logger::write_operation_record(operation_record *one)
{
    // this->operation_list.push_back(one);
    std::string flag = one->flag == true ? "成功" : "失败";
    afile << one->time << " " << one->stu_ID << " " << one->name << " " << one->operation << " " << flag << " " << one->err_msg << std::endl;
    return true;
}

bool Logger::write_consume_record(consume_record *one)
{
    // this->consume_list.push_back(one);
    char money[30], canteen_ID[20], left[30];
    std::string flag = one->flag == true ? "成功" : "失败";
    sprintf(money, "%d.%02d", one->money / 100, one->money % 100);
    sprintf(left, "%d.%02d", one->left / 100, one->left % 100);
    sprintf(canteen_ID, "%2d", one->canteen_ID);
    bfile << one->time << " " << canteen_ID << " " << one->card_ID << " " << "消费:" << money << " 余额:" << left << " " << flag << " " << one->err_msg << std::endl;
    return true;
}

Logger::~Logger()
{
    afile.close();
    bfile.close();
}

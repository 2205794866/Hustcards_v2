#include "logger.h"

Logger::Logger()
{
    this->time = "2021090300000000";
    afile.open("d:\\Study\\Project\\Hustcards_v2\\Data\\v3\\oper_log.txt", std::ios::out);
    bfile.open("d:\\Study\\Project\\Hustcards_v2\\Data\\v3\\cons_log.txt", std::ios::out);
}

bool Logger::write_operation_record(operation_record *one)
{
    // this->operation_list.push_back(one);
    std::string flag = one->succeed==true ? "成功" : "失败";
    afile << one->time << " " << one->stu_ID << " " << one->name << " " << one->operation << " " << flag << std::endl;
    return true;
}

bool Logger::write_consume_record(consume_record *one)
{
    // this->consume_list.push_back(one);
    char buff[100];
    std::string flag = one->succeed==true ? "成功" : "失败";
    sprintf(buff, "%d.%02d", one->money/100, one->money%100);
    bfile << one->time << " " << one->canteen_ID << " " << one->card_ID << " " << buff << " " << flag << std::endl;
    return true;
}

Logger::~Logger()
{
    afile.close();
    bfile.close();
}

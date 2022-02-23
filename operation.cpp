#include "operation.h"

Operation::Operation(Time tm, std::string name, std::string stu_ID, int func_num)
{
    this->tm = tm;
    this->name = name;
    this->stu_ID = stu_ID;
    this->func_num = func_num;
}

Operation::Operation(Time tm, std::string stu_ID, int func_num)
{
    this->tm = tm;
    this->stu_ID = stu_ID;
    this->func_num = func_num;
}

Operation::Operation(Time tm, std::string stu_ID, int money, int func_num)
{
    this->tm = tm;
    this->stu_ID = stu_ID;
    this->money = money;
    this->func_num = func_num;
}

Operation::Operation(Time tm, int canteen_ID, std::string card_ID, int money, int func_num)
{
    this->tm = tm;
    this->canteen_ID = canteen_ID;
    this->card_ID = card_ID;
    this->money = money;
    this->func_num = func_num;
}



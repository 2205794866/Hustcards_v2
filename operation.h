#ifndef OPERATION_H
#define OPERATION_H
#include "std.h"
#include "time.h"


class Operation
{
public:
    Time tm;
    int func_num;   //0 : 开户, 1:补卡， 2:挂失, 3:解挂， 4:充值， 5:消费
    std::string stu_ID, name, card_ID;
    int money, canteen_ID;
    Operation();
    //开户
    Operation(Time tm, std::string name, std::string stu_ID, int func_num = 0);
    //补卡,挂失,解挂
    Operation(Time tm, std::string stu_ID, int func_num);
    //充值
    Operation(Time tm, std::string stu_ID, int money, int func_num = 4);
    //消费
    Operation(Time tm, int canteen_ID, std::string card_ID, int money, int func_num = 5);

};

#endif // OPERATION_H

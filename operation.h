#ifndef OPERATION_H
#define OPERATION_H
#include "std.h"


class Operation
{
public:
    std::string tm;
    int func_num;   //0 : 开户, 1: 销户 , 2:补卡， 3:挂失, 4:解挂， 5:充值， 6:消费
    std::string stu_ID, name, card_ID;
    int money, canteen_ID;
    Operation();
    //开户
    Operation(std::string tm, std::string name, std::string stu_ID, int func_num);
    //销户, 补卡,挂失,解挂
    Operation(std::string tm, std::string stu_ID, int func_num);
    //充值
    Operation(std::string tm, std::string stu_ID, int money, int func_num);
    //消费
    Operation(std::string tm, int canteen_ID, std::string card_ID, int money, int func_num = 5);
};

struct cmp1
{
    /* data */
    bool operator() (Operation* a, Operation* b)
    {
        return a->tm > b->tm;
    }
};
#endif // OPERATION_H

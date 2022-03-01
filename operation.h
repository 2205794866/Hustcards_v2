#ifndef OPERATION_H
#define OPERATION_H
#include "std.h"

class Operation
{
public:
    // 时间
    std::string tm;
    // 功能码 0 : 开户, 1: 销户 , 2:补卡， 3:挂失, 4:解挂， 5:充值， 6:消费
    int func_num;
    // 学号，姓名，卡号
    std::string stu_ID, name, card_ID;
    // 金额，窗口号
    int money, canteen_ID;
    Operation();
    // 0：开户
    Operation(std::string tm, std::string name, std::string stu_ID, int func_num);
    // 1：销户 2：补卡 3：挂失 4： 解挂 4
    Operation(std::string tm, std::string stu_ID, int func_num);
    // 5：充值
    Operation(std::string tm, std::string stu_ID, int money, int func_num);
    // 6：消费
    Operation(std::string tm, int canteen_ID, std::string card_ID, int money, int func_num = 5);
};

struct cmp1
{
    /* data */
    // 比较
    bool operator()(Operation *a, Operation *b)
    {
        return a->tm > b->tm;
    }
};
#endif // OPERATION_H

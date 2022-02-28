#ifndef PERSON_H
#define PERSON_H
#include "std.h"
#include <card.h>

struct _record;
class Person
{
public:
    //有效卡
    Card *valid_one;
    //卡表
    // std::vector <Card *> *cardlist;
    Card *head;
    Card *tail;
    //卡数
    int card_nums;
    //累积消费金额
    int consumption;
    std::vector<struct _record *> record_list;
    // 新建账户
    Person(std::string stu_ID, std::string name);
    //获取姓名
    std::string get_name();
    //获取学号
    std::string get_stu_ID();
    //获取余额
    int get_money();
    //销户
    bool cancel_account();
    //恢复
    bool recover_account();
    //获取是否有效
    bool is_valid();
    //充值
    bool add_money(int x);
    //消费
    bool consume(int x);
private:
    //姓名
    std::string name;
    //学号
    std::string stu_ID;
    //是否有效
    bool valid;
    //余额
    int money;


};

#endif // PERSON_H

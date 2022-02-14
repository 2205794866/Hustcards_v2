#ifndef PERSON_H
#define PERSON_H
#include "std.h"

class Card;

class Person
{
public:
    Card *valid_one;
    std::vector <Card *> *cardlist;

    
    // 新建账户
    Person(std::string stu_ID, std::string name);
    //获取基本信息
    std::string get_name();
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
private:
    std::string name;
    std::string stu_ID;
    bool valid;
    int money;
};

#endif // PERSON_H

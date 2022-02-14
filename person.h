#ifndef PERSON_H
#define PERSON_H
#include "std.h"

class Card;

class Person
{
public:
    // 新建账户
    Person(std::string stu_ID, std::string name);


    //获取基本信息
    std::string get_name();
    std::string get_stu_ID();
    std::vector<Card*> * get_cardlist();
    //获取有效卡
    Card *get_valid_one();

    bool set_valid_one(Card *one);
    //新建卡
    bool Person::add_card(Card *one);
    //获取余额
    int get_money();

    //获取是否有效
    bool is_valid();

    //充值
    bool add_money(int x);
private:
    std::string name;
    std::string stu_ID;
    std::vector <Card *> *cardlist;
    Card *valid_one;
    bool valid;

    int money;

};

#endif // PERSON_H

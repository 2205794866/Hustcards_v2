#ifndef CARD_H
#define CARD_H
#include "std.h"
#include "person.h"

class Card
{
public:
    //新建卡
    Card(Person *owner, std::string Card_ID, std::string password);
    //获取是否有效
    bool is_valid();
    //挂失
    bool report_lost();
    //解挂
    bool remove_lost();
    //获取基本信息
    std::string get_card_ID();
    Person *get_owner();



private:
    std::string password;
    std::string validTime;
    std::string card_ID;
    bool valid;
    

    Person *owner;
    

};

#endif // CARD_H

#ifndef CARD_H
#define CARD_H
#include "std.h"


class Person;



class Card
{
public:
    //卡主
    Person *owner;
    //下一张卡
    Card *next;
    //新建卡
    Card(Person *owner, std::string Card_ID, std::string password = "8888");
    //挂失
    bool report_lost();
    //解挂
    bool remove_lost();
    //获取卡号
    std::string get_card_ID();
    std::string get_password();
    //获取是否有效
    bool is_valid();
    
private:
    //密码
    std::string password;
    //有效期
    std::string validTime;
    //卡号
    std::string card_ID;
    //是否有效
    bool valid;
    

};

#endif // CARD_H

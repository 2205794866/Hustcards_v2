#ifndef CARD_H
#define CARD_H
#include "std.h"
#include "person.h"





class Card
{
public:
    //卡主
    Person *owner;
    //新建卡
    Card(Person *owner, std::string Card_ID, std::string password = "8888");
    //挂失
    bool report_lost();
    //解挂
    bool remove_lost();
    //获取卡号
    std::string get_card_ID();
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

#include "card.h"

Card::Card(Person *owner, std::string card_ID, std::string password)
{
    //初始化
    this->owner = owner;
    this->card_ID = card_ID;
    this->password = password;
    this->valid = true;
    this->next = nullptr;
}

bool Card::is_valid()
//返回卡是否有效
{
    return this->valid;
}

std::string Card::get_card_ID()
//返回卡号
{
    return this->card_ID;
}

bool Card::report_lost()
{
    //若该卡有效则成功挂失
    if (this->valid == true)
    {
        this->valid = false;
        return true;
    }
    //否则挂失失败
    return false;
}

bool Card::remove_lost()
{
    //若该卡无效成功解挂
    if (this->valid == false)
    {
        this->valid = true;
        return true;
    }
    //否则则解挂失败
    return false;
}

std::string Card::get_password()
{
    return password;
}

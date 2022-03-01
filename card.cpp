#include "card.h"

Card::Card(Person *owner, std::string card_ID, std::string password)
{
    // 初始化
    // 初始化主人
    this->owner = owner;
    // 初始化卡号
    this->card_ID = card_ID;
    // 初始化密码
    this->password = password;
    // 有效性
    this->valid = true;
    // 下一张卡
    this->next = nullptr;
}
// 返回卡是否有效
bool Card::is_valid()
{
    return this->valid;
}

// 返回卡号
std::string Card::get_card_ID()
{
    return this->card_ID;
}

std::string Card::get_password()
{
    return password;
}

// 设置密码
bool Card::set_password(std::string pd)
{
    this->password = pd;
    return true;
}

// 挂失
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

// 解挂
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

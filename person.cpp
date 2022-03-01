#include "person.h"

Person::Person(std::string stu_ID, std::string name)
//初始化
{
    this->stu_ID = stu_ID;
    this->name = name;
    this->money = 0;
    //新建卡列表
    // this->cardlist = new std::vector<Card *>;
    this->head = this->tail = new Card(this, "");
    //有效卡无
    valid_one = nullptr;
    //初始为有效
    valid = true;
    //卡数为0
    card_nums = 0;
    //总消费钱数
    this->consumption = 0;
    //当天消费钱数
    this->today_money = 0;
}

std::string Person::get_name()
//返回姓名
{
    return this->name;
}

std::string Person::get_stu_ID()
//返回卡号
{
    return this->stu_ID;
}

int Person::get_money()
//返回余额
{
    return this->money;
}

bool Person::is_valid()
//返回是否有效
{
    return this->valid;
}

bool Person::cancel_account()
//销户
{
    if (this->valid == true)
    {
        this->valid = false;
        return true;
    }
    else
        return false;
}

bool Person::recover_account()
//恢复账户
{
    if (this->valid == false)
    {
        this->valid = true;
        return true;
    }
    else
        return false;
}

bool Person::add_money(int x)
//充值
{
    int sum = this->money + x;
    if (sum < 0 || sum > 99999)
    {
        return false;
    }
    else
    {
        this->money = sum;
        return true;
    }
}

bool Person::consume(int x)
//消费
{
    int sum = this->money - x;
    if (sum < 0 || sum > 99999)
    {
        return false;
    }
    else
    {
        this->money = sum;
        return true;
    }
}

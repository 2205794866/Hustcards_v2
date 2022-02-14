#include "person.h"

Person::Person(std::string stu_ID, std::string name)
{
    this->stu_ID = stu_ID;
    this->name = name;
    this->money = 0;
    this->cardlist = new std::vector<Card *>;
    valid_one = nullptr;
    valid = true;
}


std::string Person::get_name()
{
    return this->name;
}

std::string Person::get_stu_ID()
{
    return this->stu_ID;
}

int Person::get_money()
{
    return this->money;
}

bool Person::is_valid()
{
    return this->valid;
}

bool Person::cancel_account()
{
    if(this->valid == true)
    {
        this->valid = false;
        return true;
    }
    else
        return false;
}

bool Person::recover_account()
{
    if(this->valid == false)
    {
        this->valid = true;
        return true;
    }
    else
        return false;
}

bool Person::add_money(int x)
{
    int sum = this->money + x;
    if(sum < 0 || sum > 99999)
    {
        return false;
    }
    else
    {
        this->money = sum;
        return true;
    }
}

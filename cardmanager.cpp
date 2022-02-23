#include "cardmanager.h"


CardManager::CardManager()
//初始化
{
    
    this->start_ID = "12346";
    this->nums = 0;
}

int CardManager::get_check_code(std::string ID)
//获取校验码
{
    int sum = 0;
    for(int i = 0; i<6; i++)
    {
        sum += ID[i] - '0';
    }
    return (9- sum%10);
}


std::string CardManager::get_card_ID()
{
    std::string stu_ID = "3";
    int num = std::stoi(this->start_ID) + this->nums;
    stu_ID += std::to_string(num);
    stu_ID += std::to_string(get_check_code(stu_ID));
    this->nums++;
    return stu_ID;
}

bool CardManager::open_account(std::string stu_ID, std::string name)
{
    //查找stu_ID是否存在
    std::unordered_map<std::string, Person *>::iterator iter = Map_IDtoPerson.find(stu_ID);
    if(iter != Map_IDtoPerson.end())
    {
        logger.write_operation_record(new operation_record(logger.time, name, stu_ID, "开户", false));
        return false;
    }
    //新建账户
    Person *one = new Person(stu_ID, name);
    //将账户纳入管理
    this->personlist.push_back(one);
    Map_IDtoPerson.insert(std::make_pair(stu_ID, one));
    logger.write_operation_record(new operation_record(logger.time, name, stu_ID, "开户", true));
    return true;
}

bool CardManager::issue_card()
{
    //对符合条件账户发卡
    for(unsigned int i = 0; i<this->personlist.size(); i++)
    {
        Person *one = personlist[i];
        if(one->cardlist->size() == 0)
        {
            std::string card_ID = get_card_ID();
            Card* newone = new Card(personlist[i], card_ID, "8888");
            this->cardlist.push_back(newone);
            Map_CIDtoCard.insert(std::make_pair(card_ID, newone));
            one->cardlist->push_back(newone);
            one->valid_one = newone;
            logger.write_operation_record(new operation_record(logger.time,one->get_name(), one->get_stu_ID(), "发卡", true));
        }
    }
    return true;
}


bool CardManager::reissue_card(Person *one)
{
    //挂失最新卡
    if(one->valid_one != nullptr)
        one->valid_one->report_lost();
    //获取卡号
    std::string card_ID = get_card_ID();
    Card *newone = new Card(one, card_ID, "8888");
    //
    one->cardlist->push_back(newone);
    one->valid_one = newone;
    this->cardlist.push_back(newone);
    this->Map_CIDtoCard.insert(std::make_pair(card_ID, newone));
    logger.write_operation_record(new operation_record(logger.time,one->get_name(), one->get_stu_ID(), "补卡", true));
    return true;
}

bool CardManager::report_lost(Card *one)
{
    bool flag = one->report_lost();
    logger.write_operation_record(new operation_record(logger.time,one->owner->get_name(), one->owner->get_stu_ID(), "挂失", flag));
    return flag;
}

bool CardManager::remove_lost(Card *one)
{
    bool flag = one->remove_lost();
    logger.write_operation_record(new operation_record(logger.time,one->owner->get_name(), one->owner->get_stu_ID(), "解挂", flag));
    return flag;
}

bool CardManager::cancel_account(Person *one)
{
    bool flag = one->cancel_account();
    logger.write_operation_record(new operation_record(logger.time,one->get_name(), one->get_stu_ID(), "开户", flag));
    return flag;
}

bool CardManager::recover_account(Person *one)
{
    bool flag = one->recover_account();
    logger.write_operation_record(new operation_record(logger.time,one->get_name(), one->get_stu_ID(), "开户", flag));
    return flag;
}

bool CardManager::add_money(Person *one, int x)
{
    bool flag = one->add_money(x);
    logger.write_operation_record(new operation_record(logger.time, one->get_name(),one->get_stu_ID(), "充值" + std::to_string(x/100) , flag));
    return flag;
}

bool CardManager::consume(std::string card_ID, int x)
{
    auto iter = this->Map_CIDtoCard.find(card_ID);
    if(iter == this->Map_CIDtoCard.end())
    {
        return false;
    }
    Person *one = iter->second->owner;
    bool flag = one->consume(x);
    return flag;
}

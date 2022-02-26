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

int CardManager::get_card_nums()
//获取卡数
{
    return this->nums;
}


std::string CardManager::get_card_ID()
//获取卡_ID
{
    std::string card_ID = "3";
    int num = std::stoi(this->start_ID) + this->nums;
    card_ID += std::to_string(num);
    card_ID += std::to_string(get_check_code(card_ID));
    this->nums++;
    return card_ID;
}

bool CardManager::open_account(std::string tm, std::string stu_ID, std::string name)
{
    //查找stu_ID是否存在
    auto iter = Map_IDtoPerson.find(stu_ID);
    if(iter != Map_IDtoPerson.end())
    //若不存在，则卡户失败
    {
        //写入日志
        logger.write_operation_record(new operation_record(tm, name, stu_ID, "开户", false));
        return false;
    }
    //新建账户
    Person *one = new Person(stu_ID, name);
    //将账户纳入管理
    //push进账户列表
    this->personlist.push_back(one);
    //插入关系表
    Map_IDtoPerson.insert(std::make_pair(stu_ID, one));
    //写入日志
    logger.write_operation_record(new operation_record(tm, name, stu_ID, "开户", true));
    return true;
}

bool CardManager::issue_card(std::string tm)
//对符合条件账户发卡
{
    for(auto one : this->personlist)
    {
        if(one->is_valid() == true)
        //判断账户是否有效
        {
            if(one->cardlist->size() == 0)
            {
                //获取卡号
                std::string card_ID = get_card_ID();
                //新建卡
                Card *new_card = new Card(one, card_ID, "8888");
                //加入管理
                this->cardlist.push_back(new_card);
                this->Map_CIDtoCard.insert(std::make_pair(card_ID, new_card));
                //对账户设置
                one->cardlist->push_back(new_card);
                one->valid_one = new_card;
                //写入日志
                logger.write_operation_record(new operation_record(tm,one->get_name(), one->get_stu_ID(), "发卡", true));
            }
        }
    }
    return true;
}


bool CardManager::reissue_card(std::string tm, Person *one)
//重新办卡或发卡
{
    bool flag;
    if(one->is_valid() == false)
    {
        flag = false;
    }
    else
    {
        //挂失最新卡
        if(one->valid_one != nullptr)
        //若存在
            one->valid_one->report_lost();
        //获取卡号
        std::string card_ID = get_card_ID();
        //新建卡
        Card *newone = new Card(one, card_ID, "8888");
        //加入管理
        this->cardlist.push_back(newone);
        this->Map_CIDtoCard.insert(std::make_pair(card_ID, newone));
        //对账户设置
        one->cardlist->push_back(newone);
        one->valid_one = newone;
        flag = true;
    }
    //写入日志
    logger.write_operation_record(new operation_record(tm, one->get_name(),one->get_stu_ID(), "补卡", flag));
    return true;
}

bool CardManager::report_lost(std::string tm,Card *one)
//挂失
{
    bool flag;
    if(one->owner->is_valid() == false)
    //判断账户是否有效
        flag = false;
    else
    {
        //挂失
        flag = one->report_lost();
    }
    logger.write_operation_record(new operation_record(tm,one->owner->get_name(), one->owner->get_stu_ID(), "挂失", flag));
    return flag;
}

bool CardManager::remove_lost(std::string tm, Card *one)
{
    bool flag;
    if(one->owner->is_valid() == false)
    //判断账户是否有效
    {
        flag = false;
    }
    else
    {   
        //解挂
        flag = one->remove_lost();
    }
    logger.write_operation_record(new operation_record(tm,one->owner->get_name(), one->owner->get_stu_ID(), "解挂", flag));
    return flag;
}

bool CardManager::cancel_account(std::string tm, Person *one)
{
    //销户
    bool flag = one->cancel_account();
    //日志
    logger.write_operation_record(new operation_record(tm,one->get_name(), one->get_stu_ID(), "开户", flag));
    return flag;
}

bool CardManager::recover_account(std::string tm, Person *one)
{
    //恢复账户
    bool flag = one->recover_account();
    //日志记录
    logger.write_operation_record(new operation_record(tm,one->get_name(), one->get_stu_ID(), "开户", flag));
    return flag;
}

bool CardManager::add_money(std::string tm, Person *one, int x)
{
    //充值
    bool flag;
    if(one->is_valid() == false)
        flag = false;
    else 
        flag = one->add_money(x);
    //日志记录
    logger.write_operation_record(new operation_record(tm, one->get_name(),one->get_stu_ID(), "充值" + std::to_string(x/100) , flag));
    return flag;
}


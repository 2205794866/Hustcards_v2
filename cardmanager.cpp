#include "cardmanager.h"

// 初始化
CardManager::CardManager()
{
    this->start_ID = "12346";
    this->nums = 0;
}

// 获取校验码
int CardManager::get_check_code(std::string ID)
{
    // 相加取模
    int sum = 0;
    for (int i = 0; i < 6; i++)
    {
        sum += ID[i] - '0';
    }
    return (9 - sum % 10);
}

//获取卡数
int CardManager::get_card_nums()
{
    return this->nums;
}

//获取卡_ID
std::string CardManager::get_card_ID()
{
    // 开头为3
    std::string card_ID = "3";
    // 序列号
    int num = std::stoi(this->start_ID) + this->nums;
    // 连接
    card_ID += std::to_string(num);
    // 连接校验码
    card_ID += std::to_string(get_check_code(card_ID));
    // 卡数++
    this->nums++;
    return card_ID;
}

// 开户
bool CardManager::open_account(std::string tm, std::string stu_ID, std::string name)
{
    //查找账户是否存在
    auto iter = Map_IDtoPerson.find(stu_ID);
    if (iter != Map_IDtoPerson.end())
    //若存在，则开户户失败
    {
        //写入日志
        logger.write_operation_record(new operation_record(tm, name, stu_ID, "开户", false, "学号重复"));
        return false;
    }
    //新建账户
    Person *one = new Person(stu_ID, name);
    //将账户纳入管理
    // 进账户列表
    this->personlist.push_back(one);
    //插入关系表
    Map_IDtoPerson.insert(std::make_pair(stu_ID, one));
    //写入日志
    logger.write_operation_record(new operation_record(tm, name, stu_ID, "开户", true));
    return true;
}

// 对符合条件账户发卡，统一发卡
bool CardManager::issue_card(std::string tm)
{
    // 遍历账户表
    for (auto one : this->personlist)
    {
        if (one->is_valid() == true)
        //判断账户是否有效
        {
            if (one->tail->get_card_ID() == "")
            //判断是否未有卡，head学号为空
            {
                // 获取卡号
                std::string card_ID = get_card_ID();
                // 新建卡
                Card *new_card = new Card(one, card_ID, "8888");
                // 加入管理
                this->cardlist.push_back(new_card);
                this->Map_CIDtoCard.insert(std::make_pair(card_ID, new_card));
                // 对账户设置
                // 插入链表结尾
                one->tail->next = new_card;
                one->tail = new_card;
                // 设置有效卡
                one->valid_one = new_card;
                one->card_nums++;
                //写入日志
                logger.write_operation_record(new operation_record(tm, one->get_name(), one->get_stu_ID(), "发卡", true));
            }
        }
        else // 失效则写入日志
            logger.write_operation_record(new operation_record(tm, one->get_name(), one->get_stu_ID(), "发卡", false, "账户失效"));
    }
    return true;
}

//补卡或发卡
bool CardManager::reissue_card(std::string tm, std::string stu_ID)
{
    // 日志信息
    bool flag = true;
    std::string err_msg = "";
    // 查找账户是否存在
    auto iter = this->Map_IDtoPerson.find(stu_ID);
    if (iter == this->Map_IDtoPerson.end())
    //若不存在
    {
        // 写入日志
        flag = false;
        err_msg = "无此账户";
        logger.write_operation_record(new operation_record(tm, " ", stu_ID, "补卡", flag, err_msg));
        return flag;
    }
    else
    // 若存在则
    {
        Person *one = iter->second;
        // 判断账户是否失效
        if (one->is_valid() == false)
        {
            flag = false;
            err_msg = "账户失效";
        }
        else
        {
            // if(one->card_nums == 100)
            // {
            // flag = false;
            // err_msg = "补卡超过上限";
            // one->card_nums --;
            // Card *temp = one->head->next;
            // one->head->next = one->head->next->next;
            // delete temp;
            // }
            // else
            // {
            // 挂失有效卡
            if (one->valid_one != nullptr)
                one->valid_one->report_lost();
            //获取卡号
            std::string card_ID = get_card_ID();
            //新建卡
            Card *new_card = new Card(one, card_ID, "8888");
            //加入管理
            this->cardlist.push_back(new_card);
            this->Map_CIDtoCard.insert(std::make_pair(card_ID, new_card));
            //对账户设置
            one->tail->next = new_card;
            one->tail = new_card;
            one->valid_one = new_card;
            one->card_nums++;
            // }
        }
        logger.write_operation_record(new operation_record(tm, one->get_name(), one->get_stu_ID(), "补卡", flag, err_msg));
        return flag;
    }
}

// 挂失
bool CardManager::report_lost(std::string tm, std::string stu_ID)
{
    //日志信息
    bool flag = true;
    std::string err_msg = "";
    // 查找卡是否存在
    auto iter = this->Map_IDtoPerson.find(stu_ID);
    if (iter == this->Map_IDtoPerson.end())
    // 若不存在
    {
        // 写入日志
        flag = false;
        err_msg = "无此账户";
        logger.write_operation_record(new operation_record(tm, " ", stu_ID, "挂失", flag, err_msg));
        return flag;
    }
    else
    {
        Person *one = iter->second;
        // 判断账户是否失效
        if (one->is_valid() == false)
        {
            flag = false;
            err_msg = "账户失效";
        }
        else
        {
            // 判断账户是否油卡
            if (one->tail->get_card_ID() == "")
            {
                flag = false;
                err_msg = "账户无卡";
            }
            else
            {
                // 挂失
                flag = one->tail->report_lost();
                one->valid_one = nullptr;
                if (flag == false)
                    err_msg = "挂失失败";
            }
        }
        // 写入日志
        logger.write_operation_record(new operation_record(tm, one->get_name(), one->get_stu_ID(), "挂失", flag, err_msg));
        return flag;
    }
}

// 解挂
bool CardManager::remove_lost(std::string tm, std::string stu_ID)
{
    // 日志信息
    bool flag = true;
    std::string err_msg = "";
    // 查找该人
    auto iter = this->Map_IDtoPerson.find(stu_ID);
    if (iter == this->Map_IDtoPerson.end())
    {
        flag = false;
        err_msg = "无此账户";
        logger.write_operation_record(new operation_record(tm, " ", stu_ID, "解挂", flag, err_msg));
        return flag;
    }
    else
    {
        // 判断该用户是否有效
        Person *one = iter->second;
        if (one->is_valid() == false)
        {
            flag = false;
            err_msg = "账户失效";
        }
        else
        {
            // 判断是否存在卡
            if (one->tail->get_card_ID() == "")
            {
                flag = false;
                err_msg = "账户无卡";
                logger.write_operation_record(new operation_record(tm, one->get_name(), one->get_stu_ID(), "解挂", flag, err_msg));
            }
            else
            {
                // 挂失上一张卡
                flag = one->tail->remove_lost();
                one->valid_one = one->tail;
                if (flag == false)
                {
                    err_msg = "解挂失败";
                }
                logger.write_operation_record(new operation_record(tm, one->get_name(), one->get_stu_ID(), "解挂", flag, err_msg));
            }
        }
        return flag;
    }
}

// 销户
bool CardManager::cancel_account(std::string tm, std::string stu_ID)
{
    // 日志信息
    bool flag = true;
    std::string err_msg = "";
    // 查找该账户
    auto iter = this->Map_IDtoPerson.find(stu_ID);
    if (iter == this->Map_IDtoPerson.end())
    {
        // 写入日志
        flag = false;
        err_msg = "无此账户";
        logger.write_operation_record(new operation_record(tm, " ", stu_ID, "", flag, err_msg));
        return flag;
    }
    else
    {
        // 销户
        Person *one = iter->second;
        flag = one->cancel_account();
        if (flag == false)
            err_msg = "销户失败";
        // 写入日志
        logger.write_operation_record(new operation_record(tm, one->get_name(), one->get_stu_ID(), "销户", flag, err_msg));
        return flag;
    }
}

// 恢复账户
bool CardManager::recover_account(std::string tm, std::string stu_ID)
{
    // 日志信息
    bool flag = true;
    std::string err_msg = "";
    // 查找该用户是否存在
    auto iter = this->Map_IDtoPerson.find(stu_ID);
    if (iter == this->Map_IDtoPerson.end())
    {
        flag = false;
        err_msg = "无此账户";
        logger.write_operation_record(new operation_record(tm, " ", stu_ID, "恢复账户", flag, err_msg));
        return flag;
    }
    else
    {
        Person *one = iter->second;
        // 恢复账户
        flag = one->recover_account();
        if (flag == false)
            err_msg = "恢复账户失败";
        logger.write_operation_record(new operation_record(tm, one->get_name(), one->get_stu_ID(), "恢复账户", flag, err_msg));
        return flag;
    }
}

// 充值
bool CardManager::add_money(std::string tm, std::string stu_ID, int x)
{
    // 日志信息
    bool flag = true;
    std::string err_msg = "";
    // 查找该账户
    auto iter = this->Map_IDtoPerson.find(stu_ID);
    if (iter == this->Map_IDtoPerson.end())
    {
        flag = false;
        err_msg = "无此账户";
        logger.write_operation_record(new operation_record(tm, " ", stu_ID, "充值" + std::to_string(x / 100), flag, err_msg));
        return flag;
    }
    else
    {
        Person *one = iter->second;
        // 获取充值前余额
        char left[20];
        sprintf(left, "%d.%02d", one->get_money() / 100, one->get_money() % 100);
        // 判断账户是否有效
        if (one->is_valid() == false)
        {
            flag = false;
            err_msg = "账户失效";
        }
        else
        {
            // 充值
            flag = one->add_money(x);
            if (flag == false)
            {
                err_msg = "充值失败";
            }
            // 写入日志
            logger.write_operation_record(new operation_record(tm, one->get_name(), stu_ID, "充值:" + std::to_string(x / 100) + "余额:" + left, flag, err_msg));
            return flag;
        }
        logger.write_operation_record(new operation_record(tm, one->get_name(), stu_ID, "充值:" + std::to_string(x / 100) + "余额:" + left, flag, err_msg));
        return flag;
    }
}

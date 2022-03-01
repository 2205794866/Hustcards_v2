#ifndef CARDMANAGER_H
#define CARDMANAGER_H
#include "std.h"
#include "person.h"
#include "card.h"
#include "logger.h"

extern Logger logger;

// 卡片管理系统
class CardManager
{
private:
    //起始卡号
    std::string start_ID;
    //卡的数量
    int nums;
    //获取卡号校验码
    int get_check_code(std::string);
    //获取下一张卡号
    std::string get_card_ID();

public:
    //初始化
    CardManager();
    //卡列表
    std::vector<Card *> cardlist;
    //账户列表
    std::vector<Person *> personlist;
    //学号->账户
    std::unordered_map<std::string, Person *> Map_IDtoPerson;
    //卡号->卡
    std::unordered_map<std::string, Card *> Map_CIDtoCard;
    //获取卡的数量
    int get_card_nums();
    //开户
    bool open_account(std::string tm, std::string stu_ID, std::string name);
    //发卡
    bool issue_card(std::string tm);
    //补卡
    bool reissue_card(std::string, std::string stu_ID);
    //挂失
    bool report_lost(std::string, std::string stu_ID);
    //解挂
    bool remove_lost(std::string, std::string stu_ID);
    //销户
    bool cancel_account(std::string, std::string stu_ID);
    //恢复
    bool recover_account(std::string, std::string stu_ID);
    //充值
    bool add_money(std::string, std::string stu_ID, int x);
};

#endif // CARDMANAGER_H

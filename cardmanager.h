#ifndef CARDMANAGER_H
#define CARDMANAGER_H
#include "std.h"
#include "person.h"
#include "card.h"


class CardManager
{
private:
    std::string start_ID;
    int nums;

    int get_check_code(std::string);
    std::string get_card_ID();

public:
    CardManager();
    std::vector<Card *> cardlist;
    std::vector<Person *> personlist;
    std::unordered_map<std::string, Person *> Map_IDtoPerson;
    std::unordered_map<std::string, Card*> Map_CIDtoCard;    

    //开户
    bool open_account(std::string stu_ID, std::string name);
    //发卡
    bool issue_card();
    //补卡
    bool reissue_card(Person *);
    //挂失
    bool report_lost(Card *);
    //解挂
    bool remove_lost(Card *);
    //销户
    bool remove_lost(Person *);
    //充值
    bool add_money(int x);






};

#endif // CARDMANAGER_H

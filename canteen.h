#ifndef CANTEEN_H
#define CANTEEN_H
#include "std.h"
#include "cardmanager.h"
#include "logger.h"

extern Logger logger;
typedef struct _record
{
    std::string time, card_ID;
    int canteen_ID, money;
    _record(std::string time, int canteen_ID, std::string card_ID, int money)
    {
        this->time = time;
        this->canteen_ID = canteen_ID;
        this->card_ID = card_ID;
        this->money = money;
    }
} record;



class canteen
{
private:
    CardManager *CM;
    void modify_canteen(record *one);
    void modify_account(Person *, record *);



public:
    std::deque<record *>recordlist[100];
    canteen(CardManager *CM);
    //总消费记录数
    std::vector<int> nums;
    //当天消费金额
    std::vector<int> today_money;
    //当天消费次数
    std::vector<int> today_nums;


    bool consume(record *);
};

#endif // CANTEEN_H

#ifndef CANTEEN_H
#define CANTEEN_H
#include "std.h"
#include "cardmanager.h"
#include "logger.h"

extern Logger logger;

// 定义消费记录
typedef struct _record
{
    // 时间，卡号
    std::string time, card_ID;
    // 窗口号，消费金额
    int canteen_ID, money;
    // 构造函数
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
    // CM
    CardManager *CM;
    // 修改该窗口今日消费情况
    void modify_canteen(record *one);
    // 修改账户时间段累计消费
    void modify_account(Person *, record *);

public:
    // 初始化
    canteen(CardManager *CM);
    // 每个窗口消费记录表
    std::deque<record *> recordlist[100];
    //窗口总消费记录数
    std::vector<int> nums;
    //窗口当天消费金额
    std::vector<int> today_money;
    //窗口当天消费次数
    std::vector<int> today_nums;
    // 消费操作
    bool consume(record *);
};

#endif // CANTEEN_H

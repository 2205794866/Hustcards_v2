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
public:
    std::deque<record *>recordlist[100];
    canteen(CardManager *CM);
    bool consume(record *);
};

#endif // CANTEEN_H

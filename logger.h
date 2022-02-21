#ifndef LOGGER_H
#define LOGGER_H
#include "std.h"


typedef  struct _operation_record
{
    std::string time,stu_ID, name, operation;
    bool succeed;
    _operation_record(std::string time, std::string name, std::string operation, bool succeed)
    {
        this->time = time;
        this->name = name;
        this->operation = operation;
        this->succeed = succeed;
    }
} operation_record;

typedef  struct _consume_record
{
    std::string time, card_ID;
    int canteen_ID, money;
    bool succeed;
    _consume_record(std::string time, std::string card_ID,int canteen_ID,int money, bool succeed)
    {
        this->time = time;
        this->card_ID= card_ID;
        this->canteen_ID = canteen_ID;
        this->money = money;
        this->succeed = succeed;
    }
} consume_record;


class logger
{
public:
    logger();
    bool write_operation_record(operation_record *);
    bool write_consume_record(consume_record *);
    std::queue<operation_record*> operation_list;
    std::queue<consume_record *> consume_list;


private:

};

#endif // LOGGER_H

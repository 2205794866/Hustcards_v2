#ifndef LOGGER_H
#define LOGGER_H
#include "std.h"



typedef  struct _operation_record
{
    std::string time,stu_ID, name, operation;
    bool succeed;
    _operation_record(std::string time, std::string name, std::string stu_ID, std::string operation, bool succeed)
    {
        this->time = time;
        this->name = name;
        this->stu_ID = stu_ID;
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


class Logger
{
public:
    Logger();
    bool write_operation_record(operation_record *);
    bool write_consume_record(consume_record *);
    // std::deque<operation_record*> operation_list;
    // std::deque<consume_record *> consume_list; 
    std::string time;
    ~Logger();
private:
    //操作日志和消费日志文件
    std::fstream afile, bfile;

};

#endif // LOGGER_H

#ifndef LOGGER_H
#define LOGGER_H
#include "std.h"
#include <string.h>


typedef  struct _operation_record
{
    std::string time,stu_ID, name, operation, err_msg;
    bool flag;
    _operation_record(std::string time, std::string name, std::string stu_ID, std::string operation, bool flag, std::string err_msg = "")
    {
        this->time = time;
        this->name = name;
        this->stu_ID = stu_ID;
        this->operation = operation;
        this->flag = flag;
        this->err_msg = err_msg;
    }
} operation_record;

typedef  struct _consume_record
{
    std::string time, card_ID, err_msg;
    int canteen_ID, money, left, check_code;
    bool flag;
    _consume_record(std::string time, std::string card_ID,int canteen_ID, int money,int left, bool flag, std::string err_msg = "")
    {
        this->time = time;
        this->card_ID= card_ID;
        this->canteen_ID = canteen_ID;
        this->money = money;
        this->flag = flag;
        this->err_msg = err_msg;
        this->left = left;

        //获取校验码
         char buff[31];
        // std::vector<int> check_method = {7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2};
        //time 16 canteen_ID 2 card_ID 7 money 5
         sprintf(buff, "%s%02d%s%05d", time.c_str(), canteen_ID, card_ID.c_str(), money);
         check_code = 0;
         for(int i = 0; i<30; i++)
         {
             check_code += (buff[i] - '0');
         }
         check_code %= 10;
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
    // std::fstream afile, bfile;
    FILE *fp1, *fp2;

};

#endif // LOGGER_H

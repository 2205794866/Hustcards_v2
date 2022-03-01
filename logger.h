#ifndef LOGGER_H
#define LOGGER_H
#include "std.h"
#include <string.h>


typedef struct _operation_record
{
    // 时间，学号，姓名，操作，错误信息
    std::string time, stu_ID, name, operation, err_msg;
    // 是否错误
    bool flag;
    _operation_record(std::string time, std::string name, std::string stu_ID, std::string operation, bool flag, std::string err_msg = "")
    {
        //设置基本信息
        this->time = time;
        this->name = name;
        this->stu_ID = stu_ID;
        this->operation = operation;
        this->flag = flag;
        this->err_msg = err_msg;
    }
} operation_record;

typedef struct _consume_record
{
    // 时间，卡号， 错误信息
    std::string time, card_ID, err_msg;
    // 窗口号，消费金额，余额，校验码
    int canteen_ID, money, left, check_code;
    // 是否错误
    bool flag;
    _consume_record(std::string time, std::string card_ID, int canteen_ID, int money, int left, bool flag, std::string err_msg = "")
    {
        //设置基本信息
        this->time = time;
        this->card_ID = card_ID;
        this->canteen_ID = canteen_ID;
        this->money = money;
        this->flag = flag;
        this->err_msg = err_msg;
        this->left = left;

        //获取校验码
        char buff[31];
        std::vector<int> check_method = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
        // time 16 canteen_ID 2 card_ID 7 money 5
        sprintf(buff, "%s%02d%s%05d", time.c_str(), canteen_ID, card_ID.c_str(), money);
        check_code = 0;
        for (int i = 0; i < 30; i++)
        {
            check_code += (buff[i] - '0');
        }
        check_code %= 10;
    }
} consume_record;

class Logger
{
public:
    // 日志列表
    // std::deque<operation_record*> operation_list;
    // std::deque<consume_record *> consume_list;

    //日志
    Logger();
    //写入操作日志
    bool write_operation_record(operation_record *);
    //写入消费日志
    bool write_consume_record(consume_record *); 
    //获取时间
    std::string get_time();
    //设置时间
    bool set_time(std::string time);

    ~Logger();

private:
    //操作日志和消费日志文件
    // std::fstream afile, bfile;
    // 操作日志和消费日志文件
    FILE *fp1, *fp2;
    // 文件校验码
    int file_check;
    //时间
    std::string time;
};

#endif // LOGGER_H

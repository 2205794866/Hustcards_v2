#include "logger.h"

Logger::Logger()
{
    this->time = "2021090300000000";
}

bool Logger::write_operation_record(operation_record *one)
{
    this->operation_list.push_back(one);
    return true;
}

bool Logger::write_consume_record(consume_record *one)
{
    this->consume_list.push_back(one);
    return true;
}

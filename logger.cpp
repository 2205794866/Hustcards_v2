#include "logger.h"

logger::logger()
{

}

bool logger::write_operation_record(operation_record *one)
{
    this->operation_list.push(one);
    return true;
}

bool logger::write_consume_record(consume_record *one)
{
    this->consume_list.push(one);
    return true;
}

#include "canteen.h"

canteen::canteen(CardManager *CM)
{
    this->CM = CM;
}

bool canteen::consume(record *one)
{
    bool flag = CM->consume(one->card_ID, one->money);
    if(flag == true)
    {
        this->recordlist[one->canteen_ID].push_back(one);
    }
    logger.consume_list.push_back(new consume_record(one->time, one->card_ID, one->canteen_ID, one->money, flag));
    return flag;
}

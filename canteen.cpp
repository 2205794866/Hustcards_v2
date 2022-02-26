#include "canteen.h"

canteen::canteen(CardManager *CM)
{
    this->CM = CM;
}

bool canteen::consume(record *one)
{
    // bool flag = CM->consume(one->card_ID, one->money);
    // if(flag == true)
    // {
    //     this->recordlist[one->canteen_ID].push_back(one);
    // }
    // logger.consume_list.push_back(new consume_record(one->time, one->card_ID, one->canteen_ID, one->money, flag));
    // return flag;
    bool flag;
    //查找卡号是否存在
    auto iter = this->CM->Map_CIDtoCard.find(one->card_ID);
    if(iter == this->CM->Map_CIDtoCard.end()) //若不存在
        flag = false;
    else
    {
        //若存在
        Card *card = iter->second;
        Person *owner = card->owner;
        //判断账户是否有效
        if(owner->is_valid() == false || card->is_valid() == false)
        {
            flag = false;
        }
        else
        {
            //消费
            flag = owner->consume(one->money);
            if(flag == true) //若成功，则写入
                this->recordlist[one->canteen_ID].push_back(one);
        }
        //写入日志
        logger.write_consume_record(new consume_record(one->time, one->card_ID, one->canteen_ID, one->money, flag));
    }
    return flag;
}

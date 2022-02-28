#include "canteen.h"

canteen::canteen(CardManager *CM)
{
    this->CM = CM;
    nums.assign(100, 0);
}

bool canteen::consume(record *one)
{
    bool flag;
    std::string err_msg;
    //查找卡号是否存在
    auto iter = this->CM->Map_CIDtoCard.find(one->card_ID);
    if(iter == this->CM->Map_CIDtoCard.end()) //若不存在
    {
        flag = false;
        err_msg = "卡号不存在";
        logger.write_consume_record(new consume_record(one->time, one->card_ID, one->canteen_ID, one->money , 0, flag, err_msg));
    }
    else
    {
        //若存在
        Card *card = iter->second;
        Person *owner = card->owner;
        //判断账户是否有效
        if(owner->is_valid() == false || card->is_valid() == false)
        {
            flag = false;
            if(owner->is_valid() == false)
            {
                err_msg = "账户失效";
            }
            else
            {
                err_msg = "卡失效";
            }
        }
        else
        {
            //消费
            flag = owner->consume(one->money);
            if(flag == true) //若成功，则写入
            {
                if(recordlist[one->canteen_ID].size() == 60000)
                {
                    this->recordlist[one->canteen_ID].pop_front();
                }
                this->recordlist[one->canteen_ID].push_back(one);
                owner->record_list.push_back(one);
                this->nums[one->canteen_ID] ++;
            }
            else
            {
                err_msg = "余额不足";
            }
        }
        //写入日志
        logger.write_consume_record(new consume_record(one->time, one->card_ID, one->canteen_ID, one->money , owner->get_money(), flag, err_msg));
    }  
    return flag;
}

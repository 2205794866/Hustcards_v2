#include "canteen.h"

canteen::canteen(CardManager *CM)
{
    this->CM = CM;
    nums.assign(100, 0);
    today_money.assign(100, 0);
    today_nums.assign(100, 0);
}

void canteen::modify_canteen(record *one)
{
    if(!recordlist[one->canteen_ID].empty() && recordlist[one->canteen_ID].back() != nullptr)
    {
        if(one->time.substr(0, 8) == recordlist[one->canteen_ID].back()->time.substr(0, 8))
        {
            today_money[one->canteen_ID] += one->money;
            today_nums[one->canteen_ID] += 1;
        }
        else
        {
            today_money[one->canteen_ID] = one->money;
            today_nums[one->canteen_ID] = 1;
        }
    }
    else
    {
        today_money[one->canteen_ID] = one->money;
        today_nums[one->canteen_ID] = 1;
    }
}

void canteen::modify_account(Person *owner, record *now)
{
    // std::string str1 = "07", str2 = "09", str3 = "11", str4 = "13", str5="17", str6 = "19";
    std::vector<std::string> str_list = {"07","09", "11", "13","17","19"};
    if(!owner->record_list.empty())
    {
        record *current = owner->record_list.back();
        if(current->time.substr(0, 8) == now->time.substr(0, 8))
        {
            std::string now_hour = now->time.substr(8,2);
            std::string current_hour = current->time.substr(8,2);
            int i=1, j=1;
            while(i<=5 && now_hour >= str_list[i] )
            i+=2;
            while(j<=5 && current_hour >= str_list[j])
            j+=2;
            if(i < 7 && now_hour >= str_list[i-1] && current_hour > str_list[i-1])
            {
                if(i == j)
                {
                    owner->today_money += now->money;
                }
                else
                {
                    owner->today_money = now->money;
                }
            }
            else
            {
                owner->today_money = now->money;
            }
        }
        else
        {
            owner->today_money = now->money;
        }
    }
    else
    {
        owner->today_money = now->money;
    }
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
                modify_canteen(one);
                modify_account(owner, one);
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

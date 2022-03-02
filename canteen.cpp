#include "canteen.h"
// 初始化
canteen::canteen(CardManager *CM)
{
    this->CM = CM;
    // 窗口消费记录数初始为0
    nums.assign(100, 0);
    // 窗口今日消费金额为0
    today_money.assign(100, 0);
    // 窗口今日消费数为0
    today_nums.assign(100, 0);

}

void canteen::modify_canteen(record *one)
{
    // 判断窗口消费记录是否为空，且上一条是否有效
    // 比较本次与上一次消费时间，即可累计
    if(!recordlist[one->canteen_ID].empty() && recordlist[one->canteen_ID].back() != nullptr)
    {
        // 获取本窗口本次与上次消费日期
        if(one->time.substr(0, 8) == recordlist[one->canteen_ID].back()->time.substr(0, 8))
        // 若本次与上次消费日期想通，则累计
        {
            today_money[one->canteen_ID] += one->money;
            today_nums[one->canteen_ID] += 1;
            return ;
        }
    }
    // 否则情况并初始化
    today_money[one->canteen_ID] = one->money;
    today_nums[one->canteen_ID] = 1;
    return ;

}

void canteen::modify_account(Person *owner, record *now)
{
    // 时间点
    std::vector<std::string> str_list = {"07","09", "11", "13","17","19"};
    // 判断该账户消费记录是否为空
    if(!owner->record_list.empty())
    {
        // 获取上一次消费记录
        record *current = owner->record_list.back();
        // 判断本次与上一次日期是否相投
        if(current->time.substr(0, 8) == now->time.substr(0, 8))
        {
            // 获取本次与上一次hour是否相同
            std::string now_hour = now->time.substr(8,2);
            std::string current_hour = current->time.substr(8,2);
            // 获取消费时间段
            int i=1, j=1;
            while(i<=5 && now_hour >= str_list[i] )
            i+=2;
            while(j<=5 && current_hour >= str_list[j])
            j+=2;
            // 判断是否在规定时间段内消费
            if(i < 7 && now_hour >= str_list[i-1] && current_hour >= str_list[i-1])
            {
                if(i == j)
                // 若在同一消费时间段，金额累积
                {
                    owner->today_money += now->money;
                    return ;
                }
            }
        }
    }
    // 否则金额清空
    owner->today_money = now->money;
    return;
}




bool canteen::consume(record *one)
{
    // 初始化
    bool flag;
    std::string err_msg;
    //查找卡号是否存在
    auto iter = this->CM->Map_CIDtoCard.find(one->card_ID);
    if(iter == this->CM->Map_CIDtoCard.end())
    // 若不存在
    {
        // 写日志
        flag = false;
        err_msg = "卡号不存在";
        logger.write_consume_record(new consume_record(one->time, one->card_ID, one->canteen_ID, one->money , 0, flag, err_msg));
    }
    else
    {
        //若存在
        Card *card = iter->second;
        Person *owner = card->owner;
        //判断账户和卡是否有效
        if(owner->is_valid() == false || card->is_valid() == false)
        // 若失效
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
            // 消费
            flag = owner->consume(one->money);
            if(flag == true)
            // 若消费成功，则写入 
            {
                // 判断窗口记录数是否超过60000
                if(recordlist[one->canteen_ID].size() == 60000)
                {
                    this->recordlist[one->canteen_ID].pop_front();
                }
                // 窗口记录数++
                this->nums[one->canteen_ID] ++;
                // 修改窗口当天消费信息
                modify_canteen(one);
                // 修改账户当前时间段消费信息
                modify_account(owner, one);
                // 窗口消费记录添加
                this->recordlist[one->canteen_ID].push_back(one);
                // 账户消费记录添加
                owner->record_list.push_back(one);
            }
            else
            {
                // 写入错误信息
                err_msg = "余额不足";
            }
        }
        //写入日志
        logger.write_consume_record(new consume_record(one->time, one->card_ID, one->canteen_ID, one->money , owner->get_money(), flag, err_msg));
    }  
    return flag;
}

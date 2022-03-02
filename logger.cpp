#include "logger.h"

Logger::Logger()
{
    // afile.open("d:\\Study\\Project\\Hustcards_v2\\Data\\v4\\log\\oper_log.txt", std::ios::out);
    // bfile.open("d:\\Study\\Project\\Hustcards_v2\\Data\\v4\\log\\cons_log.txt", std::ios::out);

    // 初始化时间
    this->time = "2021090100000000";
    // 日志数
    nums = 0;
    // 初始化文件校验码
    file_check = 0;
    // 打开文件
    fp1 = fopen("d:\\Study\\Project\\Hustcards_v2\\Data\\v4\\log\\oper_log.txt", "w");
    fp2 = fopen("d:\\Study\\Project\\Hustcards_v2\\Data\\v4\\log\\cons_log.txt", "w");
}

// 修改时间
bool Logger::set_time(std::string time)
{
    //判断时间是否合规
    if (time.length() != 16)
    {
        return false;
    }
    //判断时间是否倒退
    else if (time <= this->time)
    {
        return false;
    }
    //设置时间
    else
    {
        this->time = time;
        return true;
    }
}

std::string Logger::get_time()
{
    return this->time;
}

bool Logger::write_operation_record(operation_record *one)
{
    // 内存中存储
    // this->operation_list.push_back(one);

    //文件中存储
    // 使用 ofstream takes 26s
    // afile << one->time << " " << one->stu_ID << " " << one->name << " " << one->operation << " " << flag << " " << one->err_msg << std::endl;
    // 使用fwrite takes 3.9s
    // fwrite(info, strlen(info), 1, fp1);

    // 使用fprintf takes 7.8s
    // fprintf(fp1, "%s %s %s %s %s %s\n", one->time.c_str(), one->stu_ID.c_str(), one->name.c_str(), one->operation.c_str(), flag.c_str(), one->err_msg.c_str());

    // 使用fputs takes 4.1s
    std::string flag = one->flag == true ? "成功" : "失败";
    char info[120];
    sprintf(info, "%s %s %s %s %s %s\n", one->time.c_str(), one->stu_ID.c_str(), one->name.c_str(), one->operation.c_str(), flag.c_str(), one->err_msg.c_str());
    fputs(info, fp1);
    return true;
}

bool Logger::write_consume_record(consume_record *one)
{
    // 内存中写日志
    // this->consume_list.push_back(one);

    // 文件中写日志
    // char money[30], canteen_ID[20], left[30];
    // 使用ofstream
    // sprintf(money, "%d.%02d", one->money / 100, one->money % 100);
    // sprintf(left, "%d.%02d", one->left / 100, one->left % 100);
    // sprintf(canteen_ID, "%2d", one->canteen_ID);
    // bfile << one->time << " " << canteen_ID << " " << one->card_ID << " " << "消费:" << money << " 余额:" << left << " " << flag << " " << one->err_msg << std::endl;
    // 使用fwrite(info, strlen(info), 1, fp2);
    // fprintf(fp2, "%s %2d %s 消费:%d.%02d 余额%d.%02d %s %s\n", one->time.c_str(), one->canteen_ID, one->card_ID.c_str(), one->money/100, one->money%100, one->left/100, one->left%100, flag.c_str(), one->err_msg.c_str());

    // 使用fputs
    std::string flag = one->flag == true ? "成功" : "失败";
    char info[140];
    // 修改文件校验码
    file_check += one->check_code;
    file_check = file_check * 101 % 100;
    // 写入日志
    sprintf(info, "%s %2d %s 消费:%d.%02d 余额%d.%02d %s %s 数据校验码:%d 文件校验码:%d\n", one->time.c_str(), one->canteen_ID, one->card_ID.c_str(), one->money / 100, one->money % 100, one->left / 100, one->left % 100, flag.c_str(), one->err_msg.c_str(), one->check_code, file_check);
    fputs(info, fp2);
    nums++;
    return true;
}

Logger::~Logger()
{
    // afile.close();
    // bfile.close();

    char end_check[100];
    sprintf(end_check, "end 校验码:%d", nums * file_check %100);
    fputs(end_check, fp2);
    //关闭文件
    fclose(fp1);
    fclose(fp2);
}

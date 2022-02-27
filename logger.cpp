#include "logger.h"

Logger::Logger()
{
    this->time = "2021090100000000";
    // afile.open("d:\\Study\\Project\\Hustcards_v2\\Data\\v4\\log\\oper_log.txt", std::ios::out);
    // bfile.open("d:\\Study\\Project\\Hustcards_v2\\Data\\v4\\log\\cons_log.txt", std::ios::out);
    fp1 = fopen("d:\\Study\\Project\\Hustcards_v2\\Data\\v4\\log\\oper_log.txt", "w");
    fp2 = fopen("d:\\Study\\Project\\Hustcards_v2\\Data\\v4\\log\\cons_log.txt", "w");
}

bool Logger::write_operation_record(operation_record *one)
{
    // this->operation_list.push_back(one);
    std::string flag = one->flag == true ? "成功" : "失败";
    // ofstream takes 26s
//    afile << one->time << " " << one->stu_ID << " " << one->name << " " << one->operation << " " << flag << " " << one->err_msg << std::endl;
    char info[120];
    sprintf(info,"%s %s %s %s %s %s\n", one->time.c_str(), one->stu_ID.c_str(), one->name.c_str(), one->operation.c_str(), flag.c_str(), one->err_msg.c_str());
    // fwrite takes 3.9s
    // fwrite(info, strlen(info), 1, fp1);
    // fprintf takes 7.8s
    // fprintf(fp1, "%s %s %s %s %s %s\n", one->time.c_str(), one->stu_ID.c_str(), one->name.c_str(), one->operation.c_str(), flag.c_str(), one->err_msg.c_str());
    // fputs takes 4.1s
    fputs(info, fp1);
    return true;
}

bool Logger::write_consume_record(consume_record *one)
{
    // this->consume_list.push_back(one);
    // char money[30], canteen_ID[20], left[30];
    std::string flag = one->flag == true ? "成功" : "失败";
    // sprintf(money, "%d.%02d", one->money / 100, one->money % 100);
    // sprintf(left, "%d.%02d", one->left / 100, one->left % 100);
    // sprintf(canteen_ID, "%2d", one->canteen_ID);
//    bfile << one->time << " " << canteen_ID << " " << one->card_ID << " " << "消费:" << money << " 余额:" << left << " " << flag << " " << one->err_msg << std::endl;
    char info[120];
    sprintf(info,"%s %2d %s 消费:%d.%02d 余额%d.%02d %s %s\n", one->time.c_str(), one->canteen_ID, one->card_ID.c_str(), one->money/100, one->money%100, one->left/100, one->left%100, flag.c_str(), one->err_msg.c_str());
    // fwrite(info, strlen(info), 1, fp2);
    // fprintf(fp2, "%s %2d %s 消费:%d.%02d 余额%d.%02d %s %s\n", one->time.c_str(), one->canteen_ID, one->card_ID.c_str(), one->money/100, one->money%100, one->left/100, one->left%100, flag.c_str(), one->err_msg.c_str());
    fputs(info, fp2);
    return true;
}

Logger::~Logger()
{
    // afile.close();
    // bfile.close();
    fclose(fp1);
    fclose(fp2);
}

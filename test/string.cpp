#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <regex>
#include <unordered_map>
#include <unordered_set>
using namespace std;

bool cmp(std::string str1, std::string str2)
{
    bool flag = str1 < str2;
    return flag;
}


int main()
{   
    // std::string str1 = "2021092307001588";
    // std::string str2 = "2021092307001464";
    // cout << (str1 < str2) << endl;
    // cout << cmp("2021092307001588", "2021092307001464") << endl;
    std::vector<std::string> str_list = {"07", "09", "11", "13", "17", "19"};
    // std::string now = "2021092307001588";
    char buff[31];
    std::string time = "2021092307001589", card_ID = "3123460";
    int canteen_ID = 3;
    int money = 300;
    sprintf(buff, "%s%02d%s%05d", time.c_str(), canteen_ID, card_ID.c_str(), money);
    int check_code = 0;
    for(int i = 0; i<30; i++)
    {
        check_code += (buff[i] - '0');
    }
    check_code %= 10;

    std::cout << buff << std::endl;
    std::cout << check_code << std::endl;
    return 0;
}
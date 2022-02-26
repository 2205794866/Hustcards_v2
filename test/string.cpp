#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
using namespace std;


int main()
{
    // std::string str = "3133351,20211002,18362314,11.00;";
    // std::string card_ID;
    // std::string tm = "";
    // std::string str_money;
    // int money = 0;
    // card_ID = str.substr(0, str.find(","));
    // str = str.substr(str.find(",") + 1);
    // tm += str.substr(0, str.find(","));
    // str = str.substr(str.find(",") + 1);
    // tm += str.substr(0, str.find(","));
    // str = str.substr(str.find(",") + 1);
    // str_money = str.substr(0, str.find(";"));
    // str_money.erase(str_money.find("."), 1);
    // money = std::stoi(str_money);
    // std::cout << tm << " " << card_ID << " "<< money << std::endl;
    int ID = 1;
    char canteen[20];
    sprintf(canteen, "%2d", ID);
    cout << canteen << endl;
    return 0;
}
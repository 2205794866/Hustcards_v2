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
    std::string str1 = "2021092307001588";
    std::string str2 = "2021092307001464";
    cout << (str1 < str2) << endl;
    cout << cmp("2021092307001588", "2021092307001464") << endl;
}
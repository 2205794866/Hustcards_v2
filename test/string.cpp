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
    std::string tm, func, stu_ID;
    std::string str = "2021090308311439,guashi,2020550050;";
    tm = str.substr(0, str.find(","));
    str = str.substr(str.find(",") + 1);
    func = str.substr(0, str.find(","));
    str = str.substr(str.find(",")+ 1);
    stu_ID = str.substr(0, str.find(";"));
    std::cout << tm << func << stu_ID;
    return 0;
}
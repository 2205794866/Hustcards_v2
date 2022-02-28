#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <time.h>
using namespace std;


int main()
{
    // vector<int> a;
    // a.push_back(0);
    // a.push_back(1);
    // a.push_back(2);
    // int num = a.size();
    // for(int i = 0; i<num; i++)
    // {
    //     cout << *a.begin() << endl;
    //     a.erase(a.begin());
    // }
    std::vector<int> a;
    std::queue<int> b;
    
    for(int i = 0; i<100000; i++)
    {
        a.push_back(i);
        b.push(i);
    }
    clock_t start1 = clock();
    for(int i =0; i<100000; i++)
    {
        a.erase(a.begin());
    }
    std::cout << (double)(clock() - start1)/CLOCKS_PER_SEC << std::endl;
    clock_t start2 = clock();
    for(int i =0; i<100000; i++)
    {
        b.pop();
    }
    std::cout << (double)(clock() - start2)/CLOCKS_PER_SEC << std::endl;


    return 0;
}
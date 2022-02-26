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
    vector<int> a;
    a.push_back(0);
    a.push_back(1);
    a.push_back(2);
    int num = a.size();
    for(int i = 0; i<num; i++)
    {
        cout << *a.begin() << endl;
        a.erase(a.begin());
    }
    return 0;
}
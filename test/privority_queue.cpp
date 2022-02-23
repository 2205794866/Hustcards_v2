#include <queue>

#include <iostream>

int main()
{
    std::priority_queue<int> data;
    data.push(1);
    data.push(3);
    data.push(2);
    std::cout << data.top() << std::endl;
    data.pop();
    std::cout << data.top() << std::endl;
    return 0;
}
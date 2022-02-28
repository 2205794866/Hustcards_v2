#include "analyser.h"

Analyser::Analyser(CardManager *CM, canteen *CT)
{
    this->CM = CM;
    this->CT = CT;
}


void Analyser::summary()
{
    clock_t start = clock();
    std::vector<record *> total;
    std::vector<unsigned int> front(100, 0);
    my_queue que;
    total.reserve(1500000);
    for(int i = 1; i<100; i++)
    {
        while(front[i] < CT->recordlist[i].size() && CT->recordlist[i][front[i]] == nullptr)
        {
            front[i]++;
        }
    }
    for(int i = 1; i<100; i++)
    {
        if(front[i] < CT->recordlist[i].size())
        {
            que.push(CT->recordlist[i][front[i]]);
            front[i] ++;
        }
    }
    while (!que.empty())
    {
        /* code */
        record *one = que.top();
        que.pop();
        total.push_back(one);
        int canteen_ID = one->canteen_ID;
        if(front[canteen_ID] < CT->recordlist[canteen_ID].size())
        {
            que.push(CT->recordlist[canteen_ID][front[canteen_ID]]);
            front[canteen_ID] ++;
        }
    }
    FILE *fp = fopen("D:\\Study\\Project\\Hustcards_v2\\Data\\v4\\log\\summary.txt", "w");
    for(auto iter: total)
    {
        char buff[100];
        sprintf(buff, "%s %2d 卡号:%s 消费:%d.%02d\n", iter->time.c_str(), iter->canteen_ID, iter->card_ID.c_str(), iter->money/100, iter->money%100);
        fputs(buff, fp);
    }
    fclose(fp);
    std::cout << "summary takes: " << (double)(clock() - start) /CLOCKS_PER_SEC << std::endl;;

}

#include "analyser.h"

Analyser::Analyser(CardManager *CM, canteen *CT)
{
    this->CM = CM;
    this->CT = CT;
}


bool cmp(record *a, record *b)
{
    return a->time < b->time;
}


void quickSort(int left, int right, std::vector<record *>& total)
{
	if(left >= right)
		return;
	int i, j;
    record* base, *temp;
	i = left, j = right;
	base = total[left];  //取最左边的数为基准数
	while (i < j)
	{
		while (cmp(total[j], base) == false && i < j)
			j--;
		while (cmp(total[i], base) == true && i < j)
			i++;
		if(i < j)
		{
			temp = total[i];
			total[i] = total[j];
			total[j] = temp;
		}
	}
	//基准数归位
	total[left] = total[i];
	total[i] = base;
	quickSort(left, i - 1, total);//递归左边
	quickSort(i + 1, right, total);//递归右边
}


void Analyser::summary()
{
    clock_t start = clock();
    std::vector<unsigned int> front(100, 0);
    total.reserve(1500000);
    for(int i = 1; i<100; i++)
    {
        while(front[i] < CT->recordlist[i].size() && CT->recordlist[i][front[i]] == nullptr)
        {
            front[i]++;
        }
    }
    // 多路归并
    my_queue que;
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

    // for(int i = 1; i<100; i++)
    // {
    //     while(front[i] < CT->recordlist[i].size())
    //     {
    //         total.push_back(CT->recordlist[i][front[i]]);
    //         front[i] ++;
    //     }
    // }
    //sort 
    // sort(total.begin(), total.end(), cmp);
    //quick_sort
    // quickSort(0, total.size() - 1, total);


    FILE *fp = fopen("D:\\Study\\Project\\Hustcards_v2\\Data\\v4\\log\\summary.txt", "w");
    for(auto iter: total)
    {
        char buff[100];
        Person *owner = this->CM->Map_CIDtoCard.find(iter->card_ID)->second->owner;
        sprintf(buff, "%s %2d %s 卡号:%s 消费:%d.%02d\n", iter->time.c_str(), iter->canteen_ID, owner->get_stu_ID().c_str(),iter->card_ID.c_str(), iter->money/100, iter->money%100);
        fputs(buff, fp);
    }
    fclose(fp);
    std::cout << "summary takes: " << (double)(clock() - start) /CLOCKS_PER_SEC << std::endl;;


}


std::vector<std::string> Analyser::get_friends(std::string stu_ID)
{
    std::vector<std::string> friends;
    std::map<std::string, int> get_counts;
    //窗口号+-2, 时间+-4min
    clock_t start = clock();
    std::vector<record *> possibles;
    for(unsigned int i = 0; i < total.size(); i++)
    {
        if(CM->Map_CIDtoCard.find(total[i]->card_ID)->second->owner->get_stu_ID() == stu_ID)
        {
            int j = 0, canteen_ID = total[i]->canteen_ID;
            while(j<=30)
            {
                if(i-j > 0 && abs(total[i- j]->canteen_ID - canteen_ID) <3)
                    possibles.push_back(total[i-j]);
                if(i+j < total.size() && abs(total[i+j]->canteen_ID - canteen_ID) <3)
                    possibles.push_back(total[i+j]);
                j++;
            }
        }
    }
    for(auto iter: possibles)
    {
        std::string ID = CM->Map_CIDtoCard.find(iter->card_ID)->second->owner->get_stu_ID();
        if(get_counts.count(ID) == 0)
        {
            get_counts.insert(std::make_pair(ID, 1));
        }
        else
        {
            get_counts.find(ID)->second++;
            if(get_counts.find(ID)->second == 20)
            friends.push_back(ID);
        }
    }
    // std::cout << get_counts.count("2020030015") << std::endl;
    std::cout << "get_friends takes: " << (double)(clock() - start) /CLOCKS_PER_SEC << std::endl;;
    return friends;
}

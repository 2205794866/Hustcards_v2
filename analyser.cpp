#include "analyser.h"

// 初始化
Analyser::Analyser(CardManager *CM, canteen *CT)
{
    this->CM = CM;
    this->CT = CT;
}

// 比较函数
bool cmp(record *a, record *b)
{
    return a->time < b->time;
}

// 快速排序
void quickSort(int left, int right, std::vector<record *> &total)
{
    if (left >= right)
        return;
    int i, j;
    // 基准数，临时交换变量
    record *base, *temp;
    i = left, j = right;
    // 取最左边的数为基准数
    base = total[left];
    while (i < j)
    {
        while (cmp(total[j], base) == false && i < j)
            j--;
        while (cmp(total[i], base) == true && i < j)
            i++;
        if (i < j)
        // 交换
        {
            temp = total[i];
            total[i] = total[j];
            total[j] = temp;
        }
    }
    // 基准数归位
    total[left] = total[i];
    total[i] = base;
    // 递归左边
    quickSort(left, i - 1, total);
    // 递归右边
    quickSort(i + 1, right, total);
}

void Analyser::summary()
{
    clock_t start = clock();
    // 求每个消费记录第一个不为空的位置
    std::vector<unsigned int> front(100, 0);

    //事先分配空间
    total.reserve(1500000);

    for (int i = 1; i < 100; i++)
    {
        while (front[i] < CT->recordlist[i].size() && CT->recordlist[i][front[i]] == nullptr)
        {
            front[i]++;
        }
    }
    // 多路归并
    my_queue que;
    // 初始化
    for (int i = 1; i < 100; i++)
    {
        if (front[i] < CT->recordlist[i].size())
        {
            que.push(CT->recordlist[i][front[i]]);
            front[i]++;
        }
    }

    // 归并过程
    while (!que.empty())
    {
        /* code */
        // 获取最小的
        record *one = que.top();
        que.pop();

        // push入结果
        total.push_back(one);

        // 查询其来自哪个归并段
        int canteen_ID = one->canteen_ID;

        // 归并段补充
        if (front[canteen_ID] < CT->recordlist[canteen_ID].size())
        {
            que.push(CT->recordlist[canteen_ID][front[canteen_ID]]);
            front[canteen_ID]++;
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
    // sort库函数排序
    // sort(total.begin(), total.end(), cmp);
    // quick_sort排序
    // quickSort(0, total.size() - 1, total);

    // 写入文件
    FILE *fp = fopen("D:\\Study\\Project\\Hustcards_v2\\Data\\v4\\log\\summary.txt", "w");
    for (auto iter : total)
    {
        char buff[100];
        Person *owner = this->CM->Map_CIDtoCard.find(iter->card_ID)->second->owner;
        sprintf(buff, "%s %2d %s 卡号:%s 消费:%d.%02d\n", iter->time.c_str(), iter->canteen_ID, owner->get_stu_ID().c_str(), iter->card_ID.c_str(), iter->money / 100, iter->money % 100);
        fputs(buff, fp);
    }
    fclose(fp);
    // 输出时间
    std::cout << "summary takes: " << (double)(clock() - start) / CLOCKS_PER_SEC << std::endl;
    ;
}

std::vector<std::string> Analyser::get_friends(std::string stu_ID)
{
    // 初始化 朋友数组， 朋友出现频率
    std::vector<std::string> friends;
    std::map<std::string, int> get_counts;
    //窗口号+-2, 记录+-30
    clock_t start = clock();
    std::vector<record *> possibles;

    // 遍历消费记录
    for (unsigned int i = 0; i < total.size(); i++)
    {
        // 查找该学生
        if (CM->Map_CIDtoCard.find(total[i]->card_ID)->second->owner->get_stu_ID() == stu_ID)
        {
            // 获取窗口号
            int j = 0, canteen_ID = total[i]->canteen_ID;

            // 查看前后30条记录
            while (j <= 50)
            {
                // 窗口号 +-2
                if (i - j > 0 && abs(total[i - j]->canteen_ID - canteen_ID) < 3)
                    possibles.push_back(total[i - j]);
                if (i + j < total.size() && abs(total[i + j]->canteen_ID - canteen_ID) < 3)
                    possibles.push_back(total[i + j]);
                j++;
            }
        }
    }

    // 判断朋友出现次数
    // 遍历可能序列
    for (auto iter : possibles)
    {
        // 获取可能序列中人学号
        std::string ID = CM->Map_CIDtoCard.find(iter->card_ID)->second->owner->get_stu_ID();
        // 统计次数
        if (get_counts.count(ID) == 0)
        {
            get_counts.insert(std::make_pair(ID, 1));
        }
        else
        {
            get_counts.find(ID)->second++;
            // 若大于 20次则列入
            if (get_counts.find(ID)->second == 20)
                friends.push_back(ID);
        }
    }
    // debug
    // std::cout << get_counts.count("2020030015") << std::endl;
    std::cout << get_counts.size() << std::endl;
    std::cout << "get_friends takes: " << (double)(clock() - start) / CLOCKS_PER_SEC << std::endl;
    ;
    return friends;
}

bool Analyser::data_detect(std::string file_name)
{
    //    FILE *fp = fopen(file_name.c_str(), "r");
    //    char buff[255];
}

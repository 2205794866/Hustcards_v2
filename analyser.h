#ifndef ANALYSER_H
#define ANALYSER_H
#include "std.h"
#include "cardmanager.h"
#include "canteen.h"
#include "logger.h"

// 自写优先队列
class my_queue
{
private:
    // 小顶堆
    std::vector<record *> heap;

public:
    //
    my_queue()
    {
    }
    // record 的比较函数
    bool cmp(record *a, record *b)
    {
        return a->time > b->time;
    }

    record *top()
    // 获取最小值
    {
        if (!heap.empty())
            //若不空返回队首
            return heap[0];
        else
            //若空则返回空
            return nullptr;
    }

    void push(record *one)
    // push一个元素进入
    {
        if (empty() == true)
        // 若为空则直接进入
        {
            heap.push_back(one);
            return;
        }
        // 若不为空，插入结尾 size++
        heap.push_back(one);
        unsigned int i;
        // 调整至正确位置
        for (i = heap.size() - 1; i > 0 && cmp(heap[(i - 1) / 2], one); i = (i - 1) / 2)
            heap[i] = heap[(i - 1) / 2];
        //
        heap[i] = one;
    }

    bool pop()
    // pop 出队列
    {

        if (empty() == true)
            // 若空返回false
            return false;
        // 获取最后一个
        record *last = heap.back();
        // 出队列
        heap.pop_back();
        // 将最后一个放置根，后调整至正确位置
        unsigned int child, i;
        for (i = 0; i * 2 + 1 < heap.size(); i = child)
        {
            child = 2 * i + 1;
            if (child + 1 < heap.size() && cmp(heap[child], heap[child + 1]))
                // 最小孩子
                child++;
            if (cmp(last, heap[child]))
                heap[i] = heap[child];
            else
                break;
        }
        // 插入正确位置
        heap[i] = last;
        return true;
    }
    // 返回是否为空
    bool empty()
    {
        return heap.empty();
    }
};

extern Logger logger;
class Analyser
{
public:
    //初始化
    Analyser(CardManager *CM, canteen *CT);

    //汇总食堂消费记录
    void summary();

    // 寻找朋友
    std::vector<std::string> get_friends(std::string stu_ID);

    // 数据检测
    bool data_detect(std::string file_name);

private:
    //CM, CT
    CardManager *CM;
    canteen *CT;
    //总消费数据
    std::vector<record *> total;
};

#endif // ANALYSER_H

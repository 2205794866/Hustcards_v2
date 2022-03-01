#ifndef ANALYSER_H
#define ANALYSER_H

#include "std.h"
#include "cardmanager.h"
#include "canteen.h"
#include "logger.h"

class my_queue
{
    private:
        std::vector<record *> heap;
    public:
        my_queue()
        {

        }
        bool cmp(record *a, record *b)
        {
            return a->time > b->time;
        }

        record* top()
        {
            if(!heap.empty())
                return heap[0];
            else
                return nullptr;
        }

        void push(record *one)
        {
            if(empty() == true)
            {
                heap.push_back(one);
                return;
            }
            heap.push_back(one);
            unsigned int i;
            for(i = heap.size() - 1; i > 0 && cmp(heap[(i-1)/2],one); i=(i-1)/2)
                heap[i] = heap[(i-1)/2];
            heap[i] = one;   
        }

        bool pop()
        {
            if(empty() == true)
                return false;
            
            record* last = heap.back();
            heap.pop_back();
            unsigned int child, i;
            for(i = 0; i * 2 + 1<heap.size(); i = child)
            {
                child = 2*i+1;
                if(child+1 < heap.size() && cmp(heap[child], heap[child + 1]))
                    child ++;
                if(cmp(last,heap[child]))
                    heap[i] = heap[child];
                else
                    break;
            }
            heap[i] = last;
            return true;
        }

        bool empty()
        {
            return heap.empty();
        }
};




extern Logger logger;
class Analyser
{
public:
    Analyser(CardManager *CM, canteen *CT);

    //汇总食堂消费记录
    void summary();
    std::vector<std::string> get_friends(std::string stu_ID);
private:
    CardManager *CM;
    canteen *CT;
    std::vector<record *> total;
};

#endif // ANALYSER_H

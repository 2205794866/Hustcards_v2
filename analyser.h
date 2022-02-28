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

        void build()
        {
            int len = heap.size();
            record *temp;
            for(int i = len/2 - 1; i >= 0; i--)
            {
                if((2*i+1) < len && cmp(heap[i], heap[2*i+1]) == true)
                {
                    temp = heap[i];
                    heap[i] = heap[2 * i + 1];
                    heap[2*i+1] = temp;
                    if((2*(2*i+1)+1 < len && cmp(heap[2*i+1],heap[2*(2*i+1)+1]) == true) || (2*(2*i+1)+2 < len && cmp(heap[2*i+1],heap[2*(2*i+1)+2]) == true))
                    {
                        build();
                    }
                }
                if((2*i+2) < len && cmp(heap[i], heap[2*i+2]) == true)
                {
                    temp = heap[i];
                    heap[i] = heap[2*i+2];
                    heap[2*i+2] = temp;
                    if ((2*(2*i+2)+1 < len && cmp(heap[2*i+2], heap[2*(2*i+2)+1]) == true) || (2*(2*i+2)+2 < len && cmp( heap[2*i+2], heap[2*(2*i+2)+2]) == true))
                    {
                        build();
                    }
                }
            }
        }
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

            heap.push_back(one);
            build();
        }

        bool pop()
        {
            if(heap.empty() == false)
            {
                heap[0] = heap.back();
                heap.pop_back();
                build();
                return true;
            }
            else
                return false;          
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

private:
    CardManager *CM;
    canteen *CT;

    

};

#endif // ANALYSER_H

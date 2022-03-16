#ifndef LIMITED_QUEUE_H
#define LIMITED_QUEUE_H
#include "nodes.h"

namespace queue_sized{
class MyQueueSized {

public:
    MyQueueSized(int size)
        : m_maxSize(size)
    {}

    bool push(int);
    RetVal<int> pop();
    RetVal<int> peek();
    int size();
    void runTask();

private:
    const int m_maxSize = 0;
    int m_curSize = 0;
    Node<int>* tail = nullptr;
};

int main();
}

#endif // LIMITED_QUEUE_H

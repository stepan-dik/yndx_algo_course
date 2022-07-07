#include <iostream>
#include "limited_queue.h"
namespace queue_sized {

bool MyQueueSized::push(int value)
{
    if (m_curSize == m_maxSize)
        return false;
    if (tail != nullptr) {
        tail->next = new Node<int>(value, tail->next);
        tail = tail->next;
    }
    else {
        tail = new Node<int>(value, nullptr);
        tail->next = tail;
    }
    ++m_curSize;
    return true;
}

RetVal<int> MyQueueSized::peek()
{
    if (tail == nullptr)
        return RetVal<int>{0, false};
    return RetVal<int>{tail->next->value, true};
}

RetVal<int> MyQueueSized::pop()
{
    if (tail == nullptr)
        return RetVal<int>{0, false};
    auto result = RetVal<int>{tail->next->value, true};
    if (tail == tail->next) {
        delete tail;
        tail = nullptr;
    }
    else {
        auto temp = tail->next;
        tail->next = tail->next->next;
        delete temp;
    }
    --m_curSize;
    return result;
}

int MyQueueSized::size()
{
    return m_curSize;
}

int main()
{
    int cmds = 0;
    std::string command;
    int maxQueueSize = 0;
    std::cin >> cmds;
    std::cin >> maxQueueSize;
    MyQueueSized queue{maxQueueSize};
    int arg;

    for (; cmds > 0; --cmds) {
        std::cin >> command;
        if (command == "push") {
            std::cin >> arg;
            bool res = queue.push(arg);
            if (!res)
                std::cout << "error" << std::endl;
        }
        else if (command == "pop") {
            auto result = queue.pop();
            if (!result.valid)
                std::cout << "None" << std::endl;
            else
                std::cout << result.value << std::endl;
        }
        else if (command == "peek") {
            auto result = queue.peek();
            if (!result.valid)
                std::cout << "None" << std::endl;
            else
                std::cout << result.value << std::endl;
        }
        else {
            std::cout << queue.size() << std::endl;
        }
    }
    return 0;
}

}

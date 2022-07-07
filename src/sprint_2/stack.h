#ifndef STACK_H
#define STACK_H

#include <optional>
#include "nodes.h"

// Basic stack on top of linked list
//using namespace std;
template<typename T>
class Stack {
    Node<T>* head = nullptr;

public:
    void push(T value)
    {
        head = new Node<T>(value, head);
    }

    std::optional<T> pop()
    {
        if (head == nullptr) {
            T temp;
            return {};
        }
        auto result = head->value;
        auto toDelete = head;
        head = head->next;
        delete toDelete;
        return result;
    }

    std::optional<T> peek()
    {
        if (head == nullptr)
            return {};
        return head->value;
    }
};

#endif // STACK_H

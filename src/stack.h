#ifndef STACK_H
#define STACK_H

// Linked list node
template<typename T>
struct Node {
    Node(const int &value, Node* next)
        : value(value)
        , next(next)
    {}
    const T value;
    Node* next = nullptr;
};

// Return value type
template<typename T>
struct RetVal {
    T value;
    bool valid;
};

// Basic stack on top of linked list
template<typename T>
class Stack {
    Node<T>* head = nullptr;

public:
    void push(T value)
    {
        head = new Node<T>(value, head);
    }

    RetVal<T> pop()
    {
        if (head == nullptr) {
            T temp;
            return RetVal<T>{temp, false};
        }
        auto result = RetVal<T>{head->value, true};
        auto toDelete = head;
        head = head->next;
        delete toDelete;
        return result;
    }

    RetVal<T> peek()
    {
        if (head == nullptr)
            return RetVal<T>{0, false};
        return RetVal<T>{head->value, true};
    }
};

#endif // STACK_H

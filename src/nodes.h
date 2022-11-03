#ifndef NODES_H
#define NODES_H
#include <optional>

// Linked list node
template<typename T>
struct Node {
    Node(const T &value, Node* next, Node* prev = nullptr)
        : value(value)
        , next(next)
        , prev(prev)
    {}

    Node() = default;
    const std::optional<T> value;
    Node* next = nullptr;
    Node* prev = nullptr;
};

// Return value type
template<typename T>
struct RetVal {
    T value;
    bool valid;
};

#endif // NODES_H

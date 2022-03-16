#ifndef SOLUTION_H
#define SOLUTION_H

#include <string>
namespace reverse {

struct Node {
    Node(const std::string &value, Node* next, Node* prev = nullptr)
        : value(value)
        , next(next)
        , prev(prev)
    {}
    const std::string value;
    Node* next;
    Node* prev;
};
}
#endif // SOLUTION_H

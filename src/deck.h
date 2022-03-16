#ifndef DECK_H
#define DECK_H
#include "nodes.h"
#include <optional>

class Deck
{
public:
    Deck(int size)
        : m_maxSize(size)
    {
        nodes = new Node<int>[size];
    }

    bool push_back(int);
    bool push_front(int);
    std::optional<int> pop_back();
    std::optional<int> pop_front();

private:
    int m_maxSize;
    int m_curSize = 0;
    Node<int> tail = nullptr;
    Node<int>* nodes = nullptr;
};

#endif // DECK_H

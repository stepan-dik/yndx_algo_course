#include "deque.h"
#include <string>
#include <iostream>

bool Deque::push_back(int value)
{
    if (m_curSize == m_maxSize)
        return false;
    if (tail != nullptr) {
        tail->next = new Node<int>(value, tail->next, tail);
        tail = tail->next;
        tail->next->prev = tail;
    }
    else {
        tail = new Node<int>(value, nullptr);
        tail->next = tail;
        tail->prev = tail;
    }
    ++m_curSize;
    return true;
}

bool Deque::push_front(int value)
{
    if (m_curSize == m_maxSize)
        return false;
    if (tail != nullptr) {
        tail->next = new Node<int>(value, tail->next, tail);
        tail->next->next->prev = tail->next;
    }
    else {
        tail = new Node<int>(value, nullptr);
        tail->next = tail;
        tail->prev = tail;
    }
    ++m_curSize;
    return true;
}

std::optional<int> Deque::pop_back()
{
    if (tail == nullptr)
        return {};
    auto result = tail->value;
    if (tail == tail->next) {
        delete tail;
        tail = nullptr;
    }
    else {
        auto temp = tail;
        tail->prev->next = tail->next;
        tail->next->prev = tail->prev;
        tail = tail->prev;
        delete temp;
    }
    --m_curSize;
    return result;
}

std::optional<int> Deque::pop_front()
{
    if (tail == nullptr)
        return {};
    auto result = tail->next->value;
    if (tail == tail->next) {
        delete tail;
        tail = nullptr;
    }
    else {
        auto temp = tail->next;
        tail->next = tail->next->next;
        tail->next->prev = tail;
        delete temp;
    }
    --m_curSize;
    return result;
}

int main()
{
    int cmds = 0;
    std::string command;
    int maxDeckSize = 0;
    std::cin >> cmds;
    std::cin >> maxDeckSize;
    Deque deck{maxDeckSize};
    int arg;

    for (; cmds > 0; --cmds) {
        std::cin >> command;
        if (command == "push_back") {
            std::cin >> arg;
            bool result = deck.push_back(arg);
            if (!result)
                std::cout << "error" << std::endl;
        }
        else if (command == "push_front") {
            std::cin >> arg;
            auto result = deck.push_front(arg);
            if (!result)
                std::cout << "error" << std::endl;
        }
        else if (command == "pop_back") {
            auto result = deck.pop_back();
            if (!result)
                std::cout << "error" << std::endl;
            else
                std::cout << result.value() << std::endl;
        }
        else {
            auto result = deck.pop_front();
            if (!result)
                std::cout << "error" << std::endl;
            else
                std::cout << result.value() << std::endl;
        }
    }
    return 0;
}

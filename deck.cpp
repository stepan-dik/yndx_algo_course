#include <string>
#include <iostream>
#include <optional>


/*
    --- ПРИНЦИП РАБОТЫ ---
  Дек реализован на двусвязном списке с использованием кольцевого буфера. Дек 
хранит последний элемент, который ссылается на начальный, в нем реализованы 
методы вставки и извлечения с обоих концов.

При любой вставке сначала проверяется, является ли текущий размер максимальным,
если нет - то начинается операция вставки, в противном случае возвращается 
false, что значит, произошла ошибка.

Если дек пустой, то элемент вставляется со ссылками на самого себя.

При вставке элемента в начало ему присваивается ссылка на конечный, как на 
предыдущий, и на следующий для последнего, как на следующий. У последнего 
элемента ссылка на вставляемый элемент задаётся как ссылка на следующий, а у 
того, который был начальным - как на предыдущий.

При вставке элемента в конец происходит аналогичная цепочка присваиваний 
значений ссылок, а после этого новый элемент записывается как последний.

При любом извлечении дек приверяется на наличие в нем элементов, если дек не
пуст, операция продолжается.

При извлечении элемента ссылка на следующий у элемента, который должен был 
быть по отношению к нему предыдущим, будет указывать на элемент после него. 
Таким же образом у элемента, который должен был быть по отношению к 
извлекаемому следующим, ссылка на предыдущий станет указывать на элемент, 
который является предыдущим к извлекаемому. При извлечении с конца, последним
элементом становится тот, что стоял перед ним.


    --- ВРЕМЕННАЯ СЛОЖНОСТЬ ---
Каждая операция занимает константное время O(1). Для N операций, 
соответственно, O(n).


    --- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ ---
Каждая операция вставки требует фиксированное количество дополнительной памяти.
O(n) памяти для N операций.

*/


// Linked list node
template<typename T>
struct Node {
    Node(const int &value, Node* next, Node* prev = nullptr)
        : value(value)
        , next(next)
        , prev(prev)
    {}
    const T value;
    Node* next = nullptr;
    Node* prev = nullptr;
};

class Deck
{
public:
    Deck(int size)
        : m_maxSize(size)
    {} 
    // Не удалось быстро придумать способ работы с заранее выделенным
    // массивом для нод. Навскидку можно выделять массив и параллельно 
    // хранить множество доступных адресов, а сама нода должна будет 
    // хранить свой индекс в массиве.

    bool push_back(int);
    bool push_front(int);
    std::optional<int> pop_back();
    std::optional<int> pop_front();

private:
    int m_maxSize;
    int m_curSize = 0;
    Node<int>* tail = nullptr;
};


bool Deck::push_back(int value)
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

bool Deck::push_front(int value)
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

std::optional<int> Deck::pop_back()
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

std::optional<int> Deck::pop_front()
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
    Deck deck{maxDeckSize};
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
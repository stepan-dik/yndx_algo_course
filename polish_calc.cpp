#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>
#include <unordered_set>



/*
    --- ПРИНЦИП РАБОТЫ ---

  Калькулятор с обратной польской нотацией реализован на стеке, который был 
написан при выполнении предыдущих заданий. Использован алгоритм работы со 
стеком из задания.

"""
Для вычисления значения выражения, записанного в обратной польской нотации, 
нужно считывать выражение слева направо и придерживаться следующих шагов:

    Обработка входного символа:
     - Если на вход подан операнд, он помещается на вершину стека.
     - Если на вход подан знак операции, то эта операция выполняется над
         требуемым количеством значений, взятых из стека в порядке добавления. 
         Результат выполненной операции помещается на вершину стека.

    Если входной набор символов обработан не полностью, перейти к шагу 1.
    После полной обработки входного набора символов результат вычисления 
    выражения находится в вершине стека. Если в стеке осталось несколько чисел,
    то надо вывести только верхний элемент.
"""

    --- ВРЕМЕННАЯ СЛОЖНОСТЬ ---

  Обработка каждого элемента имеет константную сложность O(1), соответственно, 
обработка всех элементов будет иметь линейную сложность O(n).

    --- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ ---

  В худшем случае, когда входные данные будут упорядочены так, что первую 
часть будут составлять все операнды, а вторую - всё операции, пространственная
сложность составит О(n/2) ~ O(n).


*/ 



// Linked list node
template<typename T>
struct Node {
    Node(const T &value, Node* next, Node* prev = nullptr)
        : value(value)
        , next(next)
        , prev(prev)
    {}
    const T value;
    Node* next = nullptr;
    Node* prev = nullptr;
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


int main()
{
    Stack<int> stack;
    std::unordered_set<std::string> operations{"+", "-", "*", "/"};
    std::string input;
    std::getline(std::cin, input);
    std::istringstream iss(input);
    std::vector<std::string> strings(std::istream_iterator<std::string>{iss},
                                     std::istream_iterator<std::string>());
    for (const auto& str: strings) {
        if (operations.find(str) == operations.end()) {
            stack.push(std::stoi(str));
            continue;
        }
        auto right = stack.pop();
        auto left = stack.pop();
        if (str == std::string{"+"})
            stack.push(left.value() + right.value());
        else if (str == std::string{"-"})
            stack.push(left.value() - right.value());
        else if (str == std::string{"*"})
            stack.push(left.value() * right.value());
        else if (str == std::string{"/"}) {
            auto div = std::div(left.value(), right.value());
            auto res = div.rem < 0 ? div.quot - 1 : div.quot;
            stack.push(res);
        }
    }
    std::cout << stack.peek().value() << std::endl;
    return 0;
}
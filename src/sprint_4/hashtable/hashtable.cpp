/*
        --- ПРИНЦИП РАБОТЫ ---
  Хэш-таблица реализована на статическом массиве, так как не
в задании не предполагается масштабирование. Для разрешения коллизий
используется метод цепочек. Для вычисления индекса корзины
используется метод умножения. За значение размера корзины взята
степень двойки, чтобы использовать быструю версию метода умножения.
  При доступе к элементу сначала вычисляется индекс корзины, корзина
проверяется на наличие значения, если таковое отсутствует, то
элемента нет, если же оно есть, то проводится проверка всей цепочки
на предмет элемента с нужным ключом. В случае операции удаления
процесс итерирования останавливается за один элемент до искомого.

        --- ВРЕМЕННАЯ СЛОЖНОСТЬ ---
  Структура данных имеет константную O(1) сложность для всех операций.
В худшем случае, когда элементы будут попадать в одну корзину,
операции будут занимать O(n).

        --- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ ---
  Структура данных имеет пространственную сложность O(n-M) ~ O(n) для
операций вставки. Операция поиска не требует дополнительной памяти
O(1). Операция удаления освобождает дополнительную память.

Посылка 66635394

*/

#include <iostream>
#include <array>
#include <optional>
#include <cmath>

template<typename T>
struct Node {
    Node(const int key, const T &value, Node* next = nullptr)
        : key(key)
        , value(value)
        , next(next)
    {}

    const int key;
    std::optional<T> value;
    Node* next = nullptr;
};

template<typename T>
class Hashtable {

public:
    void insert(const int h, const int val)
    {
        int bucket_index = bucket(h);
        auto cur_node = m_storage[bucket_index];
        if (cur_node == nullptr){
            m_storage[bucket_index] = new Node<T>{h, val};
            return;
        }
        while (cur_node->next != nullptr && cur_node->key != h)
            cur_node = cur_node->next;
        if (cur_node->key == h)
            cur_node->value = val;
        else
            cur_node->next = new Node<T>{h, val};
    }

    void remove(const int h)
    {
        int bucket_index = bucket(h);
        auto cur_node = m_storage[bucket_index];
        if (cur_node == nullptr)
            return;
        else if (cur_node->next == nullptr && cur_node.key == h)
            m_storage[bucket_index] = nullptr;
        while (cur_node->next != nullptr && cur_node->next->key != h)
            cur_node = cur_node->next;
        if (cur_node->next == nullptr)
            return;

        auto tmp = cur_node->next;
        cur_node->next = tmp->next;
        delete tmp;
    }

    std::optional<T> get(const int h) const
    {
        int bucket_index = bucket(h);
        auto cur_node = m_storage[bucket_index];
        if (cur_node == nullptr)
            return {};
        while (cur_node->next != nullptr && cur_node->key != h)
            cur_node = cur_node->next;
        if (cur_node->key != h)
            return {};
        return cur_node->value;
    }

private:
    int bucket(int h) const {
        return ((std::div(h * s, std::pow(2, 32)).rem) >> (32 - p));
    }
    std::array<Node<T>*, 32768> m_storage{nullptr};
    static const long s = 2654435769;
    static const int p = 15;
};

int main()
{
    Hashtable<int> map;
    int cmds = 0;
    std::cin >> cmds;
    std::string command;
    int arg0 = 0;
    int arg1 = 0;

    for (; cmds > 0; --cmds) {
        std::cin >> command;
        if (command == "put") {
            std::cin >> arg0;
            std::cin >> arg1;
            map.insert(arg0, arg1);
        }
        else if (command == "get") {
            std::cin >> arg0;
            auto result = map.get(arg0);
            if (!result)
                std::cout << "None" << std::endl;
            else
                std::cout << result.value() << std::endl;
        }
        else {
            std::cin >> arg0;
            auto result = map.get(arg0);
            if (!result) {
                std::cout << "None" << std::endl;
                continue;
            }
            std::cout << result.value() << std::endl;
            map.remove(arg0);
        }
    }
    return 0;
}

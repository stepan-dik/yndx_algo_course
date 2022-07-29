/*
 *              --- ПРИНЦИП РАБОТЫ ---
 *   При считывании массива каждый следующий элемент добавляется в
 * конец массива кучи, а затем просеивается по ней вверх. Куча
 * организована таким образом, что нулевой элемент фиктивный, а
 * индексы потомков любого элемента могут быть найдены по формулам
 * left = idx * 2, right = idx * 2 + 1 .
 *   Когда считывание массива завершено, данные из него извлекаются.
 * На каждой итерации корень кучи берется за следующее значение,
 * запоминается, меняется местами с последним элементом массива, а
 * затем удаляется. Оказавшийся в корне кучи элемент просеивается
 * вниз. Цикл повторяется до тех пор, пока в массиве не останется
 * только фиктивный элемент.
 *
 *              --- ВРЕМЕННАЯ СЛОЖНОСТЬ ---
 *   Сложность добавления элемента в кучу, как и извлечения,
 * составляет O(log(n)). Так как каждый элемент надо сначала добавить
 * в кучу, а потом извлечь оттуда, сложность составляет O(n*log(n)).
 *
 *              --- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ ---
 *   Пространственная сложность составляет O(n), так как нужен
 * дополнительный массив для хранения кучи.
 *
 */

#include <iostream>
#include <vector>

struct Participant {
    std::string name;
    int tasks_solved = 0;
    int penalty = 0;
};

bool operator<(const Participant& lhs, const Participant& rhs)
{
    if (lhs.tasks_solved != rhs.tasks_solved)
        return lhs.tasks_solved < rhs.tasks_solved;
    else if (lhs.penalty != rhs.penalty)
        return lhs.penalty > rhs.penalty;
    else
        return lhs.name > rhs.name;
}

bool operator>(const Participant& lhs, const Participant& rhs)
{
    return !(lhs < rhs);
}

size_t idx_left_child(size_t idx, std::vector<Participant>& heap) {
    size_t a = idx * 2;
    return a < heap.size() ? a : idx;
}

size_t idx_right_child(size_t idx, std::vector<Participant>& heap) {
    size_t a = idx * 2 + 1;
    return a < heap.size() ? a : idx;
}

size_t parent(size_t idx)
{
    auto a = idx / 2;
    return a ? a : idx;
}

int sift_up(std::vector<Participant>& heap, int idx) {
    while (heap[parent(idx)] < heap[idx]) {
        auto newIdx = parent(idx);
        std::swap(heap[newIdx], heap[idx]);
        idx = newIdx;
    }
    return idx;
}

int sift_down(std::vector<Participant>& heap, int idx) {
    while (heap[idx] < heap[idx_left_child(idx, heap)]
                || heap[idx] < heap[idx_right_child(idx, heap)]) {

        int newIdx = heap[idx_left_child(idx, heap)] >
                     heap[idx_right_child(idx, heap)] ?
                     idx_left_child(idx, heap) :
                     idx_right_child(idx, heap);

        std::swap(heap[idx], heap[newIdx]);
        idx = newIdx;
    }
    return idx;
}

int main()
{
    int tries = 0;
    std::cin >> tries;
    for (;tries-->0;){
        int n = 0;
        std::cin >> n;
        std::vector<Participant> vec(n + 1);
        Participant tmp;
        for (int i = 1; i < n + 1; ++i) {
            std::cin >> tmp.name >> tmp.tasks_solved >> tmp.penalty;
            vec[i] = tmp;
            sift_up(vec, i);
        }

        while (vec.size() > 1) {
            std::cout << vec[1].name << "\n";
            std::swap(vec[1], vec[vec.size()-1]);
            vec.pop_back();
            sift_down(vec, 1);
        }
        std::cout << std::flush;
    }

    return 0;
}

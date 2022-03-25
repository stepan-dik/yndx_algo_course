/*
    --- ПРИНЦИП РАБОТЫ ---
  Принцип работы алгоритма описан в задании. За основу взят алгоритм
быстрой сортировки, также используется опорный элемент, но вместо
создания новых массивов, массив делится на участки, отсортированные
относительно опорного элемента, т.е. с одной стороны находятся все
элементы больше опорного, а с другой -- меньшего. Достигается это с
помощью двух указателей, которые двигаются навстречу друг к другу,
пока элементы, на которые они указываю,  находятся на правильной
стороне участка массива. Когда условие перестаёт соблюдаться для обоих
указателей, элементы меняются местами, а указатели продолжают
двигаться, пока не встретятся. На этом моменте разбиение на участки
окончено. Функция рекурсивно вызывается для обоих участков массива.
Базовым случаем является участок массива длиной менее 3-х элементов.

    --- ВРЕМЕННАЯ СЛОЖНОСТЬ ---
  Алгоритм имеет временную сложность O(n*log(n)). В худшем случае для
отсортированного массива, если опорным элементом всегда будет
выбираться наибольший или наименьший элемент участка массива,
временная сложность составит О(n^2).

    --- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ ---
  Так как на каждом уровне рекурсии требуется константное количество
памяти, пространственная сложность алгоритма составляет O(log(n)).
*/

#include <iostream>
#include <string>
#include <vector>

struct Element {
    std::string name;
    int tasks_solved = 0;
    int penalty = 0;
    int pos = 0;
};

bool operator>(const Element& lhs, const Element& rhs)
{
    if (lhs.tasks_solved != rhs.tasks_solved)
        return lhs.tasks_solved > rhs.tasks_solved;
    else {
        if (lhs.penalty != rhs.penalty)
            return lhs.penalty < rhs.penalty;
        else {
            if (lhs.name != rhs.name)
                return lhs.name < rhs.name;
            else
                return lhs.pos < rhs.pos;
        }
    }
}

void quicksort_inplace(std::vector<Element>& vec, int l_bound, int r_bound)
{
    if (r_bound - l_bound < 2){
        if (r_bound - l_bound == 1 && vec.at(r_bound) > vec.at(l_bound))
            std::swap(vec[r_bound], vec[l_bound]);
        return;
    }
    auto pivot = vec[rand() % (r_bound - l_bound) + l_bound];
    int l_cur = l_bound;
    int r_cur = r_bound;

    while (l_cur <= r_cur){
        while (vec.at(l_cur) > pivot) {
            ++l_cur;
        }
        while (pivot > vec.at(r_cur)) {
            --r_cur;
        }
        if (l_cur >= r_cur)
            break;
        std::swap(vec[l_cur], vec[r_cur]);
    }
    quicksort_inplace(vec, l_bound, r_cur);
    quicksort_inplace(vec, r_cur, r_bound);
}

int main()
{
    int size = 0;
    std::cin >> size;
    std::vector<Element> vec;

    for (int i = 0; i < size; ++i) {
        Element tmp;
        tmp.pos = i;
        std::cin >> tmp.name;
        std::cin >> tmp.tasks_solved;
        std::cin >> tmp.penalty;
        vec.push_back(tmp);
    }

    quicksort_inplace(vec, 0, vec.size() - 1);

    for (const auto& i: vec)
        std::cout << i.name << " " << i.tasks_solved << " "
                  << i.penalty << " " << i.pos << std::endl;

    return 0;
}

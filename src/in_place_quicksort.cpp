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
    if (lhs.tasks_solved > rhs.tasks_solved)
        return true;
    else if (lhs.tasks_solved == rhs.tasks_solved) {
        if (lhs.penalty < rhs.penalty)
            return true;
        else if (lhs.penalty == rhs.penalty){
            if (lhs.name < rhs.name)
                return true;
            else if (lhs.name == rhs.name)
                return lhs.pos < rhs.pos;
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
}

void swap(std::vector<Element>& vec, int l_idx, int r_idx)
{
    Element tmp_el = vec.at(l_idx);
    vec[l_idx] = vec[r_idx];
    vec[r_idx] = tmp_el;
}

void quicksort_inplace(std::vector<Element>& vec, int l_bound, int r_bound)
{
    static int rec{0};
    std::cout << "/--------------------\\" << rec << std::endl;
    rec++;
    if (r_bound - l_bound < 2){
        if (r_bound - l_bound == 1 && vec.at(l_bound) > vec.at(r_bound))
            swap(vec, l_bound, r_bound);
        rec--;
        std::cout << "\\____________________/" << rec << std::endl;
        return;
    }
    int pivot = rand() % (r_bound - l_bound) + l_bound;
    auto piv_el = vec[pivot];
    std::cout << "pivot " << pivot << " val " << vec.at(pivot).tasks_solved << std::endl;
    int l_cur = l_bound;
    int r_cur = r_bound;

    while (l_cur < r_cur){
        while (piv_el > vec.at(l_cur)) {
            ++l_cur;
        }
        while (vec.at(r_cur) > piv_el) {
            --r_cur;
        }
        swap(vec, l_cur, r_cur);
    }

    for (int i = l_bound; i <= r_bound; ++i)
        std::cout << vec[i].tasks_solved << " ";
    std::cout << std::endl;

    std::cout << "[" << l_bound << "] [" << l_cur << "] | [" << r_cur << "] [" << r_bound << "]" << std::endl;
    quicksort_inplace(vec, l_bound, l_cur);
    quicksort_inplace(vec, r_cur, r_bound);
    rec--;
    std::cout << "\\____________________/" << rec << std::endl;
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
    for (int i = vec.size()-1; i >= 0; --i)
        std::cout << vec[i].name << " " << vec[i].tasks_solved << " " << vec[i].penalty
                  << " " << vec[i].pos << std::endl;
    return 0;
}

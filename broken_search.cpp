/*
    --- ПРИНЦИП РАБОТЫ ---
  Принцип работы алгоритма заключается в сведении к случаю бинарного
поиска. Базовые случаи: центральный элемент оказался искомым, искомый 
элемент больше элемента правой границы и меньше элемента левой 
границы (то есть, отсутствует в массиве). Прежде всего после базовых 
случаев проверяется, с какой от центрального элемента стороны массив 
не является отсортированным. Если центральный элемент больше, чем 
каждая из границ, то разрыв находится справа, если меньше -- слева.
Если искомый элемент находится в диапазоне от центрального элемента 
до граничного со стороны без разрыва, то задача сводится к бинарному 
поиску по участку массива. В противном случае, центральный элемент 
определяет границу для следующей итерации.

    --- ВРЕМЕННАЯ СЛОЖНОСТЬ ---
  Алгоритм имеет временную сложность O(log(n)).
  
    --- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ ---
  Алгоритм имеет пространственную сложность O(1).
 
 */

#include "solution.h"
#include <vector>
#include <cassert>

int binary_search(int l_bound, int r_bound, const std::vector<int>& vec, int k){
    int result = -1;
    while (!(l_bound > r_bound || k > vec.at(r_bound) || k < vec.at(l_bound))) {
        int mid = (r_bound + l_bound) / 2;
        int mid_value = vec.at(mid);
        if (k == mid_value)
            return mid;
        if (k > mid_value)
            l_bound = mid + 1;
        else
            r_bound = mid - 1;
    }
    return result;
}

int broken_search(const std::vector<int>& vec, int k) {
    int l_bound = 0;
    int r_bound = vec.size() - 1;
    int result = -1;
    
    while (r_bound >= l_bound) {
        int mid = (r_bound + l_bound)/2;
        int mid_value = vec.at(mid);
        int rb_value = vec.at(r_bound);
        int lb_value = vec.at(l_bound);
        if (k == mid_value) {
            result = mid;
            break;
        }
        else if (k > rb_value && k < lb_value)
            break;
        else if (lb_value < mid_value && mid_value < rb_value) {
            result = binary_search(l_bound, r_bound, vec, k);
            break;
        }
        else if (mid_value <= rb_value) {       // break is on the left
            if (k > mid_value && k <= rb_value) {
                result = binary_search(mid + 1, r_bound, vec, k);
                break;
            } else {
                r_bound = mid - 1;
            }
        } else {                                // break is on the right
            if (k < mid_value && k >= lb_value) {
                result = binary_search(l_bound, mid - 1, vec, k);
                break;
            } else {
                l_bound = mid + 1;
            }
        }
    }
    return result;
}

void test() {
    std::vector<int> arr = {19, 21, 100, 101, 118, 123, 1, 4, 5, 7, 12};
    assert(8 == broken_search(arr, 5));
    assert(3 == broken_search(arr, 101));
    assert(10 == broken_search(arr, 12));
    assert(0 == broken_search(arr, 19));
    assert(-1 == broken_search(arr, 22));
    assert(-1 == broken_search(arr, 2));
    assert(-1 == broken_search(arr, 13));
    assert(-1 == broken_search(arr, 17));
    assert(-1 == broken_search({1}, 4));
}

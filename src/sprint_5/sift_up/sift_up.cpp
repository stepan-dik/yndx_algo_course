#include <iostream>

#include <vector>
#include <cassert>
//#include "solution.h"

size_t parent(size_t idx)
{
    auto a = idx / 2;
    return a ? a : idx;
}

int siftUp(std::vector<int>& heap, int idx) {
    while (heap[parent(idx)] < heap[idx]) {
        auto newIdx = parent(idx);
        std::swap(heap[newIdx], heap[idx]);
        idx = newIdx;
    }
    return idx;
}

void test() {
    std::vector<int> sample = {-1, 12, 6, 8, 3, 15, 7};
    assert(siftUp(sample, 5) == 1);
}

int main()
{
    std::vector<int> vec{0, 101, 100, 90, 89, 70, 30, 50, 99, 11};
    std::cout << siftUp(vec, 8) << std::endl;
    test();
    return 0;
}

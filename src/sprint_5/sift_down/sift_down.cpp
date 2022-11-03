#include <iostream>


#include <vector>
#include <cassert>
//#include "solution.h"

size_t idxLeftChild(size_t idx, std::vector<int>& heap) {
    size_t a = idx * 2;
    return a < heap.size() ? a : idx;
}

size_t idxRightChild(size_t idx, std::vector<int>& heap) {
    size_t a = idx * 2 + 1;
    return a < heap.size() ? a : idx;
}

int siftDown(std::vector<int>& heap, int idx) {    
    while (heap[idx] < heap[idxLeftChild(idx, heap)]
                || heap[idx] < heap[idxRightChild(idx, heap)]) {

        int newIdx = heap[idxLeftChild(idx, heap)] > heap[idxRightChild(idx, heap)] ?
                    idxLeftChild(idx, heap) : idxRightChild(idx, heap);

        std::swap(heap[idx], heap[newIdx]);
        idx = newIdx;
    }
    return idx;
}

void test() {
    std::vector<int> sample = {-1, 12, 1, 8, 3, 4, 7};
    assert(siftDown(sample, 2) == 5);
}

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> heap(n + 1, 0);
    for (int i = 0; i < n; i++) {
        std::cin >> heap[i + 1];
    }
    int m;
    std::cin >> m;
    for (int i = 0; i < m; i++) {
        int idx, delta;
        std::cin >> idx >> delta;
        heap[idx] -= delta;
        for (const auto& j: heap)
            std::cout << j << " ";
        std::cout << std::endl;
        std::cout << siftDown(heap, idx) << "\n";
    }
    for (int i = 0; i < n; i++) {
        std::cout << heap[i + 1] << " ";
    }
    std::cout << std::endl;


    return 0;
}

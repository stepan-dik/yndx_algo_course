#include <vector>
#include <cassert>

using Iterator = std::vector<int>::iterator;
using CIterator = std::vector<int>::const_iterator;

std::vector<int> merge(
    CIterator left_begin, CIterator left_end,
    CIterator right_begin, CIterator right_end) {

    auto lb = left_begin;
    auto rb = right_begin;

    auto s = left_end - left_begin + right_end - right_begin;
    std::vector<int> result(s);

    for (long i = 0; i < s; ++i) {
        if ((*lb < *rb && lb < left_end) || (rb == right_end && lb < left_end)) {
            result[i] = (*lb);
            ++lb;
        }
        else if (rb < right_end) {
            result[i] = (*rb);
            ++rb;
        }
    }
    return result;
}

void merge_sort(Iterator begin, Iterator end) {
    bool sorted = true;
    for (auto b = begin, e = end; b != e; ++b) {
        if (*b > *(b+1) && (b + 1) != e) {
            sorted = false;
            break;
        }
    }
    std::vector<int>::iterator mid = begin + (end-begin)/2;
    if (sorted){
        merge(begin, mid, mid, end);
        return;
    }
    merge_sort(begin, mid);
    merge_sort(mid, end);
    auto res = merge(begin, mid, mid, end);

    int i = 0;
    for (auto b = begin, e = end; b != e; ++b, ++i)
        *b = res[i];
}

void test_merge_sort() {
    std::vector<int> a = {1, 4, 9};
    std::vector<int> b = {2, 10, 11};
    std::vector<int> c = merge(a.cbegin(), a.cend(), b.cbegin(), b.cend());
    std::vector<int> expected = {1, 2, 4, 9, 10, 11};
    assert(c == expected);
    std::vector<int> d = {1, 4, 2, 10, 1, 2};
    std::vector<int> sorted = {1, 1, 2, 2, 4, 10};
    merge_sort(d.begin(), d.end());
    assert(d == sorted);
}

int main(){
    test_merge_sort();
    return 0;
}

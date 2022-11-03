
// find biggest possible number concatenating given numbers

#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// efficient solution
bool cmp(const std::string& left, const std::string& right)
{
    if (right == left)
        return false;
    auto ls = left.size(), rs = right.size();
    auto lengths = std::minmax(ls, rs);

    bool result = false;
    size_t i = 0;
    for (; i < lengths.first; ++i) {
        if (left[i] != right[i]){
            return left[i] > right[i];
        }
    }
    auto longer_str = left.length() == lengths.second ? left : right;
    bool left_longer = left.length() == lengths.second;
    if (i >= lengths.first) {
        bool res_set = false;
        for (;i < longer_str.length(); ++i) {
            if (longer_str[i] == longer_str[i - lengths.first])
                continue;
            result = (longer_str[i] > longer_str[i - lengths.first] && left_longer) ||
                     (longer_str[i] < longer_str[i - lengths.first] && !left_longer);
            res_set = true;
            break;
        }
        if (!res_set) {
            for (size_t j = 0; j < lengths.first; ++j) {
                if (longer_str[j] == longer_str[longer_str.length() - lengths.first])
                    continue;
                result = (longer_str[longer_str.length() - lengths.first] < longer_str[j] && left_longer) ||
                        (longer_str[longer_str.length() - lengths.first] > longer_str[j] && !left_longer);
                break;
            }
        }
    }

    return result;
}

// simple solution
bool cmp2(const std::string& left, const std::string& right)
{
    std::string l(left + right);
    std::string r(right + left);
    return l > r;
}

std::string biggest_num(std::vector<std::string> vec)
{
    auto start = std::chrono::high_resolution_clock::now();
    std::sort(vec.begin(), vec.end(), cmp);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::string res;
    for(const auto& i: vec) {
        std::cout << i << " ";
        res.append(i);
    }
    std::cout << std::endl;
    std::cout << "Duration " << duration.count() << " microseconds" << std::endl;
    return res;
}

int main()
{
    int tests = 0;
    std::cin >> tests;

    for (int i = 0; i < tests; ++i)
    {
        int size = 0;
        std::cin >> size;
        std::vector<std::string> vec(size);

        for (int i = 0; i < size; ++i) {
            std::cin >> vec[i];
        }
        std::string expected;
        std::cin >> expected;
        auto res = biggest_num(vec);
        bool passed = expected == res;
        if (passed) {
            std::cout << "Correct" << std::endl;
            continue;
        }
        std::cout << "Incorrect" << std::endl;
        size_t wsym = 0;
        for(;wsym < expected.length(); ++wsym) {
            std::cout << expected[wsym];
            if (res[wsym] != expected[wsym])
                break;
        }
        std::cout << std::endl;
        for (size_t j = 0; j < wsym; ++j)
            std::cout << " ";
        std::cout << "^" << std::endl;

        for (;wsym < expected.length(); ++wsym)
            std::cout << expected[wsym];
        std::cout << std::endl;
    }


    return 0;
}

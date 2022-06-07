#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

bool cmp(const std::string& left, const std::string& right)
{
//    std::cout << "compare " << left << " and " << right << std::endl;
    if (right == left)
        return false;
    auto ls = left.size(), rs = right.size();
    auto lengths = std::minmax(ls, rs);

//    auto left_c = left[0];
//    auto right_c = right[0];
    bool result = false;
    size_t i = 0;
    for (; i < lengths.first; ++i) {
        if (left[i] != right[i]){
//            std::cout << left[i] << " " << right[i] << "   ";
            return left[i] > right[i];
        }
//        result = (left[i] < left.at(0) && left.length() != lengths.second) ||
//                (left[i] > left.at(0) && left.length() == lengths.second);
    }
    auto longer_str = left.length() == lengths.second ? left : right;
    bool left_longer = left.length() == lengths.second;
    if (i >= lengths.first) {
        std::cout<< "shit " << left << " " << right << " " << i;
        while (i < longer_str.length()) {
            result = (longer_str[i] < longer_str[0] && !left_longer) ||
                    (longer_str[i] >= longer_str[0] && left_longer);
            std::cout << " " << longer_str[i] << " " << longer_str[0] << " ";
            if (longer_str[i] < longer_str[0]){
                std::cout << " brr ";
                break;
            }
            else {
                std::cout << " aoa ";
                ++i;
            }
        }
        std::cout << " res " << result << " | final i " << i << " | Left longer " << left_longer << std::endl;
    }

    return result;
}

std::string biggest_num(std::vector<std::string> vec)
{
    std::sort(vec.begin(), vec.end(), cmp);
    std::string res;
    for(const auto& i: vec) {
        std::cout << i << " ";
        res.append(i);
    }
    std::cout << std::endl;
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
            std::cout << "true" << std::endl;
            continue;
        }
        std::cout << "false" << std::endl;
        int wsym = 0;
        for(;wsym < expected.length(); ++wsym) {
            std::cout << expected[wsym];
            if (res[wsym] != expected[wsym])
                break;
        }
        std::cout << std::endl;
        for (int j = 0; j < wsym; ++j)
            std::cout << " ";
        std::cout << "^" << std::endl;

        for (;wsym < expected.length(); ++wsym)
            std::cout << expected[wsym];
        std::cout << std::endl;
    }


    return 0;
}

// Find median value for 2 arrays

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

// O((n+m)/2)
double find_median(std::vector<int> vec1, std::vector<int> vec2)
{
    auto size = vec1.size() + vec2.size();
    auto needed_index = (vec1.size() + vec2.size())/2;

    auto v1 = vec1.begin();
    auto v2 = vec2.begin();
    auto v1_r = [vec1, vec2] (
            std::vector<int>::const_iterator v1,
            std::vector<int>::const_iterator v2)
    {
        return (*v1 < *v2 && v1 < vec1.end()) ||
               (v2 == vec2.end() && v1 < vec1.end());
    };
    int next = 0;
    int cur = 0;
    for (size_t i = 0; i <= needed_index; ++i) {
        if (i == needed_index-1) {
            cur = v1_r(v1, v2) ? *v1 : *v2;
        }
        else if (i == needed_index) {
            next = v1_r(v1, v2) ? *v1 : *v2;
        }
        if (v1_r(v1, v2))
            ++v1;
        else if (v2 < vec2.end())
            ++v2;
    }

    if (size % 2 != 0) {
        return next;
    }
    return static_cast<double>(cur)/2 + static_cast<double>(next)/2;
}


double find_med(std::vector<int> vec1, std::vector<int> vec2)
{
    auto size = vec1.size() + vec2.size();
    auto distance = std::roundl(static_cast<long double>(vec1.size() + vec2.size())/2);
    auto v1 = vec1.cbegin();
    auto v2 = vec2.cbegin();

    auto v1_r = [vec1, vec2] (
            std::vector<int>::const_iterator v1,
            std::vector<int>::const_iterator v2)
    {
        return ((*v1 < *v2 && v1 < vec1.end()) ||
                (v2 == vec2.end() && v1 < vec1.end()));
    };

    int counter = 100;
    while (distance > 1 && counter) {
        counter--;
        auto prv1 = v1;
        auto prv2 = v2;
        v1 = v1 + std::roundl(distance/2);
        v2 = v2 + std::roundl(distance/2);

        if(v1 == vec1.cend())
            v1--;
        else if(v2 == vec2.cend())
            v2--;

        if (v1_r(v1, v2)) {
            v2 = prv2;
            distance -= v1 - prv1;
            std::cout << " v1 d" << v1 - prv1 << " ";
        } else {
            v1 = prv1;
            distance -= v2 - prv2;
            std::cout << " v2 d" << v2 - prv2 << " ";
        }
        std::cout << *v1 << " " << *v2 << " `" << distance << "` || ";
    }
    std::cout << std::endl;
    double res = v1_r(v1,v2) ? *v1 : *v2;
    std::cout << res << std::endl;
    if (size % 2 != 0)
        return res;

    if (v1_r(v1, v2))
        ++v1;
    else if (v2 < vec2.end())
        ++v2;

    double next = v1_r(v1, v2) ? *v1 : *v2;
    std::cout << next << std::endl;
    return static_cast<double>(res)/2 + static_cast<double>(next)/2;
}

int main()
{
    int tries = 0;
    std::cin >> tries;
    for (; tries-->0;){
        size_t size1 = 0;
        size_t size2 = 0;
        std::cin >> size1 >> size2;

        std::vector<int> vec1(size1);
        std::vector<int> vec2(size2);

        for (size_t i = 0; i < size1; ++i)
            std::cin >> vec1[i];
        for (size_t i = 0; i < size2; ++i)
            std::cin >> vec2[i];

        std::cout << find_med(vec1, vec2) << std::endl;
    }
}

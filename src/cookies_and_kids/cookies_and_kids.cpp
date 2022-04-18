// Find the largest number of element pairs where array1[i] >= array2[j] where
// i and j can only be used once

#include <iostream>
#include <vector>
#include <algorithm>

int count_satisfied_kids(std::vector<int> kids, std::vector<int> cookies)
{
    std::sort(kids.begin(), kids.end());
    std::sort(cookies.begin(), cookies.end());

    int counter = 0;
    for (int i = 0, j = 0; i < kids.size() && j < cookies.size(); ++i) {
        for (; j < cookies.size(); ++j) {
            if (kids[i] <= cookies[j]) {
                ++counter;
                ++j;
                break;
            }
        }
    }

    return counter;
}

int main()
{
    int kids_num;
    int cookies_num;
    std::cin >> kids_num;
    std::vector<int> kids(kids_num, 0);

    for (int i = 0; i < kids_num; ++i) {
        std::cin >> kids[i];
    }

    std::cin >> cookies_num;
    std::vector<int> cookies(cookies_num, 0);

    for (int i = 0; i < cookies_num; ++i)
        std::cin >> cookies[i];

    auto res = count_satisfied_kids(kids, cookies);
    std::cout << res << std::endl;

    return 0;
}

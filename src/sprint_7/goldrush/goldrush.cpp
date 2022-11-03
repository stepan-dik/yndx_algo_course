#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

long int get_max_value(const std::vector<std::pair<int, int>>& piles, int m)
{
    long int result = 0;
    for (auto [value, mass]: piles) {
        result += static_cast<long int>(value) * std::min(mass, m);
        m -= std::min(mass, m);
        if (!m)
            break;
    }

    return result;
}

int main()
{
    int m = 0, n = 0;
    std::cin >> m >> n;

    std::vector<std::pair<int, int>> piles(n);
    for (int i = 0; i < n; ++i)
        std::cin >> piles[i].first >> piles[i].second;

    std::sort(piles.begin(), piles.end(), [](auto lhs, auto rhs) {
        if (lhs.first != rhs.first)
            return lhs.first > rhs.first;
        else
            return lhs.second > rhs.second;
    });

    std::cout << get_max_value(piles, m) << std::endl;

    return 0;
}

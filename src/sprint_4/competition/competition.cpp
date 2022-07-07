// Find longest interval where 0 and 1 are even

#include <iostream>
#include <tuple>
#include <unordered_map>

int find_longest_distance(int size)
{
    std::unordered_map<int, std::pair<int, int>> map;

    int cur_res = 0;
    map[0] = {0,0};
    for (int i = 1; i < size + 1; ++i) {
        int r = 0;
        std::cin >> r;
        r ? ++cur_res : --cur_res;

        if (map.find(cur_res) != map.end())
            map[cur_res].second = i;
        else
            map[cur_res] = {i, i};
    }

    int res = 0;
    for (const auto& [key, pair]: map) {
        int n_r = pair.second - pair.first;
        if (n_r > res)
            res = n_r;
    }
    return res;
}

int main()
{
    int tries = 0;
    std::cin >> tries;

    for (;tries-->0;) {
        int size = 0;
        std::cin >> size;
        std::cout << find_longest_distance(size) << std::endl;
    }

    return 0;
}

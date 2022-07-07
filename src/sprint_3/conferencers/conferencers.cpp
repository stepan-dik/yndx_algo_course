
// Sort values by descending quantity in array and output only first `num`
// of them (in ascending order for the same quantity).

#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <map>

void sort(std::vector<int> vec, int num)
{
    std::unordered_map<int, int> stats;
    for (const auto& i: vec)
        stats[i]++;

    std::map<int, std::set<int>> fin_stats;
    for (const auto& i: stats)
        fin_stats[i.second].insert(i.first);

    int count = 0;
    for (auto i = fin_stats.rbegin(); i != fin_stats.rend(); ++i){
        for (const auto j: i->second) {
            if (count == num)
                return;
            ++count;
            std::cout << j << " ";
        }
    }
}

int main()
{
    int tries = 0;
    std::cin >> tries;

    for (; tries > 0; --tries){
        int size = 0;
        std::cin >> size;

        std::vector<int> vec(size);

        for (int i = 0; i < size; ++i)
            std::cin >> vec[i];

        int num = 0;
        std::cin >> num;

        sort(vec, num);
        std::cout << std::endl;
    }
    return 0;
}

// Create an adjacency list from the given edge list

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

int main()
{
    int v = 0;
    int e = 0;
    std::cin >> v >> e;

    std::map<int, std::vector<int>> adj_list;
    for (int i = 1; i < v+1; ++i)
        adj_list[i] = std::vector<int>();
    for (;e-->0;) {
        int start, finish;
        std::cin >> start >> finish;
        adj_list[start].push_back(finish);
    }

    for (auto& [key, list]: adj_list) {
        std::sort(list.begin(), list.end());
        std::cout << list.size() << " ";
        for (const auto& i: list)
            std::cout << i << " ";
        std::cout << "\n";
    }
    std::cout << std::flush;

    return 0;
}

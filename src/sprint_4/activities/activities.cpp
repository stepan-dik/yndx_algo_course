// Print strings from input without duplicates

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

int main()
{
    int num = 0;
    std::string tmp;
    std::getline(std::cin, tmp);
    num = std::stoi(tmp);

    std::unordered_map<std::string, int> map;

    for (int i = 0; i < num; ++i) {
        tmp.clear();
        std::getline(std::cin, tmp);

        if (map.find(tmp) == map.end())
            map[tmp] = i;
    }

    std::vector<std::string> strs(num);
    for (const auto& i: map)
        strs[i.second] = i.first;

    for (const auto& i: strs) {
        if (i.empty())
            continue;
        std::cout << i << std::endl;
    }

    return 0;
}

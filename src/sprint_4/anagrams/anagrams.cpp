// Group input strings so that groups contain anagrams only, output groups by
// line in ascending order

#include <iostream>
#include <unordered_map>
#include <vector>
#include <array>

std::string reduce_to_chars(std::string s)
{
    std::string result;
    std::unordered_map<char, int> map;
    static std::array<char, 26> chars{
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
        'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    for (const auto c: s)
        map[c]++;
    for (const auto c: chars) {
        if (map.find(c) != map.end()){
            result.append(1, c);
            result.append(std::to_string(map[c]));
        }
    }
    return result;
}

int main()
{
    int tries = 0;
    std::cin >> tries;
    int str_num = 0;
    for (;tries-->0;) {
        std::cin >> str_num;
        std::string tmp;
        std::unordered_map<std::string, std::vector<int>> map;
        std::vector<std::string> order;
        for (int i = 0; i < str_num; ++i) {
            std::cin >> tmp;
            auto letters = reduce_to_chars(tmp);
            if (map.find(letters) == map.end())
                order.push_back(letters);
            map[letters].push_back(i);
        }
        for (const auto& s: order) {
            for (const auto& i: map[s]) {
                std::cout << i << " ";
            }
            std::cout << std::endl;
        }
    }

    return 0;
}

// Find longest substring containing unique letters only

#include <iostream>
#include <string>
#include <unordered_map>

int find_longest(std::string s)
{
    unsigned int result = 0;
    size_t cur_pointer = 0;
    size_t start_pointer = 0;
    std::unordered_map<char, size_t> map;

    for (;cur_pointer < s.size(); ++cur_pointer) {
        if (map.find(s[cur_pointer]) == map.end()) {
            if (cur_pointer - start_pointer > result)
                result = cur_pointer - start_pointer;
            map[s[cur_pointer]] = cur_pointer;
            continue;
        }
        if (cur_pointer - start_pointer > result)
            result = cur_pointer - start_pointer;
        start_pointer = std::max(map[s[cur_pointer]] + 1, start_pointer);
        map[s[cur_pointer]] = cur_pointer;
    }
    if (cur_pointer - start_pointer > result)
        result = cur_pointer - start_pointer;

    return result;
}

int main()
{
    int tries = 0;
    std::cin >> tries;
    for (;tries-->0;) {
        std::string s;
        std::cin >> s;
        std::cout << find_longest(s) << std::endl;
    }
    return 0;
}

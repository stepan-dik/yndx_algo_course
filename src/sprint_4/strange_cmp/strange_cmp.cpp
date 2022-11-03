// Find if one string is a Caesar cipher of another

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

bool cmp()
{
    std::unordered_map<char, char> dict;
    std::unordered_set<char> set;

    std::string first;
    std::getline(std::cin, first);
    std::string second;
    std::getline(std::cin, second);

    if (first.size() != second.size())
        return false;

    for (auto i = first.cbegin(), j = second.cbegin(); i < first.end(); ++i, ++j) {
        if (dict.find(*i) == dict.end() && set.find(*j) == set.end()) {
            dict[*i] = *j;
            set.insert(*j);
            continue;
        }
        if (dict[*i] != *j)
            return false;
    }
    return true;
}

int main()
{
    int tries = 0;
    std::string tmp;
    std::getline(std::cin, tmp);
    tries = std::stoi(tmp);

    for (;tries-->0;) {
        std::cout << (cmp() ? "YES" : "NO") << std::endl;
    }

    return 0;
}

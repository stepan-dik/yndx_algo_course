// Find if pattern is a subsequence of a string

#include <iostream>
#include <string>

bool subsequence(const std::string& pattern, const std::string& str)
{
    if (pattern.size() > str.size() || str.empty()) {
        return false;
    }

    int cur_pos = 0;
    for (const auto& c: str) {
        if (cur_pos == pattern.size())
            break;
        if (c == pattern[cur_pos]){
            ++cur_pos;
        }
    }

    return cur_pos == pattern.size();
}

int main()
{
    std::string pattern;
    std::string str;
    std::string expected;
    std::string num;

    std::getline(std::cin, num);
    int n = std::stoi(num);
    for (; n > 0; --n) {
        str.clear();
        pattern.clear();
        expected.clear();
        std::getline(std::cin, pattern);
        std::getline(std::cin, str);
        std::getline(std::cin, expected);

        std::cout << pattern << std::endl;
        bool res = subsequence(pattern, str);
        std::cout << "Result: " << res
                  << ". Is correct " << (std::stoi(expected) == res)
                  << std::endl;
    }

    return 0;
}

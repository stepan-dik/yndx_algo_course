#include <iostream>
#include <string>
#include <vector>

std::vector<int> calc_prefixes(std::string s)
{
    std::vector<int> res(s.size(), 0);
    for (int i = 1; i < res.size(); ++i) {
        int k = res[i-1];
        while (s[k] != s[i] && k != 0)
            k = res[k-1];
        res[i] = k + (s[k] == s[i]);
    }

    return res;
}

int main()
{
    std::string input;
    std::cin >> input;

    auto res = calc_prefixes(input);
    for (const auto& i: res)
        std::cout << i << " ";
    std::cout << std::endl;

    return 0;
}

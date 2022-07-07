#include <iostream>
#include <string>
#include <array>
namespace {
int main()
{
    int k = 0;
    std::string str;

    std::cin >> k;
    std::string tp;
    while(getline(std::cin, tp)) {
        str.append(tp);
    }

    int fullK = k*2;
    int result = 0;
    std::array<char, 10> chars{0};

    for (unsigned int i = 0; i < str.length(); ++i) {
        chars[str[i]-'0']++;
    }

    for (const auto c: chars) {
        if (c <= fullK && c > 0)
            ++result;
    }

    std::cout << result;
    return 0;
}
}

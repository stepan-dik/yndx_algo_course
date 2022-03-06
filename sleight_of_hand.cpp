#include <iostream>
#include <string>
#include <array>

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
    std::array<char, 10> chars;
    for (int i = 0; i < 10; ++i) {
        chars[i] = '0' + i;
    }

    for (const auto c: chars) {
        int repeats = 0;
        for (const auto el: str) {
            if (el == c)
                ++repeats;
            if (repeats > fullK)
                break;
        }
        if (repeats <= fullK && repeats > 0)
            ++result;
    }

	std::cout << result;
	return 0;
}

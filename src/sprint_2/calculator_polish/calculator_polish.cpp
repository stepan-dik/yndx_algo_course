#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>
#include <unordered_set>
#include "stack.h"

int main()
{
    Stack<int> stack;
    std::unordered_set<std::string> operations{"+", "-", "*", "/"};
    std::string input;
    std::getline(std::cin, input);
    std::istringstream iss(input);
    std::vector<std::string> strings(std::istream_iterator<std::string>{iss},
                                     std::istream_iterator<std::string>());
    for (const auto& str: strings) {
        if (operations.find(str) == operations.end()) {
            stack.push(std::stoi(str));
            continue;
        }
        auto right = stack.pop();
        auto left = stack.pop();
        if (str == std::string{"+"})
            stack.push(left.value() + right.value());
        else if (str == std::string{"-"})
            stack.push(left.value() - right.value());
        else if (str == std::string{"*"})
            stack.push(left.value() * right.value());
        else if (str == std::string{"/"}) {
            auto div = std::div(left.value(), right.value());
            auto res = div.rem < 0 ? div.quot - 1 : div.quot;
            stack.push(res);
        }
    }
    std::cout << stack.peek().value() << std::endl;
    return 0;
}

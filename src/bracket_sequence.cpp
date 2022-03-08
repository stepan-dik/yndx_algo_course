#include <string>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include "stack.h"

int main()
{
    std::unordered_map<char, char> symbols =
    {
        {')', '('},
        {'}', '{'},
        {']', '['}
    };
    std::string sequence;
    Stack<char> toUnload;
    std::cin >> sequence;
    bool result = true;
    for (const auto& c: sequence) {
        if (symbols.find(c) == symbols.end()) {
            toUnload.push(c);
        }
        else if (toUnload.peek().valid && toUnload.peek().value == symbols[c]) {
            toUnload.pop();
        }
        else {
            result = false;
            break;
        }
    }
    if (toUnload.peek().valid)
        result = false;

    std::cout << (result ? "True" : "False") << std::endl;

    return 0;

}

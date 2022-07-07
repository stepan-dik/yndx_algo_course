#include <iostream>
#include <deque>
#include <array>
#include <string>

std::array<std::string, 8> dict{"abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};

void backtrack_seq(std::string prefix, std::deque<int> to_process)
{
    if (to_process.empty()) {
        for (const auto& c: prefix)
            std::cout << c;
        std::cout << " ";
        return;
    }
    int cur_btn = to_process.front();
    to_process.pop_front();
    for (const auto& c: dict[cur_btn]) {
        backtrack_seq(prefix + c, to_process);
    }
}

int main()
{
    std::string input;
    std::cin >> input;

    std::deque<int> to_process;
    for (const auto& c: input)
        to_process.push_back(c - '0' - 2);
    backtrack_seq("", to_process);
    std::cout << std::endl;

    return 0;
}

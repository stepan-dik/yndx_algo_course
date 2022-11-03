#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include <string>

int main()
{
    std::string input;
    std::getline(std::cin, input);
    std::istringstream iss(input);
    std::vector<std::string> strings(std::istream_iterator<std::string>{iss},
                                     std::istream_iterator<std::string>());
    for (auto it = strings.rbegin(); it < strings.rend(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    return 0;
}

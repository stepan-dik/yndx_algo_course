#include <iostream>
#include <vector>
#include <algorithm>

void sort(std::vector<int> vec)
{
    bool sorted = true;
    int printed = 0;
    while (true) {
        for (size_t i = 0; i < vec.size(); ++i) {
            if (i+1 < vec.size() && vec[i] > vec[i+1]) {
                sorted = false;
                std::swap(vec[i], vec[i+1]);
            }
        }
        if (sorted)
            break;
        for (const auto& i: vec)
            std::cout << i << " ";
        std::cout << std::endl;
        sorted = true;
        printed++;
    }
    if (!printed) {
        for (const auto& i: vec)
            std::cout << i << " ";
    }
}

int main()
{
    int tries = 0;
    std::cin >> tries;

    for (; tries > 0; --tries){
        int size = 0;
        std::cin >> size;

        std::vector<int> vec(size);

        for (int i = 0; i < size; ++i)
            std::cin >> vec[i];

        sort(vec);
        std::cout << std::endl;
    }
    return 0;
}

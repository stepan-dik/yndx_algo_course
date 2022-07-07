/*
    Sort 3 different values
*/

#include <iostream>

int main()
{
    int n;
    std::cin >> n;

    int counter0 = 0;
    int counter1 = 0;
    int counter2 = 0;

    int tmp;

    for (int i = 0; i < n; ++i) {
        std::cin >> tmp;
        if (tmp == 0)
            ++counter0;
        else if (tmp == 1)
            ++counter1;
        else
            ++counter2;
    }

    for (; counter0 > 0; --counter0)
        std::cout << "0 ";

    for (; counter1 > 0; --counter1)
        std::cout << "1 ";

    for (; counter2 > 0; --counter2)
        std::cout << "2 ";
    std::cout << std::endl;

    return 0;
}

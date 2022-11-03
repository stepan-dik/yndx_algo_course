/*
    Find 3 side lengths that make the triangle with largest perimeter
*/

#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    int n = 0;
    std::cin >> n;
    std::vector<int> values(n, 0);

    for (int i = 0; i < n; ++i)
        std::cin >> values[i];

    std::sort(values.rbegin(), values.rend());


    for (int i = 0; i < n - 2; ++i) {
        if (values[i] < values[i+1] + values[i+2]) {
            std::cout << (values[i] + values[i+1] + values[i+2]) << std::endl;
            break;
        }
    }

    return 0;
}

/*
    Find maximum number of elements building up the value of k or less
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    int n = 0, k = 0;
    std::cin >> n >> k;
    std::vector<int> vals(n, 0);

    for (int i = 0; i < n; ++i)
        std::cin >> vals[i];

    std::sort(vals.begin(), vals.end());

    int counter = 0;
    for (const auto& val: vals) {
        if (val > k)
            break;
        k -= val;
        ++counter;
    }
    std::cout << counter << std::endl;
    return 0;
}

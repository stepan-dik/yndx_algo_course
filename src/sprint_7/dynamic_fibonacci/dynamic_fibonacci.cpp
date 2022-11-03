#include <iostream>
#include <vector>
#include <cmath>

int dynamic_fibonacci(int n)
{

    int prev_0 = 1, prev_1 = 1;
    int res = 0;

    for (int i = 2; i < n+1; ++i) {
        res = (prev_0 + prev_1) % (static_cast<int>(std::pow(10, 9)) + 7);
        prev_0 = prev_1;
        prev_1 = res;
    }

    return res;
}

int main(int argc, char *argv[])
{
    int n = 0;
    std::cin >> n;
    std::cout << dynamic_fibonacci(n) << std::endl;
    return 0;
}

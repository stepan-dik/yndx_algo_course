#include <iostream>
#include <vector>
#include <cmath>

std::vector<int> first_fill(int num)
{
    std::vector<int> dp(num);
    dp[0] = 1;
    for (int i = 1; i < num; ++i) {
        for (int j = i; j-->0;)
            dp[i] = (dp[i] + dp[j]) % static_cast<int>(std::pow(10, 9) + 7);
    }
    return dp;
}

int paths_count(int n, int k)
{
    auto dp = first_fill(k);

    for (auto i = dp.size(); i < n; ++i) {
        int next_val = 0;
        for (const auto& v: dp)
            next_val = (next_val + v) % static_cast<int>(std::pow(10, 9) + 7);
        for (auto it = dp.begin(); it != dp.end()-1; ++it)
            *it = *(it+1);
        *dp.rbegin() = next_val;
        for (const auto& d: dp)
            std::cout << d << " ";
        std::cout << std::endl;
    }
    return *dp.rbegin();
}

int main(int argc, char *argv[])
{
    int n = 0, k = 0;
    std::cin >> n >> k;

    std::cout << paths_count(n, k) << std::endl;

    return 0;
}

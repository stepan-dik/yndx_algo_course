#include <iostream>
#include <vector>
#include <tuple>

std::vector<int> max_value(
        std::vector<std::pair<int, int>> options, int m)
{
    std::vector<std::vector<int>> dp(options.size()+1, std::vector<int>(m+1, 0));
    for (int i = 1; i < dp.size(); ++i) {
        for (int j = 1; j < dp[0].size(); ++j) {
            if (j - options[i-1].first >= 0)
                dp[i][j] = std::max(
                            dp[i-1][j],
                            options[i-1].second + dp[i-1][j - options[i-1].first]);
            else
                dp[i][j] = dp[i-1][j];
        }
    }

    std::vector<int> indices;

    for (int i = dp.size() - 1, j = dp[0].size() - 1; j > 0 && i > 0; --i) {
        if (dp[i][j] != dp[i-1][j]) {
            j -= options[i-1].first;
            indices.push_back(i);
        }
    }

    return indices;
}

int main()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector<std::pair<int, int>> vals(n);
    for (auto& i: vals)
        std::cin >> i.first >> i.second;

    auto res = max_value(vals, m);
    std::cout << res.size() << std::endl;
    for (const auto& i: res)
        std::cout << i << " ";
    std::cout << std::endl;

    return 0;
}

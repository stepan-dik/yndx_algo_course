#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

auto get_timetable(const std::vector<std::pair<double, double>>& acts)
{
    std::vector<std::pair<double, double>> result;
    for (const auto& [start, fin]: acts) {
        if (result.empty() || (*result.rbegin()).second <= start)
            result.push_back({start, fin});
    }

    return result;
}

int main()
{
    int n = 0;
    std::cin >> n;

    std::vector<std::pair<double, double>> acts(n);
    for (int i = 0; i < n; ++i)
        std::cin >> acts[i].first >> acts[i].second;

    std::sort(acts.begin(), acts.end(), [](auto lhs, auto rhs) {
        if (lhs.second != rhs.second)
            return lhs.second < rhs.second;
        else
            return lhs.first < rhs.first;
    });

    auto res = get_timetable(acts);

    std::cout << res.size() << std::endl;
    for (const auto& [start, fin]: res)
        std::cout << start << " " << fin << "\n";
    std::cout << std::flush;

    return 0;
}

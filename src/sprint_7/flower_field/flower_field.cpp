#include <iostream>
#include <string>
#include <vector>

std::string max_flowers(const std::vector<std::string>& field, int n, int m)
{
    std::vector<std::vector<int>> results(n+1, std::vector<int>(m+1, 0));
    for (int i = results.size()-2; i >= 0; --i) {
        for (unsigned int j = 1; j < results[0].size(); ++j) {
            results[i][j] = std::max(results[i+1][j],
                                     results[i][j-1]) +
                                    (field[i][j-1] == '1');
        }
    }

    std::string seq(n+m-2,'0');
    for (int i = 0, j = 0; i < n-1 || j < m-1;) {
        if (results[i+1][m-j] >= results[i][m-(j+1)] && i < n-1) {
            seq[n+m-3 - (i+j)] = 'U';
            ++i;
        }
        else if (j < m-1) {
            seq[n+m-3 - (i+j)] = 'R';
            ++j;
        }
    }
    std::cout<< results[0][m] << std::endl;

    return seq;
}

int main()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector<std::string> field(n);
    for (auto& line: field)
        std::cin >> line;

    std::cout << max_flowers(field, n, m) << std::endl;

    return 0;
}

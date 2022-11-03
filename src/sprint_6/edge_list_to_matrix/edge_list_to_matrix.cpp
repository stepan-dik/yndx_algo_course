// Convert edge list to adjacency matrix

#include <iostream>
#include <unordered_map>
#include <vector>

int main()
{
    int v = 0, e = 0;
    std::cin >> v >> e;

    std::unordered_map<int, std::vector<int>> matrix;
    for (int i = 0; i < v; ++i)
        matrix[i+1] = std::vector<int>(v, 0);

    for (int i = 0; i < e; ++i) {
        int start = 0, end = 0;
        std::cin >> start >> end;
        matrix[start][end - 1] = 1;
    }

    for (int i = 0; i < v; ++i) {
        for (const auto& val: matrix[i+1])
            std::cout << val << " ";
        std::cout << "\n";
    }
    std::cout << std::flush;

    return 0;
}

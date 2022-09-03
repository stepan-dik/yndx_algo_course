// Find max distance from given vertex

#include <iostream>
#include <vector>
#include <queue>

enum Colors {
    White = 0,
    Gray,
    Black
};

int BFS(int start,
         std::vector<std::vector<int>>& adj_list,
         std::vector<Colors>& colors)
{
    std::queue<std::pair<int,int>> queue;
    queue.push({start, 0});
    int ctr = 0;
    while (!queue.empty()) {
        auto [v, count] = queue.front();
        ctr = std::max(count, ctr);
        queue.pop();
        colors[v] = Black;
        auto children = adj_list[v];
        for (int c: children) {
            if (colors[c] != White)
                continue;
            colors[c] = Gray;
            queue.push({c, count+1});
        }
    }
    return ctr;
}

int main()
{
    int v = 0, e = 0;
    std::cin >> v >> e;
    std::vector<std::vector<int>> adj_list(v+1, std::vector<int>());
    for (;e-->0;) {
        int start, finish;
        std::cin >> start >> finish;
        adj_list[start].push_back(finish);
        adj_list[finish].push_back(start);
    }
    std::vector<Colors> colors(v+1, Colors::White);

    int start = 0;
    std::cin >> start;

    std::cout << BFS(start, adj_list, colors) << std::endl;

    return 0;
}

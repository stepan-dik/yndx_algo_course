// breadth-first search

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <queue>

enum Colors {
    White = 0,
    Gray,
    Black
};

void BFS(int vertex,
         std::unordered_map<int, std::vector<int>>& adj_list,
         std::vector<Colors>& colors)
{
    std::queue<int> queue;
    queue.push(vertex);
    while (!queue.empty()) {
        auto v = queue.front();
        queue.pop();
        std::cout << v << " ";
        colors[v] = Black;
        auto children = adj_list[v];
        std::sort(children.begin(), children.end());
        for (int c: children) {
            if (colors[c] != White)
                continue;
            colors[c] = Gray;
            queue.push(c);
        }
    }
    std::cout << std::endl;
}

int main()
{
    int v = 0, e = 0;
    std::cin >> v >> e;
    std::unordered_map<int, std::vector<int>> adj_list;
    for (int i = 1; i < v+1; ++i)
        adj_list[i] = std::vector<int>();
    for (;e-->0;) {
        int start, finish;
        std::cin >> start >> finish;
        adj_list[start].push_back(finish);
        adj_list[finish].push_back(start);
    }
    std::vector<Colors> colors(v+1, Colors::White);

    int root = 0;
    std::cin >> root;

    BFS(root, adj_list, colors);

    return 0;
}

// Depth-first search

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <stack>

enum Colors {
    White = 0,
    Gray,
    Black
};

void DFS_recursive(int vertex,
         std::unordered_map<int, std::vector<int>>& adj_list,
         std::vector<Colors>& colors)
{
    colors[vertex] = Colors::Gray;
    std::cout << vertex << " ";
    auto& children = adj_list[vertex];
    std::sort(children.begin(), children.end());
    for (auto v: children) {
        if (colors[v] == Colors::White)
            DFS_recursive(v, adj_list, colors);
    }
    colors[vertex] = Colors::Black;
}

void DFS_iterative(int vertex,
                   std::unordered_map<int, std::vector<int>>& adj_list,
                   std::vector<Colors>& colors)
{
    std::stack<int> vertices;
    vertices.push(vertex);
    while (!vertices.empty()) {
        auto cur_v = vertices.top();
        vertices.pop();
        switch (colors[cur_v]) {
        case Colors::White: {
            colors[cur_v] = Colors::Gray;
            std::cout << cur_v << " ";
            vertices.push(cur_v);
            auto& children = adj_list[cur_v];
            std::sort(children.rbegin(), children.rend());
            for (const auto& v: children) {
                if (colors[v] == Colors::White)
                    vertices.push(v);
            }
            break;
        }
        case Colors::Gray: {
            colors[cur_v] = Colors::Black;
            break;
        }
        case Colors::Black:
            break;
        }
    }
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

    DFS_recursive(root, adj_list, colors);
    std::cout << std::endl;
    for (auto& v: colors)
        v = Colors::White;
    for (const auto& v: colors)
        std::cout << v << " ";
    std::cout << std::endl;
    DFS_iterative(root, adj_list, colors);
    std::cout << std::endl;

    return 0;
}

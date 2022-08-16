// Find all the disjoined sets and print all the vertices for each

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

std::vector<int> BFS(int vertex,
         std::unordered_map<int, std::vector<int>>& adj_list,
         std::vector<Colors>& colors)
{
    std::vector<int> result;
    std::queue<int> queue;
    queue.push(vertex);
    while (!queue.empty()) {
        auto v = queue.front();
        queue.pop();
        result.push_back(v);
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
    return result;
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
    colors[0] = Black;

    std::vector<std::vector<int>> result;
    for (auto it = std::begin(colors)+1;
         it != std::end(colors);
         it = std::find_if(begin(colors), end(colors),
                                 [](Colors a){return a == White;}))
    {
        int root = std::distance(std::begin(colors), it);
        result.push_back(BFS(root, adj_list, colors));
    }

    for (auto& v: result) {
        std::sort(v.begin(), v.end());
    }

    std::sort(result.begin(), result.end(), [](auto& lhs, auto& rhs) {
        return lhs[0] < rhs[0];
    });

    std::cout << result.size() << "\n";
    for (const auto& v: result){
        for (const auto& i: v)
            std::cout << i << " ";
        std::cout << "\n";
    }
    std::cout << std::flush;

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <set>

#include <unordered_map>
#include <map>
#include <algorithm>
#include <queue>


int maximal_tree_weight(int s,
        std::vector<int>& start,
        std::vector<int>& finish,
        std::vector<int>& weight,
        std::vector<std::vector<int>>& adj_list,
        std::vector<bool>& used)
{
    std::vector<int> edges;
    std::vector<int> best_edges(used.size(), -1); // idx of best edge for a vertex
    std::make_heap(edges.begin(), edges.end(), [weight](auto lhs, auto rhs) {
        return weight[lhs] > weight[rhs];
    });
    int wt = 0;
    auto cur_v = s;
    used[0] = true;
    start.push_back(0), finish.push_back(s), weight.push_back(0);
    edges.push_back(start.size()-1);


    while (!edges.empty())
    {
        std::cout << cur_v << std::endl;
        for (const auto& e: edges) {
            std::cout << start[e] << " " << finish[e] << " " << weight[e] << " | ";
        }
        std::cout << std::endl;
        int new_edge = *edges.begin();
        cur_v = used[start[new_edge]] ? finish[new_edge] : start[new_edge];

        edges.erase(edges.begin());
        if ((used[start[new_edge]] && used[finish[new_edge]]) || start[new_edge] == finish[new_edge])
            continue;
        wt += weight[new_edge];

        for (const auto& edge_idx: adj_list[cur_v]) {
            int fin = cur_v == start[edge_idx] ? finish[edge_idx] : start[edge_idx];
            if (!used[fin] &&
                    (best_edges[fin] == -1 ||
                     weight[edge_idx] > weight[best_edges[fin]]))
            {
                edges.push_back(edge_idx);
//                if (best_edges[fin] != -1)
//                    std::find
                best_edges[fin] = edge_idx;
            }
            std::make_heap(edges.begin(), edges.end(), [weight](auto lhs, auto rhs){
                return weight[lhs] < weight[rhs];
            });
        }
        used[cur_v] = true;
    }

    return wt;
}

int main()
{
    int v = 0, e = 0;
    std::cin >> v >> e;

    std::vector<std::vector<int>> adj_list(v+1);
    std::vector<int> start(e), finish(e), weight(e);
    std::vector<bool> used(v+1, false);
    used[0] = true;
    for (int i = 1; i < v+1; ++i)
        adj_list[i] = {};

    for (int i = 0; i < e; ++i) {
        int st, fin, w;
        std::cin >> st >> fin >> w;
        start[i] = st, finish[i] = fin, weight[i] = w;
        adj_list[st].push_back(i);
        adj_list[fin].push_back(i);
    }

    int w = maximal_tree_weight(1, start, finish, weight, adj_list, used);
    if (std::find(used.begin(), used.end(), false) != used.end())
        std::cout << "Oops! I did it again" << std::endl;
    else
        std::cout << w << std::endl;

    return 0;
}

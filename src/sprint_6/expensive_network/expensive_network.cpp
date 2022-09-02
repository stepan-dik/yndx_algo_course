/*              --- ПРИНЦИП РАБОТЫ ---
 *   Для получения "максимального" остовного дерева используется
 * алгоритм Прима. Берётся произвольная вершина (в случае
 * реализованного алгоритма, первая), и, начиная с неё, итеративно
 * составляется список рёбер(L), сортируемый по их весу таким
 * образом, что наиболее подходящее ребро является первым в списке.
 *
 *   На каждой итерации запоминается первое ребро(А) из списка, при
 * этом из самого списка оно удаляется. Если обе вершины ребра(А) уже
 * были посещены или же ребро является петлёй, то такое ребро дальше
 * не обрабатывается, происходит переход к следующей итерации. В
 * противном случае, указанное ребро(A) считается добавленным в
 * остов, его 'вес' добавляется к общему, новая вершина(V1)
 * записывается, как посещённая. У каждого ребра(E), инциндентного
 * ранее непосещенной вершине(V1) из ребра(A) и новой вершине(V2)
 * новая вершина проверяется была ли она посещена. Если нет, то новое
 * ребро (E) добавляется в список(L).
 *   Итерации продолжаются, пока список не станет пустым.
 *
 *
 *              --- ВРЕМЕННАЯ СЛОЖНОСТЬ ---
 *   Так как список обрабатываемых рёбер реализован при помощи
 * `priority_queue`, являющегося кучей, операции по вставке и удалению
 * рёбер занимают O(Log(E)), где E - число рёбер. Доступ к элементам
 * массивов, в которых содержится информация о рёбрах и вершинах O(1).
 * Для V вершин и E рёбер, соответственно, временная сложность
 * составит O((E+V)*Log(E)).
 *
 *
 *              --- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ ---
 *   Хранение списков рёбер, списка смежности с индексами рёбер для
 * вершин занимает O(V+E) памяти, где V вершины и E рёбра. В худшем
 * случае, хранение рёбер для очереди обработки составит O(E), если
 * все рёбра инцидентны одной вершине. Суммарно это составляет
 * пространственную сложность O(V+E).
 */


#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <tuple>
#include <queue>

std::pair<int, int> max_tree_weight(
        int v,
        const std::vector<int>& start,
        const std::vector<int>& finish,
        const std::vector<int>& weight,
        const std::vector<std::vector<int>>& adj_list)
{
    const auto cmp = [weight](const int lhs, const int rhs) {
        if (weight[lhs] != weight[rhs])
            return weight[lhs] < weight[rhs];
        else
            return lhs > rhs;
    };
    std::priority_queue<int, std::vector<int>, decltype(cmp)>
            edges(cmp);
    std::vector<bool> used(v+1, false);
    used[0] = true;

    int wt = 0;
    int ctr = 0;
    edges.push(start.size()-1);

    while (!edges.empty())
    {
        int new_edge = edges.top();
        edges.pop();
        if ((used[start[new_edge]] && used[finish[new_edge]]) ||
                start[new_edge] == finish[new_edge])
            continue;

        int cur_v = used[start[new_edge]] ?
                    finish[new_edge] : start[new_edge];
        wt += weight[new_edge];
        ++ctr;
        used[cur_v] = true;

        for (const auto& edge_idx: adj_list[cur_v]) {
            int fin = cur_v == start[edge_idx] ?
                        finish[edge_idx] : start[edge_idx];
            if (!used[fin])
                edges.push(edge_idx);
        }
    }

    return {wt, ctr};
}

std::pair<int, int> max_tree_weight_set(
        int v,
        const std::vector<int>& start,
        const std::vector<int>& finish,
        const std::vector<int>& weight,
        const std::vector<std::vector<int>>& adj_list)
{
    const auto cmp = [weight](const int lhs, const int rhs) {
        if (weight[lhs] != weight[rhs])
            return weight[lhs] > weight[rhs];
        else
            return lhs > rhs;
    };
    std::set<int, decltype(cmp)> edges(cmp);
    std::vector<bool> used(v+1, false);
    used[0] = true;

    int wt = 0;
    int ctr = 0;
    edges.insert(start.size()-1);

    while (!edges.empty())
    {        
        int new_edge = *edges.begin();
        edges.erase(edges.begin());
        if ((used[start[new_edge]] && used[finish[new_edge]]) ||
                start[new_edge] == finish[new_edge])
            continue;

        int cur_v = used[start[new_edge]] ?
                    finish[new_edge] : start[new_edge];
        wt += weight[new_edge];
        ++ctr;
        used[cur_v] = true;

        for (const auto& edge_idx: adj_list[cur_v]) {
            int fin = cur_v == start[edge_idx] ?
                        finish[edge_idx] : start[edge_idx];
            if (!used[fin])
                edges.insert(edge_idx);
        }
    }

    return {wt, ctr};
}

int main()
{
    int v = 0, e = 0;
    std::cin >> v >> e;

    std::vector<std::vector<int>> adj_list(v+1);
    std::vector<int> start(e), finish(e), weight(e);

    for (int i = 0; i < e; ++i) {
        int st = 0, fin = 0, w = 0;
        std::cin >> st >> fin >> w;
        start[i] = st, finish[i] = fin, weight[i] = w;
        adj_list[st].push_back(i);
        adj_list[fin].push_back(i);
    }

    start.push_back(0), finish.push_back(1), weight.push_back(0);
    auto [w, ctr] = max_tree_weight(v, start, finish, weight, adj_list);
    if (ctr != v)
        std::cout << "Oops! I did it again" << std::endl;
    else
        std::cout << w << std::endl;

    return 0;
}

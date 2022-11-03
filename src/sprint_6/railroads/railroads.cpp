/*          --- ПРИНЦИП РАБОТЫ ---
 *   Для определения, существует ли больше, чем один путь между
 * парами вершин используется алгоритм определения цикла. Для этого
 * ребра одного типа разворачиваются. Если в таком ориентированном
 * графе без кратных ребер образован цикл, это означает, что в графе
 * существует пара вершин, между которыми есть путь по обоим типам
 * ребер. Даже если первый найденный цикл в полносвязном
 * ориентированном графе не состоит из трёх вершин, таковой в нём
 * обязательно будет присутствовать.
 *
 *          --- ВРЕМЕННАЯ СЛОЖНОСТЬ ---
 *   В худшем случае алгоритм обходит все вершины рекурсивно, по 2
 * раза (вход и выход из рекурсии), и еще раз при поиске
 * непроверенных компонент связности графа, то есть O(V), где V
 * количество вершин. Также при посещении каждой вершины проверяются
 * все, исходящие из неё рёбра, каждое ребро графа посещается 1 раз,
 * что добавляет ко временной сложности O(E), итого O(V+E).
 *
 *          --- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ ---
 *   Хранение списка смежности O(E), хранение цветов вершин
 * O(V), рекурсивный обход всех вершин в худшем случае O(V), где V
 * число вершин графа, а E число ребер. В общем случае O(V+E). В
 * случае полносвязного графа как в задаче E = V*(V-1)/2,
 * соответственно и сложность ~O(V^2).
 */

#include <iostream>
#include <vector>
#include <string>

#include <unordered_map>
#include <algorithm>
#include <queue>

enum Color {
    White = 0,
    Gray,
    Black
};

bool DFS_recursive(int vertex,
         std::vector<std::vector<int>>& adj_list,
         std::vector<Color>& colors)
{
    colors[vertex] = Color::Gray;
    auto& children = adj_list[vertex];
    auto res = true;
    for (auto v: children) {
        if (!res)
            break;
        if (colors[v] == Color::White)
            res = DFS_recursive(v, adj_list, colors);
        else if (colors[v] == Gray){
            res = false;
            break;
        }
    }
    colors[vertex] = Color::Black;
    return res;
}

int main()
{
    unsigned int v = 0;
    std::cin >> v;
    std::vector<std::vector<int>> adj_list(v+1);

    for (unsigned int i = 0; i < v; ++i) {
        std::string row;
        std::cin >> row;
        for (unsigned int j = 0; j < row.size(); ++j) {
            if (row[j] == 'R')
                adj_list[j+i+2].push_back(i+1);
            else
                adj_list[i+1].push_back(j+i+2);
        }
    }
    std::vector<Color> colors(v+1, Color::White);
    colors[0] = Black;

    bool acyclic = true;
    for (auto it = std::begin(colors);
         it != std::end(colors);
         it = std::find_if(it, end(colors),
                           [](Color a){return a == White;}))
    {
        int root = std::distance(std::begin(colors), it);
        if (!DFS_recursive(root, adj_list, colors)) {
            acyclic = false;
            break;
        }
    }

    std::cout << (acyclic? "YES" : "NO") << std::endl;
    return 0;
}

// Slow solution O(n^2)
bool is_optimal(std::vector<std::string> vec)
{
    for (int i = vec.size()-1; i > 0; i--) {
        for (unsigned int k = 0; k < vec[i].size(); k++) {
            auto edge = vec[i-1][k];
            std::vector<int> indices;
            for (unsigned int j = 0; j < vec[i+k].size(); ++j) {
                if (vec[i+k][j] == edge)
                    indices.push_back(j+k+1);
            }

            for (const auto& n: indices) {
                if (vec[i-1][n] != edge)
                    return false;
            }
        }
    }
    return true;
}

int main1()
{
    int v = 0;
    std::cin >> v;
    v--;
    std::vector<std::string> vec(v);
    for (int i = 0; i < v; ++i)
        std::cin >> vec[i];

    std::cout << (is_optimal(vec)? "YES" : "NO") << std::endl;
    return 0;
}

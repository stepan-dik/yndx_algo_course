/*
        --- ПРИНЦИП РАБОТЫ ---
  При считывании строки сразу разбиваются на слова, из которых
собирается обратный индекс с ключом по словам, содержащий по индексам
документов статистику по слову для документа.
  При получении поискового запроса, все слова добавляются во
множество слов поискового запроса. По этому множеству далее для
каждого слова по индексу проверяется статистика для каждого документа,
данные записываются в хэш-таблицу по индексу документа кладутся
значения релевантности. После составления статистики по документам,
данные сортируются и выводятся первые 5 значений.

        --- ВРЕМЕННАЯ СЛОЖНОСТЬ ---
  Временная сложность индексации имеет сложность O(n). Временная
сложность составления статистики для n документов по поисковому
запросу в m слов составит O(n*m + n*log(n)) в худшем случае, когда во всех
документах есть все слова из поискового запроса.

        --- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ ---
  Пространственная сложность при индексации составит O(n*m), где n --
количество уникальных слов, а m -- количество документов, в которых
появляются уникальные слова. Пространственная сложность составления
статистики для n документов, содержащих искомые слова, и m уникальных
слов запроса составит O(m+2n).

Посылка 66763768
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>


std::vector<std::string> get_split_string()
{
    std::string input;
    std::getline(std::cin, input);
    std::istringstream iss(input);
    std::vector<std::string> strings(std::istream_iterator<std::string>{iss},
                                     std::istream_iterator<std::string>());
    return strings;
}

struct cmp {
    bool operator()(const std::pair<int, int>& lhs,
                    const std::pair<int, int>& rhs)
    const
    {
        if (lhs.second != rhs.second)
            return lhs.second > rhs.second;
        return lhs.first < rhs.first;
    }
};

int main()
{
    int docs_num = 0;
    int queries_num = 0;

    std::string tmp;
    std::getline(std::cin, tmp);
    docs_num = std::stoi(tmp);

    std::unordered_map<std::string, std::unordered_map<int, int>> dictionary;

    for (int i = 0; i < docs_num; ++i) {
        auto strings = get_split_string();
        for (const auto& string: strings)
            ++dictionary[string][i];
    }

    tmp.clear();
    std::getline(std::cin, tmp);
    queries_num = std::stoi(tmp);

    for (int i = 0; i < queries_num; ++i) {
        auto strings = get_split_string();
        std::unordered_set<std::string> query_set;
        for (const auto& string: strings)
            query_set.insert(string);
        std::vector<std::pair<int, int>> scores(docs_num, {0,0});
        for (const auto& word: query_set) {
            for (const auto& [index, value]: dictionary[word]) {
                scores[index].first = index;
                scores[index].second += value;
            }
        }

        if (scores.size() > 5)
            std::partial_sort(scores.begin(), scores.begin() + 5,
                              scores.end(), cmp());
        else
            std::sort(scores.begin(), scores.end(), cmp{});

        int counter = 0;
        for (const auto& [index, value]: scores) {
            if (counter == 5 || value == 0)
                break;
            std::cout << index + 1 << " ";
            ++counter;
        }
        std::cout << std::endl;
    }
    return 0;
}

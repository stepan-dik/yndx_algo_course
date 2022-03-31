#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <tuple>
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
    bool operator()(const std::pair<int, int>& lhs, const std::pair<int, int>& rhs)
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
        for (const auto& string: strings) {
            if (dictionary.find(string) == dictionary.end())
                dictionary[string][i] = 1;
            else
                ++dictionary[string][i];
        }
    }

    tmp.clear();
    std::getline(std::cin, tmp);
    queries_num = std::stoi(tmp);

    for (int i = 0; i < queries_num; ++i) {
        auto strings = get_split_string();
        std::unordered_set<std::string> query_set;
        for (const auto& string: strings)
            query_set.insert(string);
        std::unordered_map<int, int> scores;
        for (const auto& word: query_set){
            for (const auto& doc_stats: dictionary[word]) {
                if (scores.find(doc_stats.first) == scores.end())
                    scores[doc_stats.first] = doc_stats.second;
                else
                    scores[doc_stats.first] += doc_stats.second;
            }
        }

        std::set<std::pair<int, int>, cmp> sorted(scores.begin(), scores.end());


        int counter = 0;
        for (const auto& index: sorted){
            if (counter == 5)
                break;
            std::cout << index.first + 1 << " ";
            ++counter;
        }
        std::cout << std::endl;
    }
    return 0;
}

//    std::cout << "docs num " << docs_num << std::endl;
//    for (const auto& doc: docs) {
//        std::cout << "1doc ";
//        for (const auto& word: doc)
//            std::cout << word.first << " " << word.second << " ";
//        std::cout << std::endl;
//    }

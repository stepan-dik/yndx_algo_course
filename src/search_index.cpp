#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <unordered_map>
#include <unordered_set>
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

int main()
{
    int docs_num = 0;
    int queries_num = 0;

    std::string tmp;
    std::getline(std::cin, tmp);
    docs_num = std::stoi(tmp);

    std::vector<std::unordered_map<std::string, int>> docs;

    for (int i = 0; i < docs_num; ++i) {
        auto strings = get_split_string();
        std::unordered_map<std::string, int> doc;
        for (const auto& string: strings) {
            if (doc.find(string) == doc.end())
                doc[string] = 1;
            else
                doc[string]++;
        }
        docs.push_back(doc);
    }

    tmp.clear();
    std::getline(std::cin, tmp);
    queries_num = std::stoi(tmp);

    for (int i = 0; i < queries_num; ++i) {
        auto strings = get_split_string();
        std::unordered_set<std::string> query_set;
        for (const auto& string: strings)
            query_set.insert(string);
        std::vector<std::tuple<int, int>> scores;
        for (int j = 0; j < docs.size(); ++j) {
            int score = 0;
            auto doc = docs.at(j);
            for (const auto& string: query_set) {
                if (doc.find(string) != doc.end())
                    score += doc.at(string);
            }
            scores.emplace_back(score, j);
        }
        std::sort(scores.begin(), scores.end(),
                         [](const std::tuple<int, int>& lhs, const std::tuple<int, int>&rhs)
        {
            if (std::get<0>(lhs) != std::get<0>(rhs))
                return std::get<0>(lhs) > std::get<0>(rhs);
            return std::get<1>(lhs) < std::get<1>(rhs);
        });

        int counter = 0;
        for (const auto& score: scores) {
            if (counter == 5)
                break;
            if (std::get<0>(score) > 0){
                std::cout << std::get<1>(score)+1 << " ";
                ++counter;
            }
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

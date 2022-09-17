#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <unordered_map>
#include <set>

void add_word(
        std::vector<std::unordered_map<char, int>>& trie,
        const std::string& word)
{
    int cur_node = 0;
    for (const auto& c: word) {
        auto next = trie[cur_node].find(c);
        if (next != trie[cur_node].end())
            cur_node = next->second;
        else {
            trie[cur_node][c] = trie.size();
            cur_node = trie.size();
            trie.push_back({});
        }
    }
    trie[cur_node][0] = -1;
}

std::vector<std::unordered_map<char, int>> build_tree(
        const std::vector<std::string>& words)
{
    std::vector<std::unordered_map<char, int>> trie(1);
    for (const auto& w: words)
        add_word(trie, w);
    return trie;
}

bool check_text(const std::string& text,
                const std::vector<std::unordered_map<char, int>>& trie)
{
    bool res = false;
    char term = 0;
    std::stack<int> stack;
    std::set<int> been_there;
    stack.push(0);
    while (!stack.empty()) {
        int cur_idx = stack.top(), node = 0;
        stack.pop();
        for (; cur_idx < text.size(); ++cur_idx) {
            if (trie[node].find(0) != trie[node].end())
                stack.push(cur_idx);
            if (trie[node].find(text[cur_idx]) != trie[node].end())
                node = trie[node].at(text[cur_idx]);
            else
                break;
        }
        if (trie[node].find(0) != trie[node].end() && cur_idx == text.size())
            return true;
    }

    return res;
}

int main()
{
    std::string text;
    std::cin >> text;

    int n = 0;
    std::cin >> n;
    std::vector<std::string> words(n);
    for (auto& w: words)
        std::cin >> w;

    auto a = build_tree(words);
    std::cout << (check_text(text, a) ? "YES" : "NO") << std::endl;

    return 0;
}

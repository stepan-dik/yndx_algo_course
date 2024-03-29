/*              --- ПРИНЦИП РАБОТЫ ---
 *   Для определения, возможно ли составить строку из шаблонов,
 * используется префиксное дерево из шаблонов, по которому, после его
 * построения, проверяется текст. При проверке текста используется
 * динамика. В массиве dp хранится количество элементов по длине
 * текста, каждый из элементов отображает, достижим ли элемент
 * исходного текста с таким индексом и был ли он посещён. Первый
 * элемент по умолчанию достижим. Если при прохождении по тексту и
 * префиксному дереву в дереве всегда находился узел для символа из
 * текста и был достигнут узел, содержащий терминальный символ, то
 * текущий индекс помечается как достижимый. При использовании
 * достижимого индекса из массива dp, элемент массива dp помечается
 * как использованный, такой элемент не может быть заново помечен как
 * достижимый.
 *   На каждой итерации производится поиск наибольшего достижимого
 * индекса, который используется в качестве стартового. Пока такие
 * индексы находятся, либо пока не встретится терминальный символ на
 * индексе равном размеру текста, итерации продолжаются.
 *
 *              --- ВРЕМЕННАЯ СЛОЖНОСТЬ ---
 *   Сложность построения префиксного дерева O(m), где m - суммарная
 * длина всех шаблонов.
 *   В худшем случае, когда есть шаблоны совпадающие с каждым
 * собственным префиксом исходной строки и каждым суффиксом от
 * префикса без последнего символа исходной строки, сложность проверки
 * текста по такому дереву шаблонов составит O(n^2), где n - длина
 * текста.
 *
 *              --- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ ---
 *   Дополнительная память для хранения префиксного дерева O(Log(m)),
 * где m - суммарная длина всех шаблонов. Пространственная сложность
 * для dp O(n), где n - длина текста. Итого O(Log(m)+n).
 */

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

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
    std::vector<int> dp(text.size(), 0);
    dp[0] = 1;
    int i = 0;

    for (auto r_it = dp.rend() - 1 - dp.size();
        r_it != dp.rend();
        r_it = std::find(dp.rbegin()+(dp.size()-1-i),dp.rend(),1))
    {
        i = dp.size() - 1 - std::distance(dp.rbegin(), r_it);
        dp[i] = -1;
        int node = 0;

        for (; i < text.size(); ++i) {
            if (trie[node].find(0) != trie[node].end() && !dp[i])
                dp[i] = 1;

            if (trie[node].find(text[i]) != trie[node].end())
                node = trie[node].at(text[i]);
            else
                break;
        }

        if (trie[node].find(0) != trie[node].end() &&
                i == text.size())
            return true;
    }

    return res;
}


/*              --- ПРИНЦИП РАБОТЫ ---
 *   Для определения, возможно ли составить строку из шаблонов,
 * используется префиксное дерево из шаблонов, по которому, после его
 * построения, проверяется текст. При проверке текста в дек кладутся
 * значения индексов, на которых достигаются терминальные символы
 * шаблонов, как индексы, с которых следует начать в случае
 * невозможности составить текст из шаблонов с текущей стартовой
 * позиции. Также хранится множество индексов уже использованных как
 * стартовых во избежание повторного расчёта с этих позиций. В дек
 * не могут попасть индексы, которые уже находятся во множестве
 * проверенных позиций. При каждом извлечении нового стартового
 * индекса из дек, этот индекс клаётся во множество посещенных.
 * Множество посещенных индексов в свою очередь очищается от индексов,
 * в которые из оставшихся стартовых попасть не получится.
 *   Новые стартовые позиции извлекаются, пока список не опустеет,
 * либо пока не найдётся позиция, в которой завершаются и проверяемый
 * текст, и какой-то из шаблонов.
 *
 *              --- ВРЕМЕННАЯ СЛОЖНОСТЬ ---
 *   Сложность построения префиксного дерева O(m), где m - суммарная
 * длина всех шаблонов.
 *   В худшем случае, когда есть шаблоны совпадающие с каждым
 * собственным префиксом исходной строки и каждым суффиксом от
 * префикса без последнего исходной строки символа, то сложность
 * проверки текста по такому дереву шаблонов составит O(n^2), где n -
 * длина текста.
 *
 *              --- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ ---
 *   Дополнительная память для хранения префиксного дерева
 * O(Log(m)), где m - суммарная длина всех шаблонов. Пространственная
 * сложность для хранения новых стартовых индексов соразмерна
 * количеству шаблонов p, являющихся префиксами друг друга O(p), а для
 * хранения посещенных индексов - обратно пропорцинальна средней длине
 * шаблонов, составляющих наиболее длинную подстроку исходного текста
 * O(n/l), где n - длина текста, а l - средняя длина шаблонов,
 * составляющих наиболее длинную подстроку. Итого O(Log(m)+p+n/l).
 */

#include <deque>
#include <set>

bool check_text_d(const std::string& text,
                const std::vector<std::unordered_map<char, int>>& trie)
{
    bool res = false;
    char term = 0;
    std::deque<int> deque;
    std::set<int> been_there;
    deque.push_front(0);
    while (!deque.empty()) {
        int cur_idx = deque.front(), node = 0;
        been_there.insert(cur_idx);
        deque.pop_front();
        for (auto it = been_there.begin();
             it != been_there.end() && *it < deque.back(); ++it)
        {
            been_there.erase(it);
        }
        for (; cur_idx < text.size(); ++cur_idx) {
            if (trie[node].find(0) != trie[node].end() &&
                    been_there.find(cur_idx) == been_there.end())
            {
                deque.push_front(cur_idx);
            }
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

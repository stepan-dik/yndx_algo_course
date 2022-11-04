/*
     WIP
*/



#include <iostream>
#include <string>
#include <vector>


std::vector<int> search(const std::string& p, const std::string& text)
{
    std::string s(p.size()+text.size()+1, '#');
    s.replace(0, p.size(), p);
    s.replace(p.size()+1, text.size(), text);

    std::vector<int> pref(p.size(), 0);
    std::vector<int> results;
    int prev = 0;

    for (int i = p.size()+1; i < s.size(); ++i) {
        int k = prev;
        while (k > 0 && s[k] != s[i])
            k = pref[k-1];
        k += s[k] == s[i];
        if (i < p.size())
            pref[i] = k;
        prev = k;
        if (k == p.size())
            results.push_back(i - 2*p.size());
    }

    return results;
}

std::string replace_enlarge(std::string& s, const std::string& pattern, const std::string& repl)
{

}

std::string replace_shrink(std::string& s, const std::string& pattern, const std::string& repl)
{

}


std::string replace_pattern(std::string& s, const std::string& pattern, const std::string& repl)
{
    std::string result;
    auto idx = search(pattern, s);

    int diff_k = static_cast<int>(pattern.size()) - static_cast<int>(repl.size());
    if (diff_k > 0) {
        s.resize(s.size() + diff_k * idx.size());
    }



    return result;
}

int main()
{
    std::string s;
    std::string pattern;
    std::string replacement;

    std::cin >> s >> pattern >> replacement;
    auto res = search(pattern, s);
    for (const auto& i: res)
        std::cout << i << " ";
    std::cout << std::endl;

    return 0;
}

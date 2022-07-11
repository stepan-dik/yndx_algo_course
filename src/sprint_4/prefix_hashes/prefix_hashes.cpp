// Calculate hash of a substring for O(1)

#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>

long long calc_hash(long l, long r, long long* hashes, long long* pows, long mod)
{
    long long hash = (hashes[r] + mod -
                      (hashes[l-1] * pows[r - l+1]) % mod) % mod;

    return hash;
}

long long* calc_prefixes(std::string s, long long base, long long mod)
{
    long long* hashes = new long long[s.size()+1];
    hashes[0] = 0;

    size_t l = 1;
    for (auto i = s.begin(); i < s.end(); ++i, ++l)
        hashes[l] = ((hashes[l-1] * base) % mod + int(*i)) % mod;

    return hashes;
}

long long* calc_pows(size_t to, long long base, long long mod)
{
    long long* pows = new long long[to + 1];
    pows[0] = 1;

    for (size_t i = 1; i < to+1; ++i)
        pows[i] = (pows[i-1] * base) % mod;

    return pows;
}

int main()
{
    int tries = 0;
    std::cin >> tries;

    for(;tries-->0;) {
        long base = 0;
        long mod = 0;
        std::cin >> base >> mod;

        std::string s;
        std::cin >> s;

        auto start = std::chrono::high_resolution_clock::now();

        auto hashes = calc_prefixes(s, base, mod);
        auto pows = calc_pows(s.size(), base, mod);

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Prefixes " << duration.count() << "mcs" << std::endl;

        int cmds = 0;
        std::cin >> cmds;
        long l = 0;
        long r = 0;
        for (;cmds-->0;) {
            std::cin >> l >> r;
            auto start = std::chrono::high_resolution_clock::now();
            auto res = calc_hash(l, r, hashes, pows, mod);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            std::cout << "Calc hash " << res  << " duration " << duration.count() << "mcs" << std::endl;
        }
        delete [] hashes;
        delete [] pows;
    std::cout << std::endl;
    }

    return 0;
}

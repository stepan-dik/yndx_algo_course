// Find a string with a hash identical to another string

#include <iostream>
#include <unordered_map>
#include <string>
#include <array>
#include <tuple>
#include <ctime>

long long calc_hash(long l, long r, long long* hashes, long long* pows, long mod)
{
    long long hash = (hashes[r] + mod -
                      (hashes[l-1] * pows[r - l+1]) % mod) % mod;

    return hash;
}

std::pair<std::unordered_map<long long, int>, long long> calc_prefixes(std::string s, long long base, long long mod)
{
    std::unordered_map<long long, int> hashes;
    hashes[0] = 0;

    long long hash = 0;
    size_t l = 1;
    for (auto i = s.begin(); i < s.end(); ++i, ++l) {
        hash = ((hash * base) % mod + int(*i)) % mod;
        hashes[hash] = l;
    }

    return {hashes, hash};
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
    long long base = 1000;
    long long mod = 123987123;
    std::array<char, 26> chars{
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
        'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    std::string a = "akdutnedovplqwnbhzxtsdlnnnadlkkjfxmcnvitywoqplksdnmkzcvtnrqpgoybmvbqwzpokdkcvnnjoydfmashkovits";
    std::string b;
    auto [hashes_a, hash_a] = calc_prefixes(a, base, mod);
    auto pows = calc_pows(1000, base, mod);

    long long hash_b = 0;
    std::srand(std::time(nullptr));
    while (hash_b != hash_a) {
        char n = chars[std::rand() % 26]; // markus loves foods :)
        if (b.size() >= 50){
            hash_b = (hash_b + mod - (int(b.at(0)) * pows[b.size()-1]) % mod) % mod;
            b = b.substr(1);
        }
        b.append(1, n);
        hash_b = ((hash_b * base) % mod + int(n)) % mod;
        auto f = hashes_a.find(hash_b);
        if (f != hashes_a.end()){
            std::cout << hash_b << " " << f->first << "\n" << a.substr(0, f->second) << std::endl;
            std::cout << b << " " << b.size() << std::endl;
            break;
        }
    }


    delete [] pows;
    return 0;
}

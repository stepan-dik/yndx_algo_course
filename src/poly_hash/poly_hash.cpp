#include <chrono>
#include <iostream>
#include <string>
#include <cmath>

long int pow(long int base, int to, long int mod)
{
    if (to == 0)
        return 1;
    else if (to == 1)
        return base;

    long int result = 1;

    while(to > 0) {
        if (to %2 !=0)
            result = std::div(result * base, mod).rem;
        base = std::div(base*base, mod).rem;
        to >>= 1;
    }

    return result;
}

long calc_hash(std::string s, long base, long mod)
{
    long int hash = 0;
    long prev_pov = 1;
    for (auto i = s.rbegin(); i < s.rend(); ++i) {
        auto poww = std::div(static_cast<long int>(*i) * prev_pov, mod).rem;
        auto tmp = std::div(hash, mod).rem + std::div(poww, mod).rem;
        auto rem = std::div(tmp, mod).rem;
        prev_pov = std::div(prev_pov * base, mod).rem;
        hash = rem < 0 ? rem + mod : rem;
    }

    return hash;
}

int main()
{
    int tries = 0;
    std::cin >> tries;
    for (;tries-->0;){
        long base = 0;
        long mod = 0;
        std::string s;
        std::cin >> base >> mod;

        std::cin >> s;
        auto start = std::chrono::high_resolution_clock::now();
        auto res = calc_hash(s, base, mod);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        std::cout << res << " " << (res <= mod) << " " << duration.count() << "mcs" << std::endl;
    }

    return 0;
}

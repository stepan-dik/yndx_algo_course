#include <iostream>
#include <string>
#include <cmath>

long pow(long base, long to, long mod)
{
//    std::cout << base << " " << to << " " << mod << " ";
    long res = 1;
    for (;to-->0;) {
        res = std::div(res * base, mod).rem;
    }
    std::cout << res << " | ";
    return res;
}

long calc_hash(std::string s, long base, long mod)
{
    long hash = 0;
    int ctr = 0;
    for (auto i = s.rbegin(); i < s.rend(); ++i, ++ctr) {
//        std::cout << (std::div(std::pow(base, ctr), mod).rem) << " ";
//        long long tmp =
//                hash +
//                std::div(
//                    std::div(*i, mod).rem *
//                    std::div(std::pow(base, ctr), mod).rem,

//                    mod
//                    ).rem;
////        std::cout << tmp << " ";
//        auto rem = std::div(tmp, static_cast<long long>(mod)).rem;
        auto poww = (std::div(static_cast<long>(*i), mod).rem * pow(base, ctr, mod));
        auto tmp = hash + poww;
        auto rem = std::div(tmp, mod).rem;
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
        std::cout << calc_hash(s, base, mod) << std::endl;
    }

    return 0;
}

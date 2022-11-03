// Count how many search trees can be built using N unique keys

#include <iostream>

int trees_count(int keys)
{
    long long count = 0;
    if (keys < 2)
        return 1;

    long long left = 1;
    long long right = 1;
    for (auto i = 0; i < keys; ++i) {
        left = trees_count(i);
        right = trees_count(keys - i - 1);
        count += left*right;
    }
    return count;
}


int main()
{
    int tries = 0;
    std::cin >> tries;
    for (;tries-->0;){
        int n = 0;
        std::cin >> n;
        std::cout << trees_count(n) << std::endl;
    }

    return 0;
}

#include <iostream>
#include <vector>

int get_max_revenue(const std::vector<int>& prices)
{
    int rev = 0;
    bool bought = false;
    int buy_price = 0;

    for (auto it = prices.begin(); it != prices.end(); ++it) {
        if (bought) {
            if (*it > *(it+1) || (it+1) == prices.end()) {
                std::cout << "sell "<< *it << ", ";
                bought = false;
                rev += *it - buy_price;
            }
        }
        else {
            if (*it < *(it+1)) {
                std::cout << "buy "<< *it << ", ";
                bought = true;
                buy_price = *it;
            }
        }
    }

    return rev;
}

int main()
{
    int l = 0;
    std::cin >> l;

    std::vector<int> prices(l);
    for (int i = 0; i < l; ++i)
        std::cin >> prices[i];

    std::cout << get_max_revenue(prices) << std::endl;

    return 0;
}

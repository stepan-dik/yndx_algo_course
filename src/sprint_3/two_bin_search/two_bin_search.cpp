/*
    Find the first occurence of element greater than or equal to given in
    vector if there is one
*/

#include <iostream>
#include <vector>

int closest_bigger(const std::vector<int>& vec, int target)
{
    if (vec[0] >= target)
        return 1;
    if (vec[vec.size() - 1] < target)
        return -1;
    int l = 0;
    int r = vec.size() - 1;
    int mid = 0;
    while (l < r) {
        mid = r/2 + l/2;
        if (vec[mid] >= target) {
            if (vec[mid - 1] < target)
                return mid + 1;
            r = mid - 1;
            continue;
        }
        else {
            if (vec[mid + 1] > target)
                return mid + 2;
            l = mid + 1;
            continue;
        }
    }
    if (vec[mid] > target) {
        if (vec[mid - 1] < target)
            return mid + 1;
        else if (vec[mid - 2] < target)
            return mid;
    }
    return mid + 2;
}

int main()
{
    int size = 0;
    std::cin >> size;
    std::vector<int> savings(size, 0);
    for (int i = 0; i < size; ++i)
        std::cin >> savings[i];

    int price = 0;
    std::cin >> price;

    std::cout << closest_bigger(savings, price)
              << " " << closest_bigger(savings, price*2) << std::endl;

}

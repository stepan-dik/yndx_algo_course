#include <iostream>
#include <vector>

int main()
{
    int size = 0;
    std::cin >> size;
    int arr[size];

    std::vector<int> zeroIndices;
    for (int i = 0, curEl; i < size; ++i) {
        std::cin >> curEl;
        if (curEl == 0)
            zeroIndices.push_back(i);
    }

    for (int i = 0; i < zeroIndices[0] + 1; ++i) {
        arr[zeroIndices[0] - i] = i;
    }
    int first = zeroIndices[0];
    int second = zeroIndices[1];
    for (unsigned int i = 0; i + 1 < zeroIndices.size(); ++i) {
        for (int j = 0; j * 2 < (second - first) + 1; ++j) {
            arr[first + j] = j;
            arr[second - j] = j;
        }
        first = zeroIndices[i + 1];
        second = zeroIndices[i + 2];
    }

    for (int i = 0; first + i < size; ++i) {
        arr[first + i] = i;
    }

    for (int i = 0; i < size; ++i)
        std::cout << arr[i] << " ";

    return 0;
}

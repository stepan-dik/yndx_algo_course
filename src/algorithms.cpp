#include "algorithms.h"

using namespace Algs;

double* Algorithms::movingAverage(double* array, const size_t size, const int k)
{
    auto resultSize = size - k + 1;
    double* result = new double[resultSize];
    double sum = 0.0;

    for (int j = 0; j < k; ++j){
        sum += array[j];
    }

    for (size_t i = 0; i < resultSize; ++i) {
        if (i > 0){
            sum -= array[i-1];
            sum += array[i+k-1];
        }
        result[i] = sum/k;
    }
    return result;
}

int* Algorithms::twoSum(int *array, const size_t size, const int k)
{
    auto resultSize = 2;
    int* result = new int[resultSize];
    std::unordered_map<int, int> map;
    for (unsigned int i = 0; i < size; ++i) {
        map[array[i]] = i;
    }
    auto pair = map.end();
    for (const auto& i: map) {
        pair = map.find(k - i.first);
        if (pair == map.end() || pair->second == i.second)
            continue;
        result[0] = array[i.second];
        result[1] = array[pair->second];
        break;
    }
    if (pair == map.end()){
        return nullptr;
    } else {
        return result;
    }
}

std::unordered_set<unsigned int> Algorithms::primeNumbers(unsigned int n)
{
    unsigned int ints[n+1];
    std::unordered_set<unsigned int> primes;
    for (unsigned int i = 0; i < n+1; ++i)
        ints[i] = 0;
    for (unsigned int i = 2; i < n+1; ++i) {
        if (ints[i] == 0) {
            primes.emplace(i);
            for (unsigned int j = 1; j*i < n+1; ++j) {
                ints[i*j] = i;
            }
        }
    }
    return primes;
}

std::vector<int> Algorithms::neighbours()
{

    int x = 0, y = 0;
    int cX = 0, cY = 0;
    int* matrix = nullptr;
    std::ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        myfile >> x;
        myfile >> y;
        matrix = new int[x * y];
        for (int i = 0; i < x; ++i) {
            for (int j = 0; j < y; ++j) {
                myfile >> matrix[i + x*j];
            }
        }

        myfile >> cX;
        myfile >> cY;

        myfile.close();
    }

    std::vector<int> result;
    for (int i = -1, b = 0; i < 2; ++i) {
        for (int j = -1; j < 2; ++j, ++b) {
            int coordX = i + cX;
            int coordY = j + cY;
            if (b % 2 == 0 || coordX < 0 || coordX > x - 1 || coordY < 0
                    || coordY > y - 1)
                continue;
            result.emplace_back(matrix[coordX + x*coordY]);
        }
    }

    delete [] matrix;
    std::sort(result.begin(), result.end());
    return result;
}

int Algorithms::randomness()
{
    int size = 0;
    int* data = nullptr;
    int result = 0;
    std::fstream myfile("input.txt");
    if (myfile.is_open()) {
        myfile >> size;
        data = new int[size];
        for (int i = 0; i < size; ++i) {
            myfile >> data[i];
        }
        myfile.close();
    }

    if (size == 1) {
        return 1;
    }

    for (int i = 0; i < size; ++i) {
        if (i == 0) {
            if (data[i] > data[i+1])
                result+=1;
            continue;
        }
        else if (i == size - 1) {
            if (data[i] > data[i-1])
                result += 1;
            continue;
        }

        if (data[i] > data[i-1] && data[i] > data[i+1])
            result += 1;
    }

    delete [] data;
    return result;
}

std::pair<int, std::string> Algorithms::longestWord()
{
    int size = 0;
    std::string data;
    std::vector<std::string> vec;
    std::fstream myfile("input.txt");
    if (myfile.is_open()) {
        myfile >> size;
        for (std::string line; std::getline(myfile, line);) {
            data = line;
        }
        myfile.close();
    }

    int wordLength = 0;
    int maxWordLength = 0;
    std::string lWord;
    std::string curWord;

    for (const auto i: data) {
        if (std::isspace(i)) {
            if (wordLength > maxWordLength){
                lWord = curWord;
                maxWordLength = wordLength;
            }
            wordLength = 0;
            curWord = std::string();
            continue;
        }

        curWord.append(1, i);
        wordLength += 1;
    }
    if (wordLength > maxWordLength){
        lWord = curWord;
        maxWordLength = wordLength;
    }

    return std::pair<int, std::string>{maxWordLength, lWord};
}

bool Algorithms::palindrom()
{
    std::string data;
    bool result = false;
    std::fstream myfile("input.txt");
    if (myfile.is_open()) {
        for (std::string line; std::getline(myfile, line);) {
            data.append(line);
        }
        myfile.close();
    }

    std::cout << data << "\n";

    for (int i = 0, j = data.length(); i <= j + 1; ++i, --j) {

        while (!std::isalnum(data[i]))
            ++i;
        while (!std::isalnum(data[j]))
            --j;

        if (i >= j) {
            result = true;
            break;
        }
        if (std::tolower(data[i]) != std::tolower(data[j]))
            break;
    }

    return result;
}

std::string Algorithms::toBinary()
{
    std::string data;
    std::string result;
    std::fstream myfile("input.txt");
    int num = 0;
    if (myfile.is_open()) {
        myfile >> num;
    }

    while (num*2 > 1) {
        if (num % 2 != 0)
            result.insert(result.begin(), '1');
        else
            result.insert(result.begin(), '0');
        num = num/2;
    }
    if (result.empty())
        result.insert(result.begin(), '0');

    return result;
}

std::string Algorithms::binarySum()
{
    std::string result;
    std::string first;
    std::string second;
    std::fstream myfile("input.txt");
    if (myfile.is_open()) {
        myfile >> first;
        myfile >> second;
        myfile.close();
    }

    int maxLength = std::max(first.length(), second.length());
    auto pair = std::minmax(first, second, cmpByLen);
    auto smaller = pair.second;
    auto larger = pair.first;
    smaller.insert(smaller.begin(), std::abs(static_cast<int>(first.length() - second.length())), '0');
    bool overflown = false;
    for (auto i = 0; maxLength - i > 0; ++i) {
        auto curDig = overflown ? 1 : 0;
        overflown = false;

        auto fI = larger.length() - i - 1;
        auto firstNum = std::stoi(smaller.substr(fI,1));
        auto secondNum = std::stoi(larger.substr(fI,1));

        auto curNum = firstNum + secondNum + curDig;
        if ( curNum > 1) {
            overflown = true;
            curNum -= 2;
        }
        result.insert(0, std::to_string(curNum));
    }
    if (overflown)
        result.insert(0, std::to_string(1));
    return result;
}

bool Algorithms::cmpByLen(std::string one, std::string another)
{
    return one.length() > another.length();
}

bool Algorithms::isPowOf4(int num)
{
    long i = 4;
    while (i < num) {
        i *= i;
    }
    return i == num;
}

std::vector<unsigned int> Algorithms::factorize(unsigned int n)
{
    std::vector<unsigned int> result;
    unsigned int div = 0;
    unsigned int i = 2;

    while (n != 1) {
        while (i * i <= n) {
            if (n % i == 0) {
                result.push_back(i);
                div = i;
                n /= div;
                continue;
            }
            ++i;
        }
        if (div == 0 || i*i > n){
            result.push_back(n);
            break;
        }
    }

    return result;
}

std::vector<unsigned int> Algorithms::factorize1(unsigned int n)
{
    std::vector<unsigned int> result;
    std::vector<unsigned int> primes;
    unsigned int ints[(n/2 + 1)];

    for (unsigned int i = 0; i < (n/2 + 1); ++i)
        ints[i] = 0;

    for (unsigned int i = 2; i < (n/2 + 1); ++i) {
        if (ints[i] == 0) {
            primes.push_back(i);
            for (unsigned int j = 1; j*i < (n/2 + 1); ++j) {
                ints[i*j] = i;
            }
        }
    }
    unsigned int first = 0;
    for (const auto& i: primes) {
        if (n % i == 0) {
            first = i;
        }
    }
    if (first == 0){
        return std::vector<unsigned int>{n};
    }
    n /= first;
    result.push_back(first);

    while (std::find(primes.begin(), primes.end(), n) == primes.end()) {
        result.insert(result.begin(), ints[n]);
        n = n / ints[n];
    }
    result.insert(result.begin(), n);
    return result;
}

std::vector<int> Algorithms::sumListAndNum(int size, int *arr, int num)
{
    int arrNum = 0;
    std::vector<int> result;
    for (int i = 0; i < size; ++i)
        arrNum += std::pow(10, i) * arr[size - 1 - i];
    auto sum = arrNum + num;
    while (sum != 0){
        result.insert(result.begin(), sum % 10);
        sum /= 10;
    }
    return result;
}

unsigned char Algorithms::redundantLetter(std::string first, std::string second)
{
    std::unordered_map<unsigned char, int> occured1;
    std::unordered_map<unsigned char, int> occured2;

    for (const auto &c: first){
        if (occured1.find(c) == occured1.end())
            occured1[c] = 1;
        else
            occured1[c]++;
    }

    for (const auto &c: second){
        if (occured2.find(c) == occured2.end())
            occured2[c] = 1;
        else
            occured2[c]++;
    }

    for (const auto &c: occured2){
        if (occured1[c.first] != c.second)
            return c.first;
    }
    return 0;
}

int* Algorithms::closestZero(int size, int *arr)
{
    std::vector<int> zeroIndices;
    for (int i = 0; i < size; ++i) {
        if (arr[i] == 0)
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

    return arr;
}

int Algorithms::countRepeatsLT(int k, std::string str)
{
    int fullK = k*2;
    int result = 0;
    std::array<char, 10> chars;
    for (int i = 0; i < 10; ++i) {
        chars[i] = '0' + i;
    }

    for (const auto c: chars) {
        int repeats = 0;
        for (const auto el: str) {
            if (el == c)
                ++repeats;
            if (repeats > fullK)
                break;
        }
        if (repeats <= fullK && repeats > 0)
            ++result;
    }

    return result;
}

int* Algorithms::transpose(int width, int heigth, int *matrix)
{
    int size = width * heigth;

    int *matrix2 = new int[size];

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < heigth; ++j) {
            matrix2[heigth*i + j] = matrix[width*j + i];
        }
    }

    return matrix2;
}

void Algorithms::printLinkedList(Node *head)
{
    while (head != nullptr) {
        std::cout << head->value << std::endl;
        head = head->next;
    }
}

Node* Algorithms::deleteNode(Node *head, int idx)
{
    auto curEl = head;
    if (idx == 0)
        return head->next;
    for (int i = 0; i < idx -1; ++i)
        curEl = curEl->next;
    curEl->next = (curEl->next->next);
    return head;
}

int Algorithms::index(Node *head, const std::string &element)
{
    for (int i = 0; head->next != nullptr; ++i) {
        if (head->value == element)
            return i;
        head = head->next;
    }
    return -1;
}

Node* Algorithms::inverseOrder(Node *head)
{
    Node* nxt = nullptr;
    Node* cur = nullptr;
    while (head != nullptr) {
        cur = head;
        nxt = head->next;
        head->next = head->prev;
        head->prev = nxt;
        head = nxt;
    }
    return cur;
}

int Algorithms::fibonacciFirst(int num)
{
    int curr = 1;
    int prev = 1;
    for (;num > 1;--num) {
        auto tmp = curr;
        curr = prev + curr;
        prev = tmp;
    }
    return curr;
}

int Algorithms::fibonacciMod(int n, int k)
{
    int curr = 1;
    int prev = 1;
    while(n > 1) {
        auto tmp = curr;
        curr = prev + curr;
        prev = tmp;
        curr %= static_cast<int>(std::pow(10,k));
        prev %= static_cast<int>(std::pow(10,k));
        --n;
    }
    return curr;
}

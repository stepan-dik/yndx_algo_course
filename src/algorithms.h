#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <cmath>

struct Node {
    Node(const std::string &value, Node* next, Node* prev = nullptr)
        : value(value)
        , next(next)
        , prev(prev)
    {}
    const std::string value;
    Node* next;
    Node* prev;
};

class Algorithms
{
public:
    Algorithms() = delete;

    // Sprint 1
    static double* movingAverage(double* array, const size_t size, const int k);
    static int* twoSum(int* array, const size_t size, const int k);
    static std::unordered_set<unsigned int> primeNumbers(unsigned int n);
    static std::vector<int> neighbours();
    static int randomness();
    static std::pair<int, std::string> longestWord();
    static bool palindrom();
    static std::string toBinary();
    static std::string binarySum();
    static bool cmpByLen(std::string, std::string);
    static bool isPowOf4(int);
    static std::vector<unsigned int> factorize(unsigned int);
    static std::vector<unsigned int> factorize1(unsigned int);
    static std::vector<int> sumListAndNum(int, int*, int);
    static unsigned char redundantLetter(std::string, std::string);
    static int* closestZero(int, int*);
    static int countRepeatsLT(int, std::string);

    // Sprint 2
    static int* transpose(int, int, int*);
    static void printLinkedList(Node*);
    static Node* deleteNode(Node*, int);
    static int index(Node*, const std::string&);
    static Node* inverseOrder(Node*);
};

#endif // ALGORITHMS_H

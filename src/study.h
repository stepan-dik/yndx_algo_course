#include <vector>
#include <string>
#include <iostream>
#include <QDebug>
#include <unistd.h>
#include <iomanip>
#include <cmath>
#include <array>

#include "refconnector.h"

#define UNUSED(x) (void)(x)
unsigned int asecond = 1000000;

std::vector<int> vec {1,3,5,11,12,13,14,15,16,17,18,19,20,21,25,26,27,30,50,55,
                      56,58,100,200,300,400,500,600,700};
//std::vector<int> vec {1,3,5,15,16,17,18,19,20,21,25,26,27,30,50,55,56,58,100,200,300,400,500,600,700};

typedef void (*functionPointer)(std::vector<int>&, bool);

int count_divisible() {
    unsigned int count{};
    for (auto val: vec)
        count += ((val%5==0) != (val%3==0))? 1 : 0;
    return count;
}

int count_divisible_incorrect() {
    unsigned int count{};
    for (auto val: vec)
        count += (val%5 != val%3)? 1 : 0;
    return count;
}

int count_divisible_ex() {
    int count{0};
    for (auto i: vec) {
        if (i % 3 == 0 || i % 5 == 0) {
            ++count;
        }
    }
    return count;
}

int calculate_pairs(std::vector<int> vec){
    int result{};
    std::vector<int> newVec = vec;
    for (auto val: vec){
        newVec.erase(newVec.cbegin());
        for (auto otherVal: newVec){
            qDebug() << val << '*' << otherVal;
            result+= val*otherVal;
        }
    }
    return result;
}

void funcWrapper(functionPointer pointer, std::vector<int> numbers,
                 bool small=true){
    if (numbers.empty()){
        std::cout << "List is empty. Nothing to display" << std::endl;
        return;
    }
    if (pointer == nullptr){
        std::cout << "Error! Got nullptr instead of normal function pointer!"
                  << std::endl;
        return;
    }
    (pointer)(numbers,small);
}

void printNums(std::vector<int> &numbers, bool small){
    UNUSED(small);
    std::cout << "Numbers are" << std::endl;
    for (auto i: numbers)
        std::cout << i << " ";
    std::cout << std::endl;
}

void addNum(std::vector<int> &numbers){
    std::string input{};
    int num{};
    std::cout << "Please, enter your number ";
    std::cin >> input;
    try {
        num = std::stoi(input);
    } catch (std::invalid_argument()) {
        std::cout << "Error. Argument invalid." << std::endl;
        return;
    }
    numbers.push_back(num);
    std::cout << std::endl << "Number " << num << " added successfully";
}

void meanOfNums(std::vector<int> &numbers, bool small){
    UNUSED(small);
    double sum{};
    for (auto i: numbers)
        sum+=i;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Mean number is " << sum/numbers.size() << std::endl;
}

void theNum(std::vector<int> &numbers, bool small){
    int result = numbers.at(0);
    for (auto i: numbers){
        if (((i < result) && small) || ((i > result) && !small))
            result = i;
    }
    std::string str = small ? "smallest" : "largest";
    std::cout << "The " << str << " number is " << result << std::endl;
}

int loop(){
    std::vector<int> numbers{};
    do {
        std::string option{};
        std::cout << std::endl << "---------------------------" << std::endl
                  << "P - Print numbers" << std::endl
                  << "A - Add a number" << std::endl
                  << "M - Display mean of the numbers" << std::endl
                  << "S - Display the smallest number" << std::endl
                  << "L - Display the largest number" << std::endl
                  << "Q - Quit" << std::endl
                  << "Please choose your option: ";
        std::cin >> option;
        if(option.length()>1)
            std::cout << "Warning: multiple characters entered. "
                         "Taking last one '%s'.", option.back();
        unsigned char choice = option.back();
        switch(choice){
            case 'P':
            case 'p': funcWrapper(printNums, numbers); break;
            case 'A':
            case 'a': addNum(numbers); break;
            case 'M':
            case 'm': funcWrapper(meanOfNums, numbers); break;
            case 'S':
            case 's': funcWrapper(theNum, numbers, true); break;
            case 'L':
            case 'l': funcWrapper(theNum, numbers, false); break;
            case 'Q':
            case 'q': std::cout << "Goodbye" << std::endl; return 0;
        default:
            std::cout << "Unhandled reply " << choice << " . Please try again"
                      << std::endl << "Whole input: " << option;
            usleep(1 * asecond);
        }
    } while (true);
}

void encrypt(std::string &message){
    for (size_t i{0}; i< message.size(); i++){
        message.at(i) +=2*i + 1;
    }
}

void decrypt(std::string &message){
    for (size_t i{0}; i< message.size(); i++){
        message.at(i) -=2*i + 1;
    }
}

void encryptor(){
    std::string str;
    do {
        std::cout << "Enter message to encrypt: ";
        std::getline(std::cin, str);
        std::cout << "--------------" << std::endl << "Encrypting" << std::endl
                  << "--------------" << std::endl;
        encrypt(str);
        std::cout << "Encrypted message: " << str << std::endl;
        decrypt(str);
        std::cout << "Decrypted message: " << str << std::endl;
        std::cout << "--------------" << std::endl;
    } while (true);
}

void letter_pyramid() {
    std::string user_provided;
    std::cout << "Enter a string to make a pyramid: ";
    std::getline(std::cin, user_provided);
    size_t length = user_provided.size();
    std::string reversed{user_provided};
    std::reverse(reversed.begin(), reversed.end());

    for (size_t i = 0; i < length; i++) {
        std::string indent_str(length - i, ' ');
        std::cout << indent_str
                  << user_provided.substr(0, i + 1)
                  << reversed.substr(length - i, length - 1)
                  << std::endl;
    }
}

void letter_pyramid1() {
    std::string user_provided;
    std::cout << "Enter a string to make a pyramid: ";
    std::getline(std::cin, user_provided);
    size_t length = user_provided.size();
    std::string full_str = std::string(length - 1, ' ') + user_provided;

    for (size_t i = 0; i < length; i++) {
        std::string cur_string{full_str, i, length};
        std::cout << cur_string;
        for (size_t j = 0; j < i; j++) {
            std::cout << cur_string.at(length - j - 2);
        }
        std::cout << std::endl;
    }
}

void c_math_functions() {

    double bill_total {102.78};
    int number_of_guests {5};

    double individual_bill{bill_total/number_of_guests};
    double individual_bill_1{floor(individual_bill)};
    double individual_bill_2{round(individual_bill)};
    double individual_bill_3{ceil(individual_bill*100)/100};

    std::cout << "The individual bill at location 1 will be $" << individual_bill_1
              << "\n" << "The individual bill at location 2 will be $"
              << individual_bill_2 << "\n"
              << "The individual bill at location 3 will be $" << individual_bill_3;
}

void display_menu() {
    std::cout << std::endl << "---------------------------" << std::endl
              << "P - Print numbers" << std::endl
              << "A - Add a number" << std::endl
              << "M - Display mean of the numbers" << std::endl
              << "S - Display the smallest number" << std::endl
              << "L - Display the largest number" << std::endl
              << "Q - Quit" << std::endl
              << "Please choose your option: ";
}

unsigned char get_user_input() {
    std::string option{};
    std::cin >> option;
    if(option.length()>1)
        std::cout << "Warning: multiple characters entered. "
                     "Taking last one '%s'.", option.back();
    unsigned char choice = option.back();
    return choice;
}

int modified_loop() {
    std::vector<int> numbers{};
    do {
        display_menu();
        unsigned char option = get_user_input();
        switch(option){
            case 'P':
            case 'p': funcWrapper(printNums, numbers); break;
            case 'A':
            case 'a': addNum(numbers); break;
            case 'M':
            case 'm': funcWrapper(meanOfNums, numbers); break;
            case 'S':
            case 's': funcWrapper(theNum, numbers, true); break;
            case 'L':
            case 'l': funcWrapper(theNum, numbers, false); break;
            case 'Q':
            case 'q': std::cout << "Goodbye" << std::endl; return 0;
        default:
            std::cout << "Unhandled reply " << option << " . Please try again"
                      << std::endl;
            usleep(1 * asecond);
        }
    } while (true);
}

void printArray(int* array, size_t size) {
    std::cout << "[ ";
    for (size_t i = 0; i < size; i++) {
        std::cout << " " << *(array + i) << " ";
    }
    std::cout << " ]" << std::endl;
}

int* applyAll(int* array1, size_t size1, int* array2, size_t size2) {
    int* result = new int[size1 * size2];
    for (size_t i = 0, j = 0; i < size2; i++) {
        for (size_t k = 0; k < size1; k++, j++) {
            result[j] = array2[i] * array1[k];
        }
    }
    return result;
}

void section12challenge(){
    int array1[] = {1,2,3,4,5};
    int array2[] = {10,20,30};

    std::cout << "Array 1: ";
    printArray(array1, 5);

    std::cout << "Array 2: ";
    printArray(array2, 3);

    int* applied = applyAll(array1, 5, array2, 3);
    std::cout << "Array 3: ";
    printArray(applied, 15);

    delete [] applied;

}

void for_memLeakTest(Test* testObj){
    UNUSED(testObj);
}

void memoryLeakTest(){
    for_memLeakTest(new Test());
}

class ForCpy {

public:
    ForCpy() {std::cout << "init constructor" << std::endl;}

    ForCpy(QString num) {
        std::cout << "default constructor "
                  << qUtf8Printable(num) << std::endl;
        m_num = num;
    }

    ForCpy(const ForCpy& other)
        : m_num(other.m_num)
        , m_copied(true)
        , m_nah(new int(*other.m_nah))
    {
        std::cout << "copy constructor "
                  << qUtf8Printable(other.m_num) << std::endl;
    }

    ForCpy& operator=(const ForCpy& other)
    {
        std::cout << "assignment operator "
                  << qUtf8Printable(other.m_num) << std::endl;
        m_num = other.m_num;
        m_nah = new int(*other.m_nah);
        m_copied = true;
        return *this;
    }

    ForCpy(ForCpy&& other) noexcept
        : m_num(other.m_num)
        , m_copied(false)
        , m_nah(other.m_nah)
    {
        other.m_nah = nullptr;
    }

    ForCpy& operator=(ForCpy&& other) noexcept
    {

    }

    bool copied() const {return m_copied;}
    void uncopy() {m_copied = false;}
    QString num() const {return m_num;}

private:
    QString m_num;
    bool m_copied = false;
    int* m_nah = nullptr;
};

class CopyTest {

public:
//    CopyTest(){}
//    explicit CopyTest(const CopyTest& other)
//    {
//        m_testHash = other.m_testHash;
//    }

//    CopyTest& operator=(const CopyTest& other);

    void insert(QString num) {m_testHash.insert(num, ForCpy(num));}
    void uncopyHash() {
        for (auto& i: m_testHash)
            i.uncopy();
    }
    void traverseHash() const {
        for(const auto& i: m_testHash)
            std::cout << "num " << qUtf8Printable(i.num())
                      << "| copied: " << i.copied() << std::endl;
    }

private:
    QHash<QString, ForCpy> m_testHash;
};

void redundantCopyTest(){
    int s = 1;
    void* aaa = &s;
    std::cout << aaa << std::endl;
    CopyTest cpy;
    cpy.insert("1");
    cpy.insert("2");
    std::string &&a = "1";
    a = "2";
    std::cout << "1" << std::endl;
    std::cout << a << std::endl;
    cpy.uncopyHash();
    cpy.traverseHash();

    CopyTest cpy1;
    cpy1.insert("5");
    cpy1.insert("6");
    cpy1.uncopyHash();
    cpy1.traverseHash();

    cpy = cpy1;
    cpy.traverseHash();
}

template <typename T>
    void printArray(const T& arr) {
        for (const auto& element: arr)
            std::cout << element << std::endl;
    }

template <int V>
    void prArr(std::array<int, V> array){
        for (int i = 0; i < V; i++)
            std::cout << array[i] << std::endl;
    }

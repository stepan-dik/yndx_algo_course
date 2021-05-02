#include <vector>
#include <string>
#include <iostream>
#include <QDebug>
#include <unistd.h>
#include <iomanip>
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
            case 'm': funcWrapper(meanOfNums,numbers); break;
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

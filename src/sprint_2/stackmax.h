#ifndef STACKMAX_H
#define STACKMAX_H

#include <iostream>
#include <string>
#include "stack.h"

// Stack for the task
class StackMax {
    Stack<int> values;
    Stack<int> maximums;

public:
    void push(int);
    RetVal<int> pop();
    RetVal<int> get_max();
};

#endif // STACKMAX_H

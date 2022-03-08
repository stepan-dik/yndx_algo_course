#include "stackmax.h"

void StackMax::push(int value)
{
    auto maxPeek = maximums.peek();
    if (!maxPeek.valid || value >= maxPeek.value)
        maximums.push(value);
    values.push(value);
}

RetVal<int> StackMax::pop()
{
    auto maxPeek = maximums.peek();
    if (!maxPeek.valid)
        return RetVal<int>{0, false};
    auto valuesPeek = values.peek();
    if (maxPeek.value == valuesPeek.value) {
        maximums.pop();
    }
    return values.pop();
}

RetVal<int> StackMax::get_max()
{
    return maximums.peek();
}

int main()
{
    StackMax theStack;
    int cmds = 0;
    std::string command;
    int arg;
    std::cin >> cmds;
    for (; cmds > 0; --cmds) {
        std::cin >> command;
        if (command == "push") {
            std::cin >> arg;
            theStack.push(arg);
        }
        else if (command == "pop") {
            auto result = theStack.pop();
            if (!result.valid)
                std::cout << "error" << std::endl;
        }
        else {
            auto result = theStack.get_max();
            if (!result.valid)
                std::cout << "None" << std::endl;
            else
                std::cout << result.value << std::endl;
        }
    }

    return 0;
}

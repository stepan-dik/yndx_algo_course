// do not declare Node in your submit-file
struct Node {
    Node* left;
    Node* right;
    int value;
};
//


#include <stack>
#include <queue>
#include <iostream>
//#include "solution.h" // Attention!

void print_LMR(Node* node)
{
    if (node == nullptr)
        return;
    std::stack<Node*> stack;
    bool just_popped = false;
    while (true) {
        if (node->left != nullptr && !just_popped) {
            stack.push(node);
            just_popped = false;
            node = node->left;
            continue;
        }
        std::cout << node->value << " ";
        if (node->right != nullptr) {
            node = node->right;
            just_popped = false;
            continue;
        }
        if (stack.empty())
            break;
        node = stack.top();
        stack.pop();
        just_popped = true;
    }
}

void print_range(Node* root, int L, int R)
{
    std::stack<Node*> stack;
    std::queue<Node*> queue;
    auto node = root;
    while (node != nullptr) {
        if (node->value >= L) {
            if (node->value <= R)
                stack.push(node);
            node = node->left;
            continue;
        }
        if (node->value < L)
            node = node->right;
    }
    node = root;
    while (node != nullptr) {
        if (node->value <= R) {
            if (node->value >= L)
                queue.push(node);
            node = node->right;
            continue;
        }
        if (node->value > R) {
            node = node->left;
        }
    }
    while (!stack.empty() && !queue.empty()) {
        if (stack.top()->value <= queue.front()->value) {
            std::cout << stack.top()->value << " ";
            if (stack.top() == queue.front()){
                queue.pop();
                break;
            }
            print_LMR(stack.top()->right);
            stack.pop();
        }
        else {
            std::cout << "excuse me wtf";
            std::cout << queue.front()->value;
            queue.pop();
        }
    }
    while (!queue.empty()) {
        print_LMR(queue.front()->left);
        std::cout << queue.front()->value << " ";
        queue.pop();
    }
    std::cout << std::endl;
}

int main()
{
    Node node1{.left = nullptr, .right = nullptr, .value=1};
    Node node3{.left = nullptr, .right = nullptr, .value=3};
    Node node6{.left = nullptr, .right = nullptr, .value=6};
    Node node6_1{.left = nullptr, .right = nullptr, .value=6};      /*                ___________14  */
    Node node9{.left = nullptr, .right = nullptr, .value=9};        /*               /               */
    Node node11{.left = nullptr, .right = nullptr, .value=11};      /*         ___ 8 ___             */
    Node node13{.left = nullptr, .right = nullptr, .value=13};      /*        /          \           */
    Node node2{.left = &node1, .right = &node3, .value=2};          /*     _4 _          _10_        */
    Node node5{.left = nullptr, .right = &node6, .value=5};         /*    /    \        /    \       */
    Node node7{.left = &node6_1, .right = nullptr, .value=7};       /*   2      6      9     12      */
    Node node12{.left = &node11, .right = &node13, .value=12};      /*  / \    / \          /  \     */
    Node node6_2{.left = &node5, .right = &node7, .value=6};        /* 1   3  5   7        11  13    */
    Node node10{.left = &node9, .right = &node12, .value=10};       /*        \  /                   */
    Node node4{.left = &node2, .right = &node6_2, .value=4};        /*         6 6                   */
    Node node8{.left = &node4, .right = &node10, .value=8};
    Node node14{.left = &node8, .right = nullptr, .value=14};
    print_range(&node14, 1, 2);
    print_range(&node14, 5, 14);
    print_range(&node14, 10, 21);
    print_range(&node14, 3, 6);

    return 0;
}

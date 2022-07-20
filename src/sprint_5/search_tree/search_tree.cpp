//#include "solution_tree.h"

#include <stack>
#include <iostream>
#include <optional>


struct Node{
  const Node* left = nullptr;
  const Node* right = nullptr;
  int value;
};

bool Solution(const Node* node)
{
    if (node == nullptr)
        return true;
    std::optional<int> l;
    std::optional<int> r;
    std::stack<const Node*> stack;
    bool just_popped = false;
    while (true) {
        if (node->left != nullptr && !just_popped) {
            if ((l && node->left->value <= l) || node->left->value >= node->value)
                return false;
            r = node->value;
            stack.push(node);
            just_popped = false;
            node = node->left;
            continue;
        }
        if (node->right != nullptr) {
            if (node->right->value <= node->value || (r && node->right->value >= r))
                return false;
            l = node->value;
            node = node->right;
            just_popped = false;
            continue;
        }
        if (stack.empty())
            break;
        node = stack.top();
        stack.pop();
        r = stack.empty() ? std::nullopt : std::optional<int>(stack.top()->value);
        just_popped = true;
    }
    return true;
}

int main()
{
    Node node1{.left = nullptr, .right = nullptr, .value=1};
    Node node3{.left = nullptr, .right = nullptr, .value=3};
    Node node6{.left = nullptr, .right = nullptr, .value=6};
    Node node6_1{.left = nullptr, .right = nullptr, .value=6};      /*                ___________14  */
    Node node9{.left = nullptr, .right = nullptr, .value=9};        /*               /               */
    Node node11{.left = nullptr, .right = nullptr, .value=11};      /*         ___ 8 ___             */
    Node node13{.left = nullptr, .right = nullptr, .value=13};      /*        /         \            */
    Node node2{.left = &node1, .right = &node3, .value=2};          /*     _4 _         _10_         */
    Node node5{.left = nullptr, .right = &node6, .value=5};         /*    /    \       /    \        */
    Node node7{.left = &node6_1, .right = nullptr, .value=7};       /*   2      6     9     12       */
    Node node12{.left = &node11, .right = &node13, .value=12};      /*  / \    / \         /  \      */
    Node node6_2{.left = &node5, .right = &node7, .value=6};        /* 1   3  5   7       11  13     */
    Node node10{.left = &node9, .right = &node12, .value=10};       /*        \  /                   */
    Node node4{.left = &node2, .right = &node6_2, .value=4};        /*         6 6                   */
    Node node8{.left = &node4, .right = &node10, .value=8};
    Node node14{.left = &node8, .right = nullptr, .value=14};
    std::cout << Solution(&node14) << std::endl;
    std::cout << std::endl;
    std::cout << Solution(&node4) << std::endl;
    std::cout << std::endl;
    std::cout << Solution(&node10) << std::endl;
    return 0;
}

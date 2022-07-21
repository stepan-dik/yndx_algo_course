#include <stack>
#include <iostream>

// do not declare Node in your submit-file
struct Node {
    Node* left;
    Node* right;
    int value;
};
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

Node* find_parent(Node* node, int key)
{
    while (true) {
        if (key < node->value) {
            if (node->left == nullptr)
                return nullptr;
            if (node->left->value != key)
                node = node->left;
            else
                return node;
        }
        else {
            if (node->right == nullptr)
                return nullptr;
            if (node->right->value != key)
                node = node->right;
            else
                return node;
        }
    }
}

void replace_node(Node* parent, int key, Node* child = nullptr)
{
    if (child != nullptr) {
        if (key < parent->value) {
            child->left = parent->left->left;
            child->right = parent->left->right;
        }
        else {
            child->left = parent->right->left;
            child->right = parent->right->right;
        }
    }

    if (key < parent->value)
        parent->left = child;
    else
        parent->right = child;
}

Node* remove(Node* root, int key)
{
    auto parent = find_parent(root, key);
    if (parent == nullptr)
        return root;

    auto to_remove = key < parent->value ? parent->left : parent->right;
    if (to_remove->left == nullptr && to_remove->right == nullptr) {
        replace_node(parent, key);
        return root;
    }
    else if (to_remove->left == nullptr || to_remove->right == nullptr){
        auto child = to_remove->left == nullptr ?
                                                to_remove->right :
                                                to_remove->left;
        replace_node(parent, key, child);
        return root;
    }
    else {
        auto trav_node = to_remove->left;
        if (trav_node->right == nullptr) {
            replace_node(to_remove, trav_node->value, trav_node);
            return root;
        }
        while (trav_node->right->right != nullptr)
            trav_node = trav_node->right;
        replace_node(trav_node, trav_node->right->value, trav_node->right->left);
        replace_node(parent, key, trav_node->right);
    }

    return root;
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

//    auto p = find_parent(&node14, 10);
    remove(&node14, 6);
    print_LMR(&node14);

    return 0;
}

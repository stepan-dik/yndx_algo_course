#include <stack>
#include <iostream>
#include <cassert>

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
        std::cout << node->value << " " << std::flush;
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

void print_forward(Node* root)
{
    if (root == nullptr)
        return;
    std::cout << root->value << " ";
    print_forward(root->left);
    print_forward(root->right);
}

Node* find_parent(Node* node, int key)
{
    while (true) {
        if (node->value == key)
            return node;
        else if (key < node->value) {
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
    if (key < parent->value)
        parent->left = child;
    else
        parent->right = child;
}

Node* remove(Node* root, int key)
{
    if (root == nullptr)
        return root;
    Node* parent = nullptr;
    if (key != root->value) {
        parent = find_parent(root, key);
        if (parent == nullptr)
            return root;
    }

    Node* to_remove = root;
    if (parent != nullptr)
        to_remove = key < parent->value ? parent->left : parent->right;

    if (to_remove->left == nullptr && to_remove->right == nullptr) {
        if (to_remove == root)
            return nullptr;
        replace_node(parent, key);
        return root;
    }
    else if (to_remove->left == nullptr || to_remove->right == nullptr){
        auto child = to_remove->left == nullptr ?
                                                to_remove->right :
                                                to_remove->left;
        if (to_remove == root)
            return child;
        replace_node(parent, key, child);
        return root;
    }
    else {
        auto parent_of_new = to_remove->left;
        if (parent_of_new->right == nullptr) {
            parent_of_new->right = to_remove->right;
            if (to_remove == root)
                return parent_of_new;
            replace_node(parent, key, parent_of_new);
            return root;
        }
        while (parent_of_new->right->right != nullptr)
            parent_of_new = parent_of_new->right;
        auto child = parent_of_new->right;
        parent_of_new->right = child->left;

        if (to_remove == root) {
            child->left = root->left;
            child->right = root->right;
            return child;
        }
        else if (key < parent->value) {
            child->left = parent->left->left;
            child->right = parent->left->right;
        }
        else {
            child->left = parent->right->left;
            child->right = parent->right->right;
        }
        replace_node(parent, key, child);
    }

    return root;
}

void test() {
    Node node1({nullptr, nullptr, 2});
    Node node2({&node1, nullptr, 3});
    Node node3({nullptr, &node2, 1});
    Node node4({nullptr, nullptr, 6});
    Node node5({&node4, nullptr, 8});
    Node node6({&node5, nullptr, 10});
    Node node7({&node3, &node6, 5});
    Node* newHead = remove(&node7, 10);
    assert(newHead->value == 5);
    assert(newHead->right == &node5);
    assert(newHead->right->value == 8);
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
    print_LMR(&node14);
    std::cout << std::endl;
    print_forward(&node14);
    std::cout << std::endl;
    auto new_node = remove(&node14, 14);
    new_node = remove(new_node, 8);
    print_LMR(new_node);
    std::cout << std::endl;
    print_forward(new_node);
    std::cout << std::endl;
    test();

    return 0;
}

/*
 *              --- ПРИНЦИП РАБОТЫ ---
 *   Корень проверяется на nullptr. Если корень не nullptr, а удаляемый
 * узел - не корень, то ищется родительский узел для удаляемого узла.
 * Далее рассматривается 3 варианта наличия потомков у удаляемого узла.
 *   1. Если у удаляемого узла нет потомков, то ссылка на него от родительского
 * узла заменяется на nullptr (в случае, когда удалется корень, дерево
 * перестает существовать, возвращается nullptr).
 *   2. Если у удаляемого узла 1 потомок, то удаляемый узел заменяется своим
 * прямым потомком.
 *   3. Если у удаляемого узла 2 потомка, то производится поиск самого правого
 * потомка в левом поддереве, который изымается из поддерева как в случае 1
 * или 2 и заменяет удаляемый узел.
 *
 *              --- ВРЕМЕННАЯ СЛОЖНОСТЬ ---
 *   Сложность поиска удаляемого узла O(log(n)), для худшего случая, когда
 * дерево представляет собой связный список, O(n), такие же порядки сложности
 * для поиска заменяющего узла. O(1) для непосредственно замены ссылок.
 *
 *              --- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ ---
 *   Пространственная сложность O(1).
 *
 */

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
    Node* parent = nullptr;
    while (node != nullptr) {
        if (node->value == key)
            return parent;

        parent = node;
        if (key < node->value)
            node = node->left;
        else if (key > node->value)
            node = node->right;
    }
    return nullptr;
}

Node* new_root(Node* root, Node* parent, int key, Node* child = nullptr)
{
    if (parent == nullptr)
        return child;

    if (key < parent->value)
        parent->left = child;
    else
        parent->right = child;
    return root;
}

Node* remove_iterative(Node* root, int key)
{
    if (root == nullptr)
        return nullptr;
    Node* parent = nullptr;
    if (key != root->value) {
        parent = find_parent(root, key);
        if (parent == nullptr)
            return root;
    }

    Node* to_remove = root;
    if (parent != nullptr) // parent is a nullptr if root is to be removed
        to_remove = key < parent->value ? parent->left : parent->right;

    if (to_remove->left == nullptr && to_remove->right == nullptr) {
        return new_root(root, parent, key);
    }
    else if (to_remove->left == nullptr || to_remove->right == nullptr) {
        auto child = to_remove->left == nullptr ?
                                                to_remove->right :
                                                to_remove->left;
        return new_root(root, parent, key, child);
    }
    else {
        auto replacer = to_remove->left;
        Node* prev = nullptr;

        while (replacer->right != nullptr) {
            prev = replacer;
            replacer = replacer->right;
        }

        if (prev != nullptr) {
            prev->right = replacer->left;
            replacer->left = to_remove->left;
        }
        replacer->right = to_remove->right;

        return new_root(root, parent, key, replacer);
    }
}

Node* remove(Node* root, int key)
{
    if (root == nullptr)
        return root;
    else if (key < root->value)
        root->left = remove(root->left, key);
    else if (key > root->value)
        root->right = remove(root->right, key);
    else {
        if (root->left == nullptr && root->right == nullptr)
            return nullptr;
        else if (root->left == nullptr || root->right == nullptr) {
            auto child = root->left == nullptr ? root->right : root->left;
            return child;
        }
        else {
            auto replacer = root->left;
            Node* prev = nullptr;
            while (replacer->right != nullptr) {
                prev = replacer;
                replacer = replacer->right;
            }

            if (prev != nullptr) {
                prev->right = replacer->left;
                replacer->left = root->left;
            }
            replacer->right = root->right;
            return replacer;
        }
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
//    print_LMR(&node14);
    std::cout << std::endl;
    print_forward(&node14);
    std::cout << std::endl;
    auto new_node = remove_iterative(&node14, 8);
//    new_node = remove(new_node, 8);
//    print_LMR(new_node);
//    std::cout << std::endl;
    print_forward(new_node);
    std::cout << std::endl;
    test();

    return 0;
}

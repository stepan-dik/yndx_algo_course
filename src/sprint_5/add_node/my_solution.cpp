#include "solution.h" // Attention!

Node* insert(Node* root, int key)
{
    auto node = root;
    while (node != nullptr) {
        if (key < node->value){
            if (node->left != nullptr)
                node = node->left;
            else {
                node->left = new Node{nullptr, nullptr, key};
                break;
            }
        }
        else {
            if (node->right != nullptr)
                node = node->right;
            else {
                node->right = new Node{nullptr, nullptr, key};
                break;
            }
        }
    }
    return root;
}

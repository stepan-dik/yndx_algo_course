#include <iostream>


struct Node {
  int value;
  const Node* left = nullptr;
  const Node* right = nullptr;
};


//#include "solution_tree.h"
#include <cassert>

using namespace std;

int Solution(const Node* root) {
    if (root == nullptr)
        return 0;
    int l = Solution(root->left);
    int r = Solution(root->right);
    return max(l,r) + 1;
}

void test() {
    Node node1({1, nullptr, nullptr});
    Node node2({4, nullptr, nullptr});
    Node node3({3, &node1, &node2});
    Node node4({8, nullptr, nullptr});
    Node node5({5, &node3, &node4});
    assert(Solution(&node5) == 3);
}

int main()
{
    Node node1  {  .value=1 , .left = nullptr, .right = nullptr };
    Node node3  {  .value=3 , .left = nullptr, .right = nullptr };
    Node node6  {  .value=6 , .left = nullptr, .right = nullptr };
    Node node6_1{  .value=6 , .left = nullptr, .right = nullptr };         /*                ___________14  */
    Node node9  {  .value=9 , .left = nullptr, .right = nullptr };         /*               /               */
    Node node11 {  .value=11, .left = nullptr, .right = nullptr };         /*         ___ 8 ___             */
    Node node13 {  .value=13, .left = nullptr, .right = nullptr };         /*        /          \           */
    Node node2  {  .value=2 , .left = &node1, .right = &node3  };          /*     _4 _          _10_        */
    Node node5  {  .value=5 , .left = nullptr, .right = &node6  };         /*    /    \        /    \       */
    Node node7  {  .value=7 , .left = &node6_1, .right = nullptr};         /*   2      6      9     12      */
    Node node12 {  .value=12, .left = &node11, .right = &node13 };         /*  / \    / \          /  \     */
    Node node6_2{  .value=6 , .left = &node5, .right = &node7   };         /* 1   3  5   7        11  13    */
    Node node10 {  .value=10, .left = &node9, .right = &node12  };         /*        \  /                   */
    Node node4  {  .value=4 , .left = &node2, .right = &node6_2 };         /*         6 6                   */
    Node node8  {  .value=8 , .left = &node4, .right = &node10  };
    Node node14 {  .value=14, .left = &node8, .right = nullptr  };

    cout << Solution(&node1) << endl;
    cout << Solution(&node4) << endl;
    cout << Solution(&node6_2) << endl;
    test();

    return 0;
}

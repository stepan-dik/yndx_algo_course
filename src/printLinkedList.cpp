#include "solution.h"

/*
Comment it before submitting
struct Node {  
    std::string value;  
    Node* next;  
    Node(const std::string &value, Node* next);  
};
*/

void solution(Node* head) {
    while (head != nullptr) {
        std::cout << head->value << std::endl;
        head = head->next;
    }
}

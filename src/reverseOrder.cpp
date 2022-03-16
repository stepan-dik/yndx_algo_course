#include "solution.h"

using namespace reverse;
namespace{
Node* solution(Node* head) {
    Node* nxt = nullptr;
    Node* cur = nullptr;
    while (head != nullptr) {
        cur = head;
        nxt = head->next;
        head->next = head->prev;
        head->prev = nxt;
        head = nxt;
    }
    return cur;
}
}

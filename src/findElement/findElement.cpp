#include "solution.h"
using namespace reverse;

int solution(Node* head, const std::string& element) {
    for (int i = 0; head->next != nullptr; ++i) {
        if (head->value == element)
            return i;
        head = head->next;
    }
    return -1;
}

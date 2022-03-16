#include "solution.h"
using namespace reverse;

Node* solution(Node* head, int idx)
{
    auto curEl = head;
    if (idx == 0)
        return head->next;
    for (int i = 0; i < idx -1; ++i)
        curEl = curEl->next;
    curEl->next = (curEl->next->next);
    return head;
}

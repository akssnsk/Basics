#include <vector>
#include <stdlib.h>
#include <time.h>

#include "List.h"

typedef ListNode<int> ListNodeInt;

void ListsAlgorithmRun()
{
    int nElem = 10;
    srand((unsigned int)time(NULL));

    std::vector<int> printVector;
    for (int i = 0; i < nElem; i++)
    {
        int num = rand() % 100;

        if (rand() % 2)
            num *= -1;

        printVector.push_back(num);
    }

    ListNodeInt *top = nullptr;

    for (int num : printVector)
    {
        ListNodeInt *n = new ListNodeInt(num);

        if (top == nullptr)
        {
            top = n;
            continue;
        }
        else
        {
            n->pNext = top;
            top = n;
        }
    }

    ListNodeInt *t = top;

    while (t != nullptr)
    {
        printf("%d ", t->data);
        t = t->pNext;
    }

    printf("\n");

    top = Reverse(top);

    t = top;
    while (t != nullptr)
    {
        printf("%d ", t->data);
        t = t->pNext;
    }

    printf("\n");

    top = ReverseRecursively(top);

    t = top;
    while (t != nullptr)
    {
        printf("%d ", t->data);
        t = t->pNext;
    }
}
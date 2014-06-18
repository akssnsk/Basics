#include <stdio.h>

#include <iostream>

void NumberPlay()
{
    /// -----------------
    int iVar = 1;
    iVar = iVar++;
    int iLen = 3;
    iVar = iVar++ % iLen, 4, 6;

    /// -------------------

    int i = 0;
    i = 10;
    bool bRes1 = (++i == i++);
    bool bRes2 = (i++ == ++i);
    bool bRes3 = (++i == ++i);
    bool bRes4 = (i++ == i++);

    bool bRes5 = (i++ == --i);
    bool bRes6 = (i++ == i--);
    bool bRes7 = (i-- == ++i);
    bool bRes8 = (i-- == i++);

    for (int i = 0,  j = printf("init "); i < 2 && printf("cmp "); i++, std::cout << "step ")
    {
        printf("loop ");
    }
}
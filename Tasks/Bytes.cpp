
#include <stdlib.h>

#include "Bytes.h"

char get_byte()
{
    static int idx = -1;
    static int len = 300;

    while (true)
    {
        idx++;
        
        if (idx == 0)
        {
            int mask = 0xff00;
            int retVal = (len & mask) >> 8;
            return retVal;
        }
        else if (idx == 1)
        {
            int mask = 0x00ff;
            char retVal = (char)(len & mask);
            return retVal;
        }

        if (idx < len)
            return (char)idx % 0xff;

        idx = 0;
        len = rand() % 10000;
        
        continue;
    }

}

size_t recv(char* buf, size_t size)
{
    if (size < 3)
        return 0; // buf is too small

    char *pBuf = buf;
    *(pBuf+1) = get_byte();
    *pBuf     = get_byte();

    short packetLen = *(short*)buf;
    if (size < packetLen)
        return 0; // buf is too small

    pBuf += 2; // skip the size

    for (short i = 0; i < packetLen - 2; i++)
    {
        char c = get_byte();
        *pBuf = c;
        pBuf++;
    }

    return packetLen;
}


void ReveiveData()
{
    std::vector<char> buf1(1<<16);

    size_t recBytes1 = recv(&buf1[0], buf1.size());
    
    std::vector<char> buf2(1 << 16);

    size_t recBytes2 = recv(&buf2[0], buf2.size());

}

void ByteTasks()
{
    ReveiveData();
}

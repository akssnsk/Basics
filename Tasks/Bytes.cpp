
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
    if (size < (size_t)packetLen)
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

std::pair<unsigned short, unsigned short> MaxXorPreparer(std::istream &input)
{
    size_t intL, intR;
    input >> intL;
    input.ignore();

    input >> intR;
    input.ignore();

    return std::make_pair(intL, intR);
}

//R : 6, 0x110 | 5, 0x101 | 61, 0x111101
//L : 5, 0x101 | 1, 0x001 | 5,  0x000101
//S : 3, 0x011 | 7, 0x111 | --, 0x111111

unsigned short MaxXorSolver(unsigned short L, unsigned short R)
{
#if 1
    short res2 = L ^ R;

    int a = L, b = R;
    for (short i = L; i <= R; i++)
    {
        for (short j = L; j <= R; j++)
        {
            short tmpMax = (i ^ j);
            if (res2 < tmpMax)
            {
                a = i; b = j;
                res2 = tmpMax;
            }
        }
    }
#endif

    unsigned short res = L^R;

    int msb = 0;
    while (res != 0)
    {
        res >>= 1;
        msb++;
    }

    res = 1 << msb;
    res--;

    return res;
}
void MaxXor()
{
    std::string strData = "5\n61\n";
    std::istringstream inStr(strData);

    //std::istream &dataStream = std::cin;
    std::istream &dataStream = inStr;

    auto lr = MaxXorPreparer(dataStream);
    int iRes = MaxXorSolver(lr.first, lr.second);

    std::cout << iRes << std::endl;
}


void ByteTasks()
{
    MaxXor();

    //ReveiveData();
}

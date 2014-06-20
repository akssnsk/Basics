#include "StringTasks.h"

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>



void normalizeSentence(/* in, out */std::string& str)
{
    if (str.empty())
        return;

    // remove leading and trailing spaces
    size_t i1 = 0;
    size_t i2 = str.size() - 1;
    while (str[i1] == ' ')
    {
        i1++;
    }

    while (str[i2] == ' ')
    {
        i2--;
    }

    str = str.substr(i1, (i2-i1)+1);

    // remove spaces in the middle
    i1 = 0;
    i2 = i1;

    while (i2 < str.size())
    {
        if (str[i2] == ' ' && str[i2 + 1] == ' ')
        {
            i2++;
            continue;
        }

        str[i1] = str[i2];
        i1++; i2++;
    }

    str = str.substr(0, i1);

    return;
}


void reverseSentence(/* in, out */std::string& str)
{
    if (str.empty())
        return;

    // 0: Normalize the string
    // the     word -> the word

    normalizeSentence(str);

    // I: reverse words
    // the word -> eht drow and so on

    size_t i1 = 0;
    while (i1 < str.size())
    {
        size_t i2 = i1 + 1;

        // find the ending of the 1st word
        while (str[i2] != ' ' && i2 < str.size())
        {
            i2++;
        }

        size_t length = (i2 - i1); // 3 for "the"
        //std::cout << i1 << " " << i2 << " " << length << std::endl;
        for (size_t i = 0; i < length / 2; i++)
        {
            std::swap(str[i1 + i], str[i2 - i - 1]);
        }

        i1 += length + 1;
    }

    // II: reverse the string
    // eht drow -> word the

    // just to remember: std::rotate(str.begin(), str.end());

    for (size_t i = 0; i < str.size() / 2; i++)
    {
        std::swap(str[i], str[str.size() - i - 1]);
    }

    return;
}


void StringTaskRun()
{

    std::vector<std::string> strVect = { 
        "the",
        "the word",
        "the sentence with more words",
        "the spaces in the end     ",
        "     the spaces in the beginning",
        "the spaces in the      middle",
        "    the   spaces  everywhere   "
    };

    for (auto &s : strVect)
    {
        reverseSentence(s);
    }

    return;
}
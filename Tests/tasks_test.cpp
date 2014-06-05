
#include "Tasks.h"

#include <strstream>
#include "gtest/gtest.h"

TEST(Tasks, AnagramPos1) 
{
  EXPECT_TRUE(IsAnagram("str1", "str1"));
}

TEST(Tasks, AnagramPos2) 
{
  EXPECT_TRUE(IsAnagram("str1", "s1tr"));
}

TEST(Tasks, AnagramNeg1) 
{
  EXPECT_FALSE(IsAnagram("str1", "str2"));
}

TEST(Tasks, AnagramNeg2) 
{
  EXPECT_FALSE(IsAnagram("str1", "s2tr"));
}


TEST(Tasks, CutTheTreePrep1)
{
    NodeType edges;

    std::string input =
        "6\n"
        "100 200 100 500 100 600\n"
        "1 2 "
        "2 3\n"
        "2 5\n"
        "4 5\n"
        "5 6\n";

    char *inp = (char *)input.c_str();
    std::strstream inStr(inp, input.size());
    CutTheTreePreparer(inStr, &edges);

    EXPECT_EQ(edges.size(), 6);
    EXPECT_EQ(edges[1].conn.size(), 3);
}

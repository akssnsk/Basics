
#include "Tasks.h"

#include "gtest/gtest.h"

TEST(Tasks, AnagramPos1) {
  EXPECT_TRUE(IsAnagram("str1", "str1"));
}

TEST(Tasks, AnagramPos2) {
  EXPECT_TRUE(IsAnagram("str1", "s1tr"));
}

TEST(Tasks, AnagramNeg1) {
  EXPECT_FALSE(IsAnagram("str1", "str2"));
}

TEST(Tasks, AnagramNeg2) {
  EXPECT_FALSE(IsAnagram("str1", "s2tr"));
}


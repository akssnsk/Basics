
#include "Cpp.h"

#include "gtest/gtest.h"

TEST(Cpp, IsPrimePos1) {
	EXPECT_TRUE(IsPrime(11));
}

TEST(Cpp, IsPrimeNeg1) {
	EXPECT_FALSE(IsPrime(10));
}


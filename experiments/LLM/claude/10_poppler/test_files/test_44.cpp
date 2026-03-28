#include <gtest/gtest.h>
#include <climits>
#include <limits>

// Declaration of the function under test
typedef long long Goffset;
Goffset GoffsetMax();

TEST(GoffsetMaxTest_44, ReturnsPositiveValue_44)
{
    Goffset result = GoffsetMax();
    EXPECT_GT(result, 0);
}

TEST(GoffsetMaxTest_44, ReturnsConsistentValue_44)
{
    Goffset first = GoffsetMax();
    Goffset second = GoffsetMax();
    EXPECT_EQ(first, second);
}

TEST(GoffsetMaxTest_44, ReturnValueIsAtLeastLongMax_44)
{
    // Regardless of platform, the return value should be at least as large as LONG_MAX
    Goffset result = GoffsetMax();
    EXPECT_GE(result, static_cast<Goffset>((std::numeric_limits<long>::max)()));
}

TEST(GoffsetMaxTest_44, ReturnValueIsNonZero_44)
{
    Goffset result = GoffsetMax();
    EXPECT_NE(result, 0);
}

TEST(GoffsetMaxTest_44, ReturnValueFitsInGoffset_44)
{
    // The return value should not exceed the max of Goffset itself
    Goffset result = GoffsetMax();
    EXPECT_LE(result, (std::numeric_limits<Goffset>::max)());
}

TEST(GoffsetMaxTest_44, ReturnValueIsLargeEnoughForTypicalFileOffsets_44)
{
    // Should support at least 2GB file sizes (INT32_MAX)
    Goffset result = GoffsetMax();
    EXPECT_GE(result, static_cast<Goffset>(2147483647LL));
}

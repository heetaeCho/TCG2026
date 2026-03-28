#include <gtest/gtest.h>

// Include necessary headers
#include "GfxFont.h"

// We need to define the functor as it appears in the source
// Based on the partial code provided
struct cmpWidthExcepFunctor
{
    bool operator()(const GfxFontCIDWidthExcep w1, const GfxFontCIDWidthExcep w2)
    {
        return w1.first < w2.first;
    }
};

class CmpWidthExcepFunctorTest_1971 : public ::testing::Test {
protected:
    cmpWidthExcepFunctor comparator;
};

// Test that w1.first < w2.first returns true
TEST_F(CmpWidthExcepFunctorTest_1971, FirstLessThanSecond_ReturnsTrue_1971)
{
    GfxFontCIDWidthExcep w1;
    GfxFontCIDWidthExcep w2;
    w1.first = 1;
    w1.last = 10;
    w2.first = 5;
    w2.last = 20;

    EXPECT_TRUE(comparator(w1, w2));
}

// Test that w1.first > w2.first returns false
TEST_F(CmpWidthExcepFunctorTest_1971, FirstGreaterThanSecond_ReturnsFalse_1971)
{
    GfxFontCIDWidthExcep w1;
    GfxFontCIDWidthExcep w2;
    w1.first = 10;
    w1.last = 20;
    w2.first = 5;
    w2.last = 15;

    EXPECT_FALSE(comparator(w1, w2));
}

// Test that w1.first == w2.first returns false (strict less than)
TEST_F(CmpWidthExcepFunctorTest_1971, EqualFirstValues_ReturnsFalse_1971)
{
    GfxFontCIDWidthExcep w1;
    GfxFontCIDWidthExcep w2;
    w1.first = 5;
    w1.last = 10;
    w2.first = 5;
    w2.last = 20;

    EXPECT_FALSE(comparator(w1, w2));
}

// Test with zero values
TEST_F(CmpWidthExcepFunctorTest_1971, ZeroValues_1971)
{
    GfxFontCIDWidthExcep w1;
    GfxFontCIDWidthExcep w2;
    w1.first = 0;
    w1.last = 0;
    w2.first = 0;
    w2.last = 0;

    EXPECT_FALSE(comparator(w1, w2));
}

// Test with zero less than nonzero
TEST_F(CmpWidthExcepFunctorTest_1971, ZeroLessThanNonZero_ReturnsTrue_1971)
{
    GfxFontCIDWidthExcep w1;
    GfxFontCIDWidthExcep w2;
    w1.first = 0;
    w1.last = 5;
    w2.first = 1;
    w2.last = 10;

    EXPECT_TRUE(comparator(w1, w2));
}

// Test that the 'last' field does not affect comparison
TEST_F(CmpWidthExcepFunctorTest_1971, LastFieldDoesNotAffectComparison_1971)
{
    GfxFontCIDWidthExcep w1;
    GfxFontCIDWidthExcep w2;
    w1.first = 3;
    w1.last = 100;
    w2.first = 3;
    w2.last = 1;

    EXPECT_FALSE(comparator(w1, w2));
    EXPECT_FALSE(comparator(w2, w1));
}

// Test consecutive values
TEST_F(CmpWidthExcepFunctorTest_1971, ConsecutiveFirstValues_1971)
{
    GfxFontCIDWidthExcep w1;
    GfxFontCIDWidthExcep w2;
    w1.first = 4;
    w1.last = 10;
    w2.first = 5;
    w2.last = 10;

    EXPECT_TRUE(comparator(w1, w2));
    EXPECT_FALSE(comparator(w2, w1));
}

// Test with large CID values
TEST_F(CmpWidthExcepFunctorTest_1971, LargeCIDValues_1971)
{
    GfxFontCIDWidthExcep w1;
    GfxFontCIDWidthExcep w2;
    w1.first = 65534;
    w1.last = 65535;
    w2.first = 65535;
    w2.last = 65535;

    EXPECT_TRUE(comparator(w1, w2));
    EXPECT_FALSE(comparator(w2, w1));
}

// Test reflexivity - an element is not less than itself
TEST_F(CmpWidthExcepFunctorTest_1971, Irreflexivity_1971)
{
    GfxFontCIDWidthExcep w;
    w.first = 42;
    w.last = 100;

    EXPECT_FALSE(comparator(w, w));
}

// Test antisymmetry - if a < b then !(b < a)
TEST_F(CmpWidthExcepFunctorTest_1971, Antisymmetry_1971)
{
    GfxFontCIDWidthExcep w1;
    GfxFontCIDWidthExcep w2;
    w1.first = 10;
    w1.last = 20;
    w2.first = 20;
    w2.last = 30;

    EXPECT_TRUE(comparator(w1, w2));
    EXPECT_FALSE(comparator(w2, w1));
}

// Test transitivity - if a < b and b < c then a < c
TEST_F(CmpWidthExcepFunctorTest_1971, Transitivity_1971)
{
    GfxFontCIDWidthExcep w1, w2, w3;
    w1.first = 1;
    w1.last = 5;
    w2.first = 2;
    w2.last = 5;
    w3.first = 3;
    w3.last = 5;

    EXPECT_TRUE(comparator(w1, w2));
    EXPECT_TRUE(comparator(w2, w3));
    EXPECT_TRUE(comparator(w1, w3));
}

// Test usability with std::sort (functional integration)
#include <algorithm>
#include <vector>

TEST_F(CmpWidthExcepFunctorTest_1971, UsableWithStdSort_1971)
{
    std::vector<GfxFontCIDWidthExcep> vec(4);
    vec[0].first = 30; vec[0].last = 40;
    vec[1].first = 10; vec[1].last = 20;
    vec[2].first = 50; vec[2].last = 60;
    vec[3].first = 20; vec[3].last = 30;

    std::sort(vec.begin(), vec.end(), comparator);

    EXPECT_EQ(vec[0].first, 10);
    EXPECT_EQ(vec[1].first, 20);
    EXPECT_EQ(vec[2].first, 30);
    EXPECT_EQ(vec[3].first, 50);
}

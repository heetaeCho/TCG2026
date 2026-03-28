#include <gtest/gtest.h>

// Include necessary headers
// Based on the provided code, we need the GfxFont structures
// We'll define the minimal structures needed since we're testing the functor

struct GfxFontCIDWidthExcepV {
    int first;
    int last;
    double height;
    double vx;
    double vy;
};

struct cmpWidthExcepVFunctor {
    bool operator()(const GfxFontCIDWidthExcepV &w1, const GfxFontCIDWidthExcepV &w2) {
        return w1.first < w2.first;
    }
};

class CmpWidthExcepVFunctorTest_1972 : public ::testing::Test {
protected:
    cmpWidthExcepVFunctor comparator;
};

// Test that w1.first < w2.first returns true
TEST_F(CmpWidthExcepVFunctorTest_1972, FirstLessThanSecond_ReturnsTrue_1972) {
    GfxFontCIDWidthExcepV w1 = {1, 0, 0.0, 0.0, 0.0};
    GfxFontCIDWidthExcepV w2 = {2, 0, 0.0, 0.0, 0.0};
    EXPECT_TRUE(comparator(w1, w2));
}

// Test that w1.first > w2.first returns false
TEST_F(CmpWidthExcepVFunctorTest_1972, FirstGreaterThanSecond_ReturnsFalse_1972) {
    GfxFontCIDWidthExcepV w1 = {5, 0, 0.0, 0.0, 0.0};
    GfxFontCIDWidthExcepV w2 = {3, 0, 0.0, 0.0, 0.0};
    EXPECT_FALSE(comparator(w1, w2));
}

// Test that w1.first == w2.first returns false (strict less-than)
TEST_F(CmpWidthExcepVFunctorTest_1972, EqualFirstValues_ReturnsFalse_1972) {
    GfxFontCIDWidthExcepV w1 = {4, 0, 0.0, 0.0, 0.0};
    GfxFontCIDWidthExcepV w2 = {4, 0, 0.0, 0.0, 0.0};
    EXPECT_FALSE(comparator(w1, w2));
}

// Test with zero values
TEST_F(CmpWidthExcepVFunctorTest_1972, BothZeroFirst_ReturnsFalse_1972) {
    GfxFontCIDWidthExcepV w1 = {0, 0, 0.0, 0.0, 0.0};
    GfxFontCIDWidthExcepV w2 = {0, 0, 0.0, 0.0, 0.0};
    EXPECT_FALSE(comparator(w1, w2));
}

// Test with negative values
TEST_F(CmpWidthExcepVFunctorTest_1972, NegativeFirstLessThanPositive_ReturnsTrue_1972) {
    GfxFontCIDWidthExcepV w1 = {-1, 0, 0.0, 0.0, 0.0};
    GfxFontCIDWidthExcepV w2 = {1, 0, 0.0, 0.0, 0.0};
    EXPECT_TRUE(comparator(w1, w2));
}

// Test with negative values where first is greater
TEST_F(CmpWidthExcepVFunctorTest_1972, NegativeFirstGreaterThanMoreNegative_ReturnsFalse_1972) {
    GfxFontCIDWidthExcepV w1 = {-1, 0, 0.0, 0.0, 0.0};
    GfxFontCIDWidthExcepV w2 = {-5, 0, 0.0, 0.0, 0.0};
    EXPECT_FALSE(comparator(w1, w2));
}

// Test that other fields don't affect comparison
TEST_F(CmpWidthExcepVFunctorTest_1972, DifferentOtherFields_OnlyFirstMatters_1972) {
    GfxFontCIDWidthExcepV w1 = {1, 100, 999.0, 888.0, 777.0};
    GfxFontCIDWidthExcepV w2 = {2, 0, 0.0, 0.0, 0.0};
    EXPECT_TRUE(comparator(w1, w2));
}

// Test with large values
TEST_F(CmpWidthExcepVFunctorTest_1972, LargeFirstValues_1972) {
    GfxFontCIDWidthExcepV w1 = {999999, 0, 0.0, 0.0, 0.0};
    GfxFontCIDWidthExcepV w2 = {1000000, 0, 0.0, 0.0, 0.0};
    EXPECT_TRUE(comparator(w1, w2));
}

// Test antisymmetry: if a < b then !(b < a)
TEST_F(CmpWidthExcepVFunctorTest_1972, Antisymmetry_1972) {
    GfxFontCIDWidthExcepV w1 = {3, 0, 0.0, 0.0, 0.0};
    GfxFontCIDWidthExcepV w2 = {7, 0, 0.0, 0.0, 0.0};
    EXPECT_TRUE(comparator(w1, w2));
    EXPECT_FALSE(comparator(w2, w1));
}

// Test irreflexivity: !(a < a)
TEST_F(CmpWidthExcepVFunctorTest_1972, Irreflexivity_1972) {
    GfxFontCIDWidthExcepV w1 = {42, 0, 0.0, 0.0, 0.0};
    EXPECT_FALSE(comparator(w1, w1));
}

// Test transitivity: if a < b and b < c then a < c
TEST_F(CmpWidthExcepVFunctorTest_1972, Transitivity_1972) {
    GfxFontCIDWidthExcepV w1 = {1, 0, 0.0, 0.0, 0.0};
    GfxFontCIDWidthExcepV w2 = {2, 0, 0.0, 0.0, 0.0};
    GfxFontCIDWidthExcepV w3 = {3, 0, 0.0, 0.0, 0.0};
    EXPECT_TRUE(comparator(w1, w2));
    EXPECT_TRUE(comparator(w2, w3));
    EXPECT_TRUE(comparator(w1, w3));
}

// Test consecutive values
TEST_F(CmpWidthExcepVFunctorTest_1972, ConsecutiveValues_1972) {
    GfxFontCIDWidthExcepV w1 = {0, 0, 0.0, 0.0, 0.0};
    GfxFontCIDWidthExcepV w2 = {1, 0, 0.0, 0.0, 0.0};
    EXPECT_TRUE(comparator(w1, w2));
    EXPECT_FALSE(comparator(w2, w1));
}

// Test usability with std::sort (functor as comparator)
#include <algorithm>
#include <vector>

TEST_F(CmpWidthExcepVFunctorTest_1972, UsableWithStdSort_1972) {
    std::vector<GfxFontCIDWidthExcepV> vec;
    vec.push_back({5, 0, 0.0, 0.0, 0.0});
    vec.push_back({1, 0, 0.0, 0.0, 0.0});
    vec.push_back({3, 0, 0.0, 0.0, 0.0});
    vec.push_back({2, 0, 0.0, 0.0, 0.0});
    vec.push_back({4, 0, 0.0, 0.0, 0.0});

    std::sort(vec.begin(), vec.end(), comparator);

    for (size_t i = 0; i < vec.size(); ++i) {
        EXPECT_EQ(vec[i].first, static_cast<int>(i + 1));
    }
}

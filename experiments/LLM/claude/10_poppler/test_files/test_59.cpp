#include <gtest/gtest.h>
#include "Object.h"

// Test that a Ref with smaller num is less than a Ref with larger num
TEST(RefLessThanOperator_59, SmallerNumIsLess_59) {
    Ref lhs = {1, 0};
    Ref rhs = {2, 0};
    EXPECT_TRUE(lhs < rhs);
}

// Test that a Ref with larger num is not less than a Ref with smaller num
TEST(RefLessThanOperator_59, LargerNumIsNotLess_59) {
    Ref lhs = {2, 0};
    Ref rhs = {1, 0};
    EXPECT_FALSE(lhs < rhs);
}

// Test that when nums are equal, smaller gen makes it less
TEST(RefLessThanOperator_59, EqualNumSmallerGenIsLess_59) {
    Ref lhs = {1, 0};
    Ref rhs = {1, 1};
    EXPECT_TRUE(lhs < rhs);
}

// Test that when nums are equal, larger gen is not less
TEST(RefLessThanOperator_59, EqualNumLargerGenIsNotLess_59) {
    Ref lhs = {1, 2};
    Ref rhs = {1, 1};
    EXPECT_FALSE(lhs < rhs);
}

// Test that identical Refs are not less than each other
TEST(RefLessThanOperator_59, EqualRefsNotLess_59) {
    Ref lhs = {1, 1};
    Ref rhs = {1, 1};
    EXPECT_FALSE(lhs < rhs);
}

// Test that num comparison takes priority over gen
TEST(RefLessThanOperator_59, NumTakesPriorityOverGen_59) {
    Ref lhs = {1, 100};
    Ref rhs = {2, 0};
    EXPECT_TRUE(lhs < rhs);
}

// Test reverse: larger num with smaller gen is not less
TEST(RefLessThanOperator_59, LargerNumSmallerGenNotLess_59) {
    Ref lhs = {2, 0};
    Ref rhs = {1, 100};
    EXPECT_FALSE(lhs < rhs);
}

// Test with zero values
TEST(RefLessThanOperator_59, BothZero_59) {
    Ref lhs = {0, 0};
    Ref rhs = {0, 0};
    EXPECT_FALSE(lhs < rhs);
}

// Test with negative num values
TEST(RefLessThanOperator_59, NegativeNumValues_59) {
    Ref lhs = {-1, 0};
    Ref rhs = {0, 0};
    EXPECT_TRUE(lhs < rhs);
}

// Test with negative gen values when nums are equal
TEST(RefLessThanOperator_59, NegativeGenValues_59) {
    Ref lhs = {1, -1};
    Ref rhs = {1, 0};
    EXPECT_TRUE(lhs < rhs);
}

// Test that gen is only compared when num is equal
TEST(RefLessThanOperator_59, GenOnlyMattersWhenNumEqual_59) {
    Ref lhs = {5, 10};
    Ref rhs = {5, 20};
    EXPECT_TRUE(lhs < rhs);
    
    Ref lhs2 = {5, 20};
    Ref rhs2 = {5, 10};
    EXPECT_FALSE(lhs2 < rhs2);
}

// Test with large values
TEST(RefLessThanOperator_59, LargeValues_59) {
    Ref lhs = {INT_MAX - 1, 0};
    Ref rhs = {INT_MAX, 0};
    EXPECT_TRUE(lhs < rhs);
}

// Test with large gen values when num is equal
TEST(RefLessThanOperator_59, LargeGenValues_59) {
    Ref lhs = {1, INT_MAX - 1};
    Ref rhs = {1, INT_MAX};
    EXPECT_TRUE(lhs < rhs);
}

// Test strict weak ordering: irreflexivity
TEST(RefLessThanOperator_59, Irreflexivity_59) {
    Ref r = {42, 7};
    EXPECT_FALSE(r < r);
}

// Test strict weak ordering: asymmetry
TEST(RefLessThanOperator_59, Asymmetry_59) {
    Ref a = {1, 2};
    Ref b = {1, 3};
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

// Test strict weak ordering: transitivity
TEST(RefLessThanOperator_59, Transitivity_59) {
    Ref a = {1, 0};
    Ref b = {2, 0};
    Ref c = {3, 0};
    EXPECT_TRUE(a < b);
    EXPECT_TRUE(b < c);
    EXPECT_TRUE(a < c);
}

#include <gtest/gtest.h>
#include "Object.h"

// Test: Two Refs with same num and gen are not "not equal" (i.e., they are equal)
TEST(RefNotEqualOperatorTest_58, SameNumAndGen_ReturnsFalse_58) {
    Ref a;
    a.num = 5;
    a.gen = 10;
    Ref b;
    b.num = 5;
    b.gen = 10;
    EXPECT_FALSE(a != b);
}

// Test: Two Refs with different num but same gen are not equal
TEST(RefNotEqualOperatorTest_58, DifferentNumSameGen_ReturnsTrue_58) {
    Ref a;
    a.num = 5;
    a.gen = 10;
    Ref b;
    b.num = 6;
    b.gen = 10;
    EXPECT_TRUE(a != b);
}

// Test: Two Refs with same num but different gen are not equal
TEST(RefNotEqualOperatorTest_58, SameNumDifferentGen_ReturnsTrue_58) {
    Ref a;
    a.num = 5;
    a.gen = 10;
    Ref b;
    b.num = 5;
    b.gen = 11;
    EXPECT_TRUE(a != b);
}

// Test: Two Refs with different num and different gen are not equal
TEST(RefNotEqualOperatorTest_58, DifferentNumDifferentGen_ReturnsTrue_58) {
    Ref a;
    a.num = 1;
    a.gen = 2;
    Ref b;
    b.num = 3;
    b.gen = 4;
    EXPECT_TRUE(a != b);
}

// Test: Both num and gen are zero
TEST(RefNotEqualOperatorTest_58, BothZero_ReturnsFalse_58) {
    Ref a;
    a.num = 0;
    a.gen = 0;
    Ref b;
    b.num = 0;
    b.gen = 0;
    EXPECT_FALSE(a != b);
}

// Test: Negative values for num and gen that are equal
TEST(RefNotEqualOperatorTest_58, NegativeValuesEqual_ReturnsFalse_58) {
    Ref a;
    a.num = -1;
    a.gen = -2;
    Ref b;
    b.num = -1;
    b.gen = -2;
    EXPECT_FALSE(a != b);
}

// Test: Negative values for num and gen that are different
TEST(RefNotEqualOperatorTest_58, NegativeValuesDifferent_ReturnsTrue_58) {
    Ref a;
    a.num = -1;
    a.gen = -2;
    Ref b;
    b.num = -3;
    b.gen = -4;
    EXPECT_TRUE(a != b);
}

// Test: Comparing a Ref with itself (reflexive case)
TEST(RefNotEqualOperatorTest_58, SameObject_ReturnsFalse_58) {
    Ref a;
    a.num = 42;
    a.gen = 99;
    EXPECT_FALSE(a != a);
}

// Test: Symmetry - a != b should equal b != a
TEST(RefNotEqualOperatorTest_58, Symmetry_58) {
    Ref a;
    a.num = 1;
    a.gen = 2;
    Ref b;
    b.num = 3;
    b.gen = 4;
    EXPECT_EQ((a != b), (b != a));
}

// Test: Symmetry when equal
TEST(RefNotEqualOperatorTest_58, SymmetryWhenEqual_58) {
    Ref a;
    a.num = 7;
    a.gen = 8;
    Ref b;
    b.num = 7;
    b.gen = 8;
    EXPECT_EQ((a != b), (b != a));
    EXPECT_FALSE(a != b);
}

// Test: INVALID Ref compared with itself should be equal (not not-equal)
TEST(RefNotEqualOperatorTest_58, InvalidRefComparedWithItself_ReturnsFalse_58) {
    Ref inv = Ref::INVALID();
    EXPECT_FALSE(inv != inv);
}

// Test: INVALID Ref compared with a valid Ref
TEST(RefNotEqualOperatorTest_58, InvalidRefVsValidRef_ReturnsTrue_58) {
    Ref inv = Ref::INVALID();
    Ref valid;
    valid.num = 1;
    valid.gen = 0;
    // INVALID ref typically has special sentinel values, so should differ from a normal ref
    EXPECT_TRUE(inv != valid);
}

// Test: Two INVALID Refs are equal
TEST(RefNotEqualOperatorTest_58, TwoInvalidRefs_ReturnsFalse_58) {
    Ref inv1 = Ref::INVALID();
    Ref inv2 = Ref::INVALID();
    EXPECT_FALSE(inv1 != inv2);
}

// Test: Large values for num and gen
TEST(RefNotEqualOperatorTest_58, LargeValues_Equal_ReturnsFalse_58) {
    Ref a;
    a.num = 2147483647;
    a.gen = 2147483647;
    Ref b;
    b.num = 2147483647;
    b.gen = 2147483647;
    EXPECT_FALSE(a != b);
}

// Test: Large values differing by one in num
TEST(RefNotEqualOperatorTest_58, LargeValuesDifferByOneNum_ReturnsTrue_58) {
    Ref a;
    a.num = 2147483647;
    a.gen = 0;
    Ref b;
    b.num = 2147483646;
    b.gen = 0;
    EXPECT_TRUE(a != b);
}

// Test: Large values differing by one in gen
TEST(RefNotEqualOperatorTest_58, LargeValuesDifferByOneGen_ReturnsTrue_58) {
    Ref a;
    a.num = 0;
    a.gen = 2147483647;
    Ref b;
    b.num = 0;
    b.gen = 2147483646;
    EXPECT_TRUE(a != b);
}

// Test: One field zero, other field differs
TEST(RefNotEqualOperatorTest_58, ZeroNumDifferentGen_ReturnsTrue_58) {
    Ref a;
    a.num = 0;
    a.gen = 1;
    Ref b;
    b.num = 0;
    b.gen = 2;
    EXPECT_TRUE(a != b);
}

TEST(RefNotEqualOperatorTest_58, DifferentNumZeroGen_ReturnsTrue_58) {
    Ref a;
    a.num = 1;
    a.gen = 0;
    Ref b;
    b.num = 2;
    b.gen = 0;
    EXPECT_TRUE(a != b);
}

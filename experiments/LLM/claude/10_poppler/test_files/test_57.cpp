#include <gtest/gtest.h>
#include "Object.h"

// Test equality of two Refs with same num and gen
TEST(RefEqualityTest_57, EqualRefsReturnTrue_57) {
    Ref a = {1, 2};
    Ref b = {1, 2};
    EXPECT_TRUE(a == b);
}

// Test inequality when num differs
TEST(RefEqualityTest_57, DifferentNumReturnsFalse_57) {
    Ref a = {1, 2};
    Ref b = {3, 2};
    EXPECT_FALSE(a == b);
}

// Test inequality when gen differs
TEST(RefEqualityTest_57, DifferentGenReturnsFalse_57) {
    Ref a = {1, 2};
    Ref b = {1, 4};
    EXPECT_FALSE(a == b);
}

// Test inequality when both num and gen differ
TEST(RefEqualityTest_57, BothDifferentReturnsFalse_57) {
    Ref a = {1, 2};
    Ref b = {3, 4};
    EXPECT_FALSE(a == b);
}

// Test with zero values
TEST(RefEqualityTest_57, ZeroValuesEqual_57) {
    Ref a = {0, 0};
    Ref b = {0, 0};
    EXPECT_TRUE(a == b);
}

// Test with negative values
TEST(RefEqualityTest_57, NegativeValuesEqual_57) {
    Ref a = {-1, -2};
    Ref b = {-1, -2};
    EXPECT_TRUE(a == b);
}

// Test with negative values not equal
TEST(RefEqualityTest_57, NegativeValuesNotEqual_57) {
    Ref a = {-1, -2};
    Ref b = {-1, -3};
    EXPECT_FALSE(a == b);
}

// Test symmetry: a == b implies b == a
TEST(RefEqualityTest_57, SymmetryEqual_57) {
    Ref a = {5, 10};
    Ref b = {5, 10};
    EXPECT_EQ((a == b), (b == a));
}

// Test symmetry for non-equal refs
TEST(RefEqualityTest_57, SymmetryNotEqual_57) {
    Ref a = {5, 10};
    Ref b = {10, 5};
    EXPECT_EQ((a == b), (b == a));
}

// Test reflexivity: a == a
TEST(RefEqualityTest_57, Reflexivity_57) {
    Ref a = {42, 99};
    EXPECT_TRUE(a == a);
}

// Test with INVALID ref compared to itself
TEST(RefEqualityTest_57, InvalidRefEqualToItself_57) {
    Ref inv = Ref::INVALID();
    EXPECT_TRUE(inv == inv);
}

// Test with INVALID ref compared to another INVALID ref
TEST(RefEqualityTest_57, TwoInvalidRefsAreEqual_57) {
    Ref inv1 = Ref::INVALID();
    Ref inv2 = Ref::INVALID();
    EXPECT_TRUE(inv1 == inv2);
}

// Test INVALID ref not equal to a valid ref
TEST(RefEqualityTest_57, InvalidRefNotEqualToValidRef_57) {
    Ref inv = Ref::INVALID();
    Ref valid = {1, 0};
    // INVALID typically has num=-1, gen=-1 or similar sentinel values
    // This should be false unless valid happens to match INVALID's values
    // We test that a normal ref differs from INVALID
    if (inv.num != valid.num || inv.gen != valid.gen) {
        EXPECT_FALSE(inv == valid);
    }
}

// Test with large values
TEST(RefEqualityTest_57, LargeValuesEqual_57) {
    Ref a = {INT_MAX, INT_MAX};
    Ref b = {INT_MAX, INT_MAX};
    EXPECT_TRUE(a == b);
}

// Test with large values not equal
TEST(RefEqualityTest_57, LargeValuesNotEqual_57) {
    Ref a = {INT_MAX, INT_MAX};
    Ref b = {INT_MAX, INT_MAX - 1};
    EXPECT_FALSE(a == b);
}

// Test with INT_MIN values
TEST(RefEqualityTest_57, MinValuesEqual_57) {
    Ref a = {INT_MIN, INT_MIN};
    Ref b = {INT_MIN, INT_MIN};
    EXPECT_TRUE(a == b);
}

// Test mixed positive and negative
TEST(RefEqualityTest_57, MixedSignNotEqual_57) {
    Ref a = {1, -1};
    Ref b = {-1, 1};
    EXPECT_FALSE(a == b);
}

// Test that num match but gen swapped doesn't match
TEST(RefEqualityTest_57, SwappedNumGenNotEqual_57) {
    Ref a = {3, 7};
    Ref b = {7, 3};
    EXPECT_FALSE(a == b);
}

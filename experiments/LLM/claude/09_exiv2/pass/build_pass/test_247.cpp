#include <gtest/gtest.h>
#include "tiffcomposite_int.hpp"

using namespace Exiv2::Internal;

// Test that ArrayDef equality operator returns true when idx matches
TEST(ArrayDefTest_247, EqualityOperatorReturnsTrue_247) {
    ArrayDef def;
    def.idx_ = 5;
    def.count_ = 10;
    EXPECT_TRUE(def == 5);
}

// Test that ArrayDef equality operator returns false when idx does not match
TEST(ArrayDefTest_247, EqualityOperatorReturnsFalse_247) {
    ArrayDef def;
    def.idx_ = 5;
    def.count_ = 10;
    EXPECT_FALSE(def == 6);
}

// Test equality with zero index
TEST(ArrayDefTest_247, EqualityOperatorWithZeroIndex_247) {
    ArrayDef def;
    def.idx_ = 0;
    def.count_ = 1;
    EXPECT_TRUE(def == 0);
}

// Test equality with zero index but comparing to non-zero
TEST(ArrayDefTest_247, EqualityOperatorZeroIdxNonZeroComparison_247) {
    ArrayDef def;
    def.idx_ = 0;
    def.count_ = 1;
    EXPECT_FALSE(def == 1);
}

// Test equality with large index value
TEST(ArrayDefTest_247, EqualityOperatorLargeIndex_247) {
    ArrayDef def;
    def.idx_ = SIZE_MAX;
    def.count_ = 0;
    EXPECT_TRUE(def == SIZE_MAX);
}

// Test equality with large index value but different
TEST(ArrayDefTest_247, EqualityOperatorLargeIndexMismatch_247) {
    ArrayDef def;
    def.idx_ = SIZE_MAX;
    def.count_ = 0;
    EXPECT_FALSE(def == (SIZE_MAX - 1));
}

// Test that count_ does not affect equality comparison
TEST(ArrayDefTest_247, CountDoesNotAffectEquality_247) {
    ArrayDef def1;
    def1.idx_ = 3;
    def1.count_ = 100;

    ArrayDef def2;
    def2.idx_ = 3;
    def2.count_ = 200;

    EXPECT_TRUE(def1 == 3);
    EXPECT_TRUE(def2 == 3);
}

// Test equality operator with adjacent values
TEST(ArrayDefTest_247, EqualityOperatorAdjacentValues_247) {
    ArrayDef def;
    def.idx_ = 10;
    def.count_ = 5;
    EXPECT_FALSE(def == 9);
    EXPECT_TRUE(def == 10);
    EXPECT_FALSE(def == 11);
}

// Test multiple ArrayDef instances with different idx values
TEST(ArrayDefTest_247, MultipleInstancesDifferentIdx_247) {
    ArrayDef def1;
    def1.idx_ = 1;
    def1.count_ = 1;

    ArrayDef def2;
    def2.idx_ = 2;
    def2.count_ = 1;

    EXPECT_TRUE(def1 == 1);
    EXPECT_FALSE(def1 == 2);
    EXPECT_TRUE(def2 == 2);
    EXPECT_FALSE(def2 == 1);
}

// Test equality with value 1
TEST(ArrayDefTest_247, EqualityOperatorWithOne_247) {
    ArrayDef def;
    def.idx_ = 1;
    def.count_ = 0;
    EXPECT_TRUE(def == 1);
    EXPECT_FALSE(def == 0);
}

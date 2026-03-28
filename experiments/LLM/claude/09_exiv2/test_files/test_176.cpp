#include <gtest/gtest.h>
#include <cstdint>

// Include the header under test
#include "tags_int.hpp"

namespace {

using Exiv2::Internal::TagDetails;

// Test normal equality when key matches val_
TEST(TagDetailsTest_176, EqualityMatchesWhenKeyEqualsVal_176) {
    TagDetails td{42, "some_label"};
    EXPECT_TRUE(td == 42);
}

// Test inequality when key does not match val_
TEST(TagDetailsTest_176, EqualityReturnsFalseWhenKeyDiffers_176) {
    TagDetails td{42, "some_label"};
    EXPECT_FALSE(td == 43);
}

// Test with val_ = 0
TEST(TagDetailsTest_176, EqualityWithZeroVal_176) {
    TagDetails td{0, "zero_label"};
    EXPECT_TRUE(td == 0);
    EXPECT_FALSE(td == 1);
}

// Test with negative val_
TEST(TagDetailsTest_176, EqualityWithNegativeVal_176) {
    TagDetails td{-100, "negative_label"};
    EXPECT_TRUE(td == -100);
    EXPECT_FALSE(td == 100);
}

// Test with INT64_MAX
TEST(TagDetailsTest_176, EqualityWithInt64Max_176) {
    TagDetails td{INT64_MAX, "max_label"};
    EXPECT_TRUE(td == INT64_MAX);
    EXPECT_FALSE(td == INT64_MAX - 1);
}

// Test with INT64_MIN
TEST(TagDetailsTest_176, EqualityWithInt64Min_176) {
    TagDetails td{INT64_MIN, "min_label"};
    EXPECT_TRUE(td == INT64_MIN);
    EXPECT_FALSE(td == INT64_MIN + 1);
}

// Test with val_ = 1 and key = -1
TEST(TagDetailsTest_176, EqualityPositiveValNegativeKey_176) {
    TagDetails td{1, "one_label"};
    EXPECT_FALSE(td == -1);
}

// Test with val_ = -1 and key = 1
TEST(TagDetailsTest_176, EqualityNegativeValPositiveKey_176) {
    TagDetails td{-1, "neg_one_label"};
    EXPECT_FALSE(td == 1);
}

// Test that label_ field is accessible and can be set
TEST(TagDetailsTest_176, LabelFieldAccessible_176) {
    TagDetails td{10, "test_label"};
    EXPECT_STREQ(td.label_, "test_label");
}

// Test with nullptr label
TEST(TagDetailsTest_176, NullLabelDoesNotAffectEquality_176) {
    TagDetails td{5, nullptr};
    EXPECT_TRUE(td == 5);
    EXPECT_FALSE(td == 6);
    EXPECT_EQ(td.label_, nullptr);
}

// Test multiple TagDetails with different values
TEST(TagDetailsTest_176, MultipleTagDetailsComparisons_176) {
    TagDetails td1{1, "first"};
    TagDetails td2{2, "second"};
    TagDetails td3{3, "third"};

    EXPECT_TRUE(td1 == 1);
    EXPECT_FALSE(td1 == 2);
    EXPECT_FALSE(td1 == 3);

    EXPECT_FALSE(td2 == 1);
    EXPECT_TRUE(td2 == 2);
    EXPECT_FALSE(td2 == 3);

    EXPECT_FALSE(td3 == 1);
    EXPECT_FALSE(td3 == 2);
    EXPECT_TRUE(td3 == 3);
}

// Test with large positive value
TEST(TagDetailsTest_176, EqualityWithLargePositiveValue_176) {
    int64_t largeVal = 999999999999LL;
    TagDetails td{largeVal, "large"};
    EXPECT_TRUE(td == largeVal);
    EXPECT_FALSE(td == largeVal + 1);
}

// Test with large negative value
TEST(TagDetailsTest_176, EqualityWithLargeNegativeValue_176) {
    int64_t largeNegVal = -999999999999LL;
    TagDetails td{largeNegVal, "large_neg"};
    EXPECT_TRUE(td == largeNegVal);
    EXPECT_FALSE(td == largeNegVal - 1);
}

// Test that val_ member is correctly stored
TEST(TagDetailsTest_176, ValMemberCorrectlyStored_176) {
    TagDetails td{12345, "stored"};
    EXPECT_EQ(td.val_, 12345);
}

} // namespace

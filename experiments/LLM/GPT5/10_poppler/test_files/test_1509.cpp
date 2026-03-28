#include <gtest/gtest.h>
#include <optional>
#include "CIDFontsWidthsBuilder.h"

class SegmentBuilderTest_1509 : public ::testing::Test {
protected:
    CIDFontsWidthsBuilder::SegmentBuilder builder;
};

// Test normal operation where the values are accepted properly
TEST_F(SegmentBuilderTest_1509, AcceptFirstValue_1509) {
    EXPECT_TRUE(builder.accept(0, 100));
    EXPECT_TRUE(builder.accept(1, 100));
    EXPECT_TRUE(builder.accept(2, 100));
    EXPECT_TRUE(builder.accept(3, 100));
}

// Test boundary condition when the index is not consecutive
TEST_F(SegmentBuilderTest_1509, AcceptNonConsecutiveIndex_1509) {
    // First value accepted
    EXPECT_TRUE(builder.accept(0, 100));

    // Second value with a different index will fail
    EXPECT_FALSE(builder.accept(2, 100));
}

// Test boundary condition when the `m_values` list has more than 4 elements
TEST_F(SegmentBuilderTest_1509, AcceptMoreThanFourValues_1509) {
    builder.accept(0, 100);
    builder.accept(1, 100);
    builder.accept(2, 100);
    builder.accept(3, 100);
    
    // This fifth value should be rejected as we only accept up to 4 values
    EXPECT_FALSE(builder.accept(4, 100));
}

// Test exceptional case when values are not equal but are different
TEST_F(SegmentBuilderTest_1509, AcceptDifferentValues_1509) {
    EXPECT_TRUE(builder.accept(0, 100));
    EXPECT_TRUE(builder.accept(1, 200));
    EXPECT_TRUE(builder.accept(2, 300));
    EXPECT_TRUE(builder.accept(3, 400));
}

// Test when a repeated value can be added when there are no different values
TEST_F(SegmentBuilderTest_1509, AcceptRepeatedValueNoDifference_1509) {
    EXPECT_TRUE(builder.accept(0, 100));
    EXPECT_TRUE(builder.accept(1, 100));
    EXPECT_TRUE(builder.accept(2, 100));
    EXPECT_TRUE(builder.accept(3, 100));  // This should pass, as it’s the same value as the front
}

// Test when there are too many unique elements from the end
TEST_F(SegmentBuilderTest_1509, RejectTooManyUniqueElements_1509) {
    EXPECT_TRUE(builder.accept(0, 100));
    EXPECT_TRUE(builder.accept(1, 100));
    EXPECT_TRUE(builder.accept(2, 200));
    EXPECT_TRUE(builder.accept(3, 300));

    // This value should be rejected because of too many unique elements from the end
    EXPECT_FALSE(builder.accept(4, 400));
}

// Test when the first index is set correctly
TEST_F(SegmentBuilderTest_1509, FirstIndexSet_1509) {
    EXPECT_TRUE(builder.accept(0, 100));
    EXPECT_EQ(builder.m_firstIndex, 0);
}

// Test when the last index is set correctly
TEST_F(SegmentBuilderTest_1509, LastIndexSet_1509) {
    EXPECT_TRUE(builder.accept(0, 100));
    EXPECT_TRUE(builder.accept(1, 100));
    EXPECT_TRUE(builder.accept(2, 100));
    EXPECT_TRUE(builder.accept(3, 100));
    EXPECT_EQ(builder.m_lastIndex, 3);
}

// Test when differentValues is set correctly
TEST_F(SegmentBuilderTest_1509, DifferentValuesSet_1509) {
    EXPECT_TRUE(builder.accept(0, 100));
    EXPECT_TRUE(builder.accept(1, 200));
    EXPECT_TRUE(builder.accept(2, 300));
    EXPECT_TRUE(builder.accept(3, 400));
    EXPECT_TRUE(builder.differentValues);
}
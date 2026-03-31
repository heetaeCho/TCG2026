#include <gtest/gtest.h>
#include "CIDFontsWidthsBuilder.h"
#include <variant>
#include <vector>

using namespace std;

class SegmentBuilderTest_1510 : public ::testing::Test {
protected:
    // We need access to the inner class through CIDFontsWidthsBuilder
};

// Test building with fewer than 4 identical values produces a ListSegment
TEST(SegmentBuilderBuild_1510, FewIdenticalValuesProducesListSegment_1510) {
    CIDFontsWidthsBuilder::SegmentBuilder builder;
    builder.accept(0, 100);
    builder.accept(1, 100);
    builder.accept(2, 100);
    
    auto segment = builder.build();
    ASSERT_TRUE(std::holds_alternative<CIDFontsWidthsBuilder::ListSegment>(segment));
    auto list = std::get<CIDFontsWidthsBuilder::ListSegment>(segment);
    EXPECT_EQ(list.first, 0);
    EXPECT_EQ(list.widths.size(), 3u);
    EXPECT_EQ(list.widths[0], 100);
    EXPECT_EQ(list.widths[1], 100);
    EXPECT_EQ(list.widths[2], 100);
}

// Test building with 4+ identical values produces a RangeSegment
TEST(SegmentBuilderBuild_1510, FourOrMoreIdenticalValuesProducesRangeSegment_1510) {
    CIDFontsWidthsBuilder::SegmentBuilder builder;
    builder.accept(0, 200);
    builder.accept(1, 200);
    builder.accept(2, 200);
    builder.accept(3, 200);
    
    auto segment = builder.build();
    ASSERT_TRUE(std::holds_alternative<CIDFontsWidthsBuilder::RangeSegment>(segment));
    auto range = std::get<CIDFontsWidthsBuilder::RangeSegment>(segment);
    EXPECT_EQ(range.first, 0);
    EXPECT_EQ(range.last, 3);
    EXPECT_EQ(range.width, 200);
}

// Test building with different values produces a ListSegment
TEST(SegmentBuilderBuild_1510, DifferentValuesProducesListSegment_1510) {
    CIDFontsWidthsBuilder::SegmentBuilder builder;
    builder.accept(5, 100);
    builder.accept(6, 200);
    builder.accept(7, 300);
    builder.accept(8, 400);
    
    auto segment = builder.build();
    ASSERT_TRUE(std::holds_alternative<CIDFontsWidthsBuilder::ListSegment>(segment));
    auto list = std::get<CIDFontsWidthsBuilder::ListSegment>(segment);
    EXPECT_EQ(list.first, 5);
    EXPECT_EQ(list.widths.size(), 4u);
    EXPECT_EQ(list.widths[0], 100);
    EXPECT_EQ(list.widths[1], 200);
    EXPECT_EQ(list.widths[2], 300);
    EXPECT_EQ(list.widths[3], 400);
}

// Test mixed values followed by trailing identical values (>=3) splits into ListSegment
TEST(SegmentBuilderBuild_1510, MixedThenTrailingIdenticalSplits_1510) {
    CIDFontsWidthsBuilder::SegmentBuilder builder;
    builder.accept(0, 100);
    builder.accept(1, 200);
    builder.accept(2, 300);
    builder.accept(3, 300);
    builder.accept(4, 300);
    
    auto segment = builder.build();
    ASSERT_TRUE(std::holds_alternative<CIDFontsWidthsBuilder::ListSegment>(segment));
    auto list = std::get<CIDFontsWidthsBuilder::ListSegment>(segment);
    EXPECT_EQ(list.first, 0);
    // The trailing 300s (3 of them) should be saved, leaving [100, 200]
    EXPECT_EQ(list.widths.size(), 2u);
    EXPECT_EQ(list.widths[0], 100);
    EXPECT_EQ(list.widths[1], 200);
}

// Test single value produces ListSegment
TEST(SegmentBuilderBuild_1510, SingleValueProducesListSegment_1510) {
    CIDFontsWidthsBuilder::SegmentBuilder builder;
    builder.accept(10, 500);
    
    auto segment = builder.build();
    ASSERT_TRUE(std::holds_alternative<CIDFontsWidthsBuilder::ListSegment>(segment));
    auto list = std::get<CIDFontsWidthsBuilder::ListSegment>(segment);
    EXPECT_EQ(list.first, 10);
    EXPECT_EQ(list.widths.size(), 1u);
    EXPECT_EQ(list.widths[0], 500);
}

// Test accept returns value indicating whether segment is ready to build
TEST(SegmentBuilderAccept_1510, AcceptSequentialIndicesReturnsTrue_1510) {
    CIDFontsWidthsBuilder::SegmentBuilder builder;
    EXPECT_TRUE(builder.accept(0, 100));
    EXPECT_TRUE(builder.accept(1, 200));
    EXPECT_TRUE(builder.accept(2, 300));
}

// Test accept with non-sequential index returns false
TEST(SegmentBuilderAccept_1510, AcceptNonSequentialReturnsFalse_1510) {
    CIDFontsWidthsBuilder::SegmentBuilder builder;
    builder.accept(0, 100);
    builder.accept(1, 200);
    // Skip index 2, go to 5
    bool result = builder.accept(5, 300);
    EXPECT_FALSE(result);
}

// Test 5 identical values produces RangeSegment
TEST(SegmentBuilderBuild_1510, FiveIdenticalValuesProducesRangeSegment_1510) {
    CIDFontsWidthsBuilder::SegmentBuilder builder;
    builder.accept(0, 50);
    builder.accept(1, 50);
    builder.accept(2, 50);
    builder.accept(3, 50);
    builder.accept(4, 50);
    
    auto segment = builder.build();
    ASSERT_TRUE(std::holds_alternative<CIDFontsWidthsBuilder::RangeSegment>(segment));
    auto range = std::get<CIDFontsWidthsBuilder::RangeSegment>(segment);
    EXPECT_EQ(range.first, 0);
    EXPECT_EQ(range.last, 4);
    EXPECT_EQ(range.width, 50);
}

// Test building after split - second build should return remaining saved values
TEST(SegmentBuilderBuild_1510, ConsecutiveBuildsAfterSplit_1510) {
    CIDFontsWidthsBuilder::SegmentBuilder builder;
    builder.accept(0, 100);
    builder.accept(1, 200);
    builder.accept(2, 300);
    builder.accept(3, 300);
    builder.accept(4, 300);
    builder.accept(5, 300);
    
    // First build should produce list [100, 200] 
    auto segment1 = builder.build();
    ASSERT_TRUE(std::holds_alternative<CIDFontsWidthsBuilder::ListSegment>(segment1));
    auto list1 = std::get<CIDFontsWidthsBuilder::ListSegment>(segment1);
    EXPECT_EQ(list1.first, 0);
    EXPECT_EQ(list1.widths[0], 100);
    EXPECT_EQ(list1.widths[1], 200);

    // Second build should produce range of 300s
    auto segment2 = builder.build();
    ASSERT_TRUE(std::holds_alternative<CIDFontsWidthsBuilder::RangeSegment>(segment2));
    auto range2 = std::get<CIDFontsWidthsBuilder::RangeSegment>(segment2);
    EXPECT_EQ(range2.width, 300);
}

// Test with exactly 4 different values
TEST(SegmentBuilderBuild_1510, ExactlyFourDifferentValues_1510) {
    CIDFontsWidthsBuilder::SegmentBuilder builder;
    builder.accept(10, 1);
    builder.accept(11, 2);
    builder.accept(12, 3);
    builder.accept(13, 4);
    
    auto segment = builder.build();
    ASSERT_TRUE(std::holds_alternative<CIDFontsWidthsBuilder::ListSegment>(segment));
    auto list = std::get<CIDFontsWidthsBuilder::ListSegment>(segment);
    EXPECT_EQ(list.first, 10);
    EXPECT_EQ(list.widths.size(), 4u);
}

// Test two values
TEST(SegmentBuilderBuild_1510, TwoValuesProducesListSegment_1510) {
    CIDFontsWidthsBuilder::SegmentBuilder builder;
    builder.accept(0, 10);
    builder.accept(1, 20);
    
    auto segment = builder.build();
    ASSERT_TRUE(std::holds_alternative<CIDFontsWidthsBuilder::ListSegment>(segment));
    auto list = std::get<CIDFontsWidthsBuilder::ListSegment>(segment);
    EXPECT_EQ(list.first, 0);
    EXPECT_EQ(list.widths.size(), 2u);
    EXPECT_EQ(list.widths[0], 10);
    EXPECT_EQ(list.widths[1], 20);
}

// Test starting at non-zero index
TEST(SegmentBuilderBuild_1510, NonZeroStartIndex_1510) {
    CIDFontsWidthsBuilder::SegmentBuilder builder;
    builder.accept(100, 42);
    builder.accept(101, 42);
    builder.accept(102, 42);
    builder.accept(103, 42);
    
    auto segment = builder.build();
    ASSERT_TRUE(std::holds_alternative<CIDFontsWidthsBuilder::RangeSegment>(segment));
    auto range = std::get<CIDFontsWidthsBuilder::RangeSegment>(segment);
    EXPECT_EQ(range.first, 100);
    EXPECT_EQ(range.last, 103);
    EXPECT_EQ(range.width, 42);
}

// Test large number of mixed values with trailing identical
TEST(SegmentBuilderBuild_1510, LargeMixedWithTrailingIdentical_1510) {
    CIDFontsWidthsBuilder::SegmentBuilder builder;
    builder.accept(0, 1);
    builder.accept(1, 2);
    builder.accept(2, 3);
    builder.accept(3, 4);
    builder.accept(4, 5);
    builder.accept(5, 5);
    builder.accept(6, 5);
    builder.accept(7, 5);
    
    auto segment = builder.build();
    ASSERT_TRUE(std::holds_alternative<CIDFontsWidthsBuilder::ListSegment>(segment));
    auto list = std::get<CIDFontsWidthsBuilder::ListSegment>(segment);
    // Trailing 5s (4 of them) should be saved
    EXPECT_EQ(list.first, 0);
    EXPECT_EQ(list.widths.size(), 4u);
    EXPECT_EQ(list.widths[0], 1);
    EXPECT_EQ(list.widths[1], 2);
    EXPECT_EQ(list.widths[2], 3);
    EXPECT_EQ(list.widths[3], 4);
}

// Test zero width values
TEST(SegmentBuilderBuild_1510, ZeroWidthValues_1510) {
    CIDFontsWidthsBuilder::SegmentBuilder builder;
    builder.accept(0, 0);
    builder.accept(1, 0);
    builder.accept(2, 0);
    builder.accept(3, 0);
    
    auto segment = builder.build();
    ASSERT_TRUE(std::holds_alternative<CIDFontsWidthsBuilder::RangeSegment>(segment));
    auto range = std::get<CIDFontsWidthsBuilder::RangeSegment>(segment);
    EXPECT_EQ(range.width, 0);
}

// Test negative width values
TEST(SegmentBuilderBuild_1510, NegativeWidthValues_1510) {
    CIDFontsWidthsBuilder::SegmentBuilder builder;
    builder.accept(0, -100);
    builder.accept(1, -100);
    builder.accept(2, -100);
    builder.accept(3, -100);
    
    auto segment = builder.build();
    ASSERT_TRUE(std::holds_alternative<CIDFontsWidthsBuilder::RangeSegment>(segment));
    auto range = std::get<CIDFontsWidthsBuilder::RangeSegment>(segment);
    EXPECT_EQ(range.width, -100);
}

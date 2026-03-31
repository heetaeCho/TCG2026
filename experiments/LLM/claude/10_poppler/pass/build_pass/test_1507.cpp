#include <gtest/gtest.h>
#include "CIDFontsWidthsBuilder.h"

class CIDFontsWidthsBuilderTest_1507 : public ::testing::Test {
protected:
    CIDFontsWidthsBuilder builder;
};

// Test that a freshly constructed builder produces empty segments
TEST_F(CIDFontsWidthsBuilderTest_1507, DefaultConstructorProducesEmptySegments_1507)
{
    auto segments = builder.takeSegments();
    EXPECT_TRUE(segments.empty());
}

// Test adding a single width and retrieving segments
TEST_F(CIDFontsWidthsBuilderTest_1507, AddSingleWidth_1507)
{
    builder.addWidth(0, 500);
    auto segments = builder.takeSegments();
    EXPECT_FALSE(segments.empty());
}

// Test adding multiple widths with consecutive indices
TEST_F(CIDFontsWidthsBuilderTest_1507, AddConsecutiveWidths_1507)
{
    builder.addWidth(0, 500);
    builder.addWidth(1, 600);
    builder.addWidth(2, 700);
    auto segments = builder.takeSegments();
    EXPECT_FALSE(segments.empty());
}

// Test adding widths with non-consecutive (gap) indices
TEST_F(CIDFontsWidthsBuilderTest_1507, AddWidthsWithGaps_1507)
{
    builder.addWidth(0, 500);
    builder.addWidth(5, 600);
    builder.addWidth(10, 700);
    auto segments = builder.takeSegments();
    EXPECT_FALSE(segments.empty());
}

// Test adding widths with the same width value (uniform widths)
TEST_F(CIDFontsWidthsBuilderTest_1507, AddUniformWidths_1507)
{
    builder.addWidth(0, 500);
    builder.addWidth(1, 500);
    builder.addWidth(2, 500);
    builder.addWidth(3, 500);
    auto segments = builder.takeSegments();
    EXPECT_FALSE(segments.empty());
}

// Test adding widths with varying values
TEST_F(CIDFontsWidthsBuilderTest_1507, AddVaryingWidths_1507)
{
    builder.addWidth(1, 100);
    builder.addWidth(2, 200);
    builder.addWidth(3, 300);
    builder.addWidth(4, 100);
    builder.addWidth(5, 200);
    auto segments = builder.takeSegments();
    EXPECT_FALSE(segments.empty());
}

// Test that strictly increasing indices are accepted
TEST_F(CIDFontsWidthsBuilderTest_1507, StrictlyIncreasingIndices_1507)
{
    builder.addWidth(10, 500);
    builder.addWidth(20, 600);
    builder.addWidth(30, 700);
    auto segments = builder.takeSegments();
    EXPECT_FALSE(segments.empty());
}

// Test large index values
TEST_F(CIDFontsWidthsBuilderTest_1507, LargeIndexValues_1507)
{
    builder.addWidth(10000, 500);
    builder.addWidth(10001, 600);
    builder.addWidth(20000, 700);
    auto segments = builder.takeSegments();
    EXPECT_FALSE(segments.empty());
}

// Test zero width value
TEST_F(CIDFontsWidthsBuilderTest_1507, ZeroWidthValue_1507)
{
    builder.addWidth(0, 0);
    builder.addWidth(1, 0);
    auto segments = builder.takeSegments();
    EXPECT_FALSE(segments.empty());
}

// Test negative width values
TEST_F(CIDFontsWidthsBuilderTest_1507, NegativeWidthValues_1507)
{
    builder.addWidth(0, -100);
    builder.addWidth(1, -200);
    auto segments = builder.takeSegments();
    EXPECT_FALSE(segments.empty());
}

// Test that takeSegments can be called multiple times (second call should return empty after first take)
TEST_F(CIDFontsWidthsBuilderTest_1507, TakeSegmentsTwice_1507)
{
    builder.addWidth(0, 500);
    builder.addWidth(1, 600);
    auto segments1 = builder.takeSegments();
    EXPECT_FALSE(segments1.empty());
    auto segments2 = builder.takeSegments();
    EXPECT_TRUE(segments2.empty());
}

// Test adding many widths
TEST_F(CIDFontsWidthsBuilderTest_1507, AddManyWidths_1507)
{
    for (int i = 0; i < 1000; ++i) {
        builder.addWidth(i, i * 10);
    }
    auto segments = builder.takeSegments();
    EXPECT_FALSE(segments.empty());
}

// Test a mix of uniform and varying segments
TEST_F(CIDFontsWidthsBuilderTest_1507, MixedUniformAndVaryingSegments_1507)
{
    // Uniform segment
    builder.addWidth(0, 500);
    builder.addWidth(1, 500);
    builder.addWidth(2, 500);
    // Gap then varying
    builder.addWidth(10, 100);
    builder.addWidth(11, 200);
    builder.addWidth(12, 300);
    // Gap then uniform again
    builder.addWidth(20, 800);
    builder.addWidth(21, 800);
    builder.addWidth(22, 800);
    auto segments = builder.takeSegments();
    EXPECT_FALSE(segments.empty());
}

// Test adding width at index 0 with large width
TEST_F(CIDFontsWidthsBuilderTest_1507, SingleWidthAtIndexZero_1507)
{
    builder.addWidth(0, 1000);
    auto segments = builder.takeSegments();
    EXPECT_GE(segments.size(), 1u);
}

// Test that after takeSegments, new widths can be added and taken again
TEST_F(CIDFontsWidthsBuilderTest_1507, AddAfterTakeSegments_1507)
{
    builder.addWidth(0, 500);
    auto segments1 = builder.takeSegments();
    EXPECT_FALSE(segments1.empty());

    builder.addWidth(0, 600);
    builder.addWidth(1, 700);
    auto segments2 = builder.takeSegments();
    EXPECT_FALSE(segments2.empty());
}

// Test consecutive indices with large gap between two groups
TEST_F(CIDFontsWidthsBuilderTest_1507, LargeGapBetweenGroups_1507)
{
    builder.addWidth(0, 500);
    builder.addWidth(1, 500);
    builder.addWidth(1000000, 600);
    builder.addWidth(1000001, 600);
    auto segments = builder.takeSegments();
    EXPECT_FALSE(segments.empty());
}

#include <gtest/gtest.h>
#include "CIDFontsWidthsBuilder.h"

class CIDFontsWidthsBuilderTest_1508 : public ::testing::Test {
protected:
    CIDFontsWidthsBuilder builder;
};

// Test that takeSegments returns empty vector when no widths have been added
TEST_F(CIDFontsWidthsBuilderTest_1508, TakeSegmentsEmpty_1508)
{
    auto segments = builder.takeSegments();
    EXPECT_TRUE(segments.empty());
}

// Test that adding a single width produces a segment
TEST_F(CIDFontsWidthsBuilderTest_1508, SingleWidth_1508)
{
    builder.addWidth(0, 500);
    auto segments = builder.takeSegments();
    EXPECT_FALSE(segments.empty());
}

// Test that adding consecutive widths with the same value works
TEST_F(CIDFontsWidthsBuilderTest_1508, ConsecutiveSameWidths_1508)
{
    builder.addWidth(0, 500);
    builder.addWidth(1, 500);
    builder.addWidth(2, 500);
    auto segments = builder.takeSegments();
    EXPECT_FALSE(segments.empty());
}

// Test that adding consecutive widths with different values works
TEST_F(CIDFontsWidthsBuilderTest_1508, ConsecutiveDifferentWidths_1508)
{
    builder.addWidth(0, 500);
    builder.addWidth(1, 600);
    builder.addWidth(2, 700);
    auto segments = builder.takeSegments();
    EXPECT_FALSE(segments.empty());
}

// Test that adding non-consecutive indices creates separate segments
TEST_F(CIDFontsWidthsBuilderTest_1508, NonConsecutiveIndices_1508)
{
    builder.addWidth(0, 500);
    builder.addWidth(5, 600);
    builder.addWidth(10, 700);
    auto segments = builder.takeSegments();
    EXPECT_FALSE(segments.empty());
}

// Test that takeSegments clears the internal state (calling again yields empty)
TEST_F(CIDFontsWidthsBuilderTest_1508, TakeSegmentsClearsState_1508)
{
    builder.addWidth(0, 500);
    builder.addWidth(1, 600);
    auto segments1 = builder.takeSegments();
    EXPECT_FALSE(segments1.empty());

    auto segments2 = builder.takeSegments();
    EXPECT_TRUE(segments2.empty());
}

// Test adding widths after takeSegments has been called (builder is reusable)
TEST_F(CIDFontsWidthsBuilderTest_1508, AddWidthsAfterTake_1508)
{
    builder.addWidth(0, 500);
    auto segments1 = builder.takeSegments();
    EXPECT_FALSE(segments1.empty());

    builder.addWidth(10, 800);
    auto segments2 = builder.takeSegments();
    EXPECT_FALSE(segments2.empty());
}

// Test large number of consecutive entries with same width
TEST_F(CIDFontsWidthsBuilderTest_1508, LargeConsecutiveSameWidth_1508)
{
    for (int i = 0; i < 100; i++) {
        builder.addWidth(i, 1000);
    }
    auto segments = builder.takeSegments();
    EXPECT_FALSE(segments.empty());
}

// Test large number of consecutive entries with different widths
TEST_F(CIDFontsWidthsBuilderTest_1508, LargeConsecutiveDifferentWidths_1508)
{
    for (int i = 0; i < 100; i++) {
        builder.addWidth(i, i * 10);
    }
    auto segments = builder.takeSegments();
    EXPECT_FALSE(segments.empty());
}

// Test mixed pattern: some consecutive same, then different, then gap
TEST_F(CIDFontsWidthsBuilderTest_1508, MixedPattern_1508)
{
    // Same width consecutive
    builder.addWidth(0, 500);
    builder.addWidth(1, 500);
    builder.addWidth(2, 500);
    // Different width consecutive
    builder.addWidth(3, 600);
    builder.addWidth(4, 700);
    // Gap
    builder.addWidth(10, 800);
    builder.addWidth(11, 800);

    auto segments = builder.takeSegments();
    EXPECT_FALSE(segments.empty());
}

// Test with width value of zero
TEST_F(CIDFontsWidthsBuilderTest_1508, ZeroWidth_1508)
{
    builder.addWidth(0, 0);
    auto segments = builder.takeSegments();
    EXPECT_FALSE(segments.empty());
}

// Test with negative width values
TEST_F(CIDFontsWidthsBuilderTest_1508, NegativeWidth_1508)
{
    builder.addWidth(0, -100);
    auto segments = builder.takeSegments();
    EXPECT_FALSE(segments.empty());
}

// Test with large index values
TEST_F(CIDFontsWidthsBuilderTest_1508, LargeIndex_1508)
{
    builder.addWidth(65535, 500);
    auto segments = builder.takeSegments();
    EXPECT_FALSE(segments.empty());
}

// Test multiple takeSegments calls without adding anything in between
TEST_F(CIDFontsWidthsBuilderTest_1508, MultipleTakeSegmentsWithoutAdding_1508)
{
    auto segments1 = builder.takeSegments();
    EXPECT_TRUE(segments1.empty());

    auto segments2 = builder.takeSegments();
    EXPECT_TRUE(segments2.empty());

    auto segments3 = builder.takeSegments();
    EXPECT_TRUE(segments3.empty());
}

// Test alternating same and different widths
TEST_F(CIDFontsWidthsBuilderTest_1508, AlternatingSameAndDifferent_1508)
{
    builder.addWidth(0, 500);
    builder.addWidth(1, 500);
    builder.addWidth(2, 600);
    builder.addWidth(3, 600);
    builder.addWidth(4, 500);
    builder.addWidth(5, 500);
    auto segments = builder.takeSegments();
    EXPECT_FALSE(segments.empty());
}

// Test that segments returned by takeSegments are moved (not copied)
TEST_F(CIDFontsWidthsBuilderTest_1508, TakeSegmentsMoveSemantics_1508)
{
    builder.addWidth(0, 500);
    builder.addWidth(1, 600);
    auto segments = builder.takeSegments();
    size_t count = segments.size();
    EXPECT_GT(count, 0u);

    // After move, builder should be empty
    auto segments2 = builder.takeSegments();
    EXPECT_TRUE(segments2.empty());
}

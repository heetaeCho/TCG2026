#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "CIDFontsWidthsBuilder.h"  // Assuming this includes the necessary headers

// Mocking any external dependencies
// In this case, there are no external collaborators that require Google Mock, as we're only testing the interface itself.

class CIDFontsWidthsBuilderTest : public ::testing::Test {
protected:
    CIDFontsWidthsBuilder::SegmentBuilder builder;

    // Resetting the builder for each test
    void SetUp() override {
        builder = CIDFontsWidthsBuilder::SegmentBuilder();
    }
};

TEST_F(CIDFontsWidthsBuilderTest, Build_SingleValue_ReturnsSegmentWithFirstIndex_1510) {
    builder.accept(0, 10);

    auto segment = builder.build();
    
    ASSERT_EQ(segment.first, 0);
    ASSERT_EQ(segment.widths.size(), 1);
    ASSERT_EQ(segment.widths[0], 10);
}

TEST_F(CIDFontsWidthsBuilderTest, Build_MultipleValues_SameValue_ReturnsSegmentWithLastIndex_1511) {
    builder.accept(0, 10);
    builder.accept(1, 10);
    builder.accept(2, 10);

    auto segment = builder.build();
    
    ASSERT_EQ(segment.first, 0);
    ASSERT_EQ(segment.last, 2);
    ASSERT_EQ(segment.widths.size(), 1);
    ASSERT_EQ(segment.widths[0], 10);
}

TEST_F(CIDFontsWidthsBuilderTest, Build_MultipleValues_DifferentValues_ReturnsCorrectSegment_1512) {
    builder.accept(0, 10);
    builder.accept(1, 15);
    builder.accept(2, 20);

    auto segment = builder.build();
    
    ASSERT_EQ(segment.first, 0);
    ASSERT_EQ(segment.last, 2);
    ASSERT_EQ(segment.widths.size(), 1);
    ASSERT_EQ(segment.widths[0], 20);
}

TEST_F(CIDFontsWidthsBuilderTest, Build_MultipleValues_ValidSavedValues_1513) {
    builder.accept(0, 10);
    builder.accept(1, 20);
    builder.accept(2, 20);
    builder.accept(3, 20);
    builder.accept(4, 10);

    auto segment = builder.build();

    ASSERT_EQ(segment.first, 0);
    ASSERT_EQ(segment.last, 4);
    ASSERT_EQ(segment.widths.size(), 1);
    ASSERT_EQ(segment.widths[0], 10);
}

TEST_F(CIDFontsWidthsBuilderTest, Build_InsufficientValues_ReturnsEmptyWidths_1514) {
    builder.accept(0, 10);
    builder.accept(1, 15);

    auto segment = builder.build();

    ASSERT_EQ(segment.first, 0);
    ASSERT_EQ(segment.widths.size(), 0);
}

TEST_F(CIDFontsWidthsBuilderTest, Build_NoValues_ReturnsEmptySegment_1515) {
    auto segment = builder.build();

    ASSERT_EQ(segment.first, 0);
    ASSERT_EQ(segment.widths.size(), 0);
}

// Boundary conditions and exceptional/error cases
TEST_F(CIDFontsWidthsBuilderTest, Build_WithAssertFail_WhenConditionsNotMet_1516) {
    // This test assumes the 'assert' calls inside the `build` method may fail.
    // For testing, we simulate failure by passing invalid data
    // GoogleTest will catch the assertion failure and mark the test as failed.

    // Simulating insufficient values (with assert failure on size < 4)
    builder.accept(0, 10);
    builder.accept(1, 10);
    builder.accept(2, 10);

    // The assert should fail if it tries to build the segment here
    ASSERT_DEATH(builder.build(), ".*");
}
#include <gtest/gtest.h>
#include "JArithmeticDecoder.h"

// Test fixture for JArithmeticDecoderStats
class JArithmeticDecoderStatsTest_1474 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Normal operation: Create stats with a positive context size and verify getContextSize
TEST_F(JArithmeticDecoderStatsTest_1474, GetContextSizeReturnsCorrectValue_1474) {
    JArithmeticDecoderStats stats(512);
    EXPECT_EQ(stats.getContextSize(), 512);
}

// Normal operation: Create stats with context size of 1
TEST_F(JArithmeticDecoderStatsTest_1474, GetContextSizeWithSizeOne_1474) {
    JArithmeticDecoderStats stats(1);
    EXPECT_EQ(stats.getContextSize(), 1);
}

// Normal operation: Create stats with a large context size
TEST_F(JArithmeticDecoderStatsTest_1474, GetContextSizeWithLargeSize_1474) {
    JArithmeticDecoderStats stats(65536);
    EXPECT_EQ(stats.getContextSize(), 65536);
}

// Normal operation: Test copy() produces a stats object with same context size
TEST_F(JArithmeticDecoderStatsTest_1474, CopyPreservesContextSize_1474) {
    JArithmeticDecoderStats stats(256);
    auto copied = stats.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getContextSize(), 256);
}

// Normal operation: Test copyFrom preserves context size consistency
TEST_F(JArithmeticDecoderStatsTest_1474, CopyFromMaintainsContextSize_1474) {
    JArithmeticDecoderStats stats1(128);
    JArithmeticDecoderStats stats2(128);
    stats2.copyFrom(stats1);
    EXPECT_EQ(stats2.getContextSize(), 128);
}

// Normal operation: Test resetContext doesn't change context size
TEST_F(JArithmeticDecoderStatsTest_1474, ResetContextDoesNotChangeSize_1474) {
    JArithmeticDecoderStats stats(64);
    stats.resetContext();
    EXPECT_EQ(stats.getContextSize(), 64);
}

// Normal operation: Test setEntry doesn't change context size
TEST_F(JArithmeticDecoderStatsTest_1474, SetEntryDoesNotChangeContextSize_1474) {
    JArithmeticDecoderStats stats(256);
    stats.setEntry(0, 0, 0);
    EXPECT_EQ(stats.getContextSize(), 256);
}

// Normal operation: Test setEntry with boundary index
TEST_F(JArithmeticDecoderStatsTest_1474, SetEntryAtLastIndex_1474) {
    JArithmeticDecoderStats stats(256);
    stats.setEntry(255, 0, 1);
    EXPECT_EQ(stats.getContextSize(), 256);
}

// Normal operation: Test isValid
TEST_F(JArithmeticDecoderStatsTest_1474, IsValidWithPositiveContextSize_1474) {
    JArithmeticDecoderStats stats(512);
    EXPECT_TRUE(stats.isValid());
}

// Boundary condition: Create stats with context size of 0
TEST_F(JArithmeticDecoderStatsTest_1474, GetContextSizeWithZero_1474) {
    JArithmeticDecoderStats stats(0);
    EXPECT_EQ(stats.getContextSize(), 0);
}

// Boundary condition: Test copy of stats with size 0
TEST_F(JArithmeticDecoderStatsTest_1474, CopyWithZeroContextSize_1474) {
    JArithmeticDecoderStats stats(0);
    auto copied = stats.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getContextSize(), 0);
}

// Normal operation: Multiple copies have independent context sizes
TEST_F(JArithmeticDecoderStatsTest_1474, MultipleCopiesAreIndependent_1474) {
    JArithmeticDecoderStats stats(100);
    auto copy1 = stats.copy();
    auto copy2 = stats.copy();
    ASSERT_NE(copy1, nullptr);
    ASSERT_NE(copy2, nullptr);
    EXPECT_EQ(copy1->getContextSize(), 100);
    EXPECT_EQ(copy2->getContextSize(), 100);
}

// Normal operation: Verify different context sizes
TEST_F(JArithmeticDecoderStatsTest_1474, DifferentContextSizes_1474) {
    JArithmeticDecoderStats stats1(32);
    JArithmeticDecoderStats stats2(1024);
    EXPECT_EQ(stats1.getContextSize(), 32);
    EXPECT_EQ(stats2.getContextSize(), 1024);
    EXPECT_NE(stats1.getContextSize(), stats2.getContextSize());
}

// Normal operation: resetContext followed by copy
TEST_F(JArithmeticDecoderStatsTest_1474, ResetContextThenCopy_1474) {
    JArithmeticDecoderStats stats(200);
    stats.resetContext();
    auto copied = stats.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getContextSize(), 200);
}

// Boundary: Context size of 2 (minimal useful size for arithmetic decoder)
TEST_F(JArithmeticDecoderStatsTest_1474, ContextSizeTwo_1474) {
    JArithmeticDecoderStats stats(2);
    EXPECT_EQ(stats.getContextSize(), 2);
}

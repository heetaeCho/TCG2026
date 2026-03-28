#include <gtest/gtest.h>
#include "JArithmeticDecoder.h"

// Test fixture for JArithmeticDecoderStats
class JArithmeticDecoderStatsTest_1475 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a stats object created with a positive context size is valid
TEST_F(JArithmeticDecoderStatsTest_1475, ConstructWithPositiveContextSizeIsValid_1475)
{
    JArithmeticDecoderStats stats(10);
    EXPECT_TRUE(stats.isValid());
}

// Test that a stats object created with context size 1 is valid
TEST_F(JArithmeticDecoderStatsTest_1475, ConstructWithContextSizeOneIsValid_1475)
{
    JArithmeticDecoderStats stats(1);
    EXPECT_TRUE(stats.isValid());
}

// Test that a stats object created with a large context size is valid
TEST_F(JArithmeticDecoderStatsTest_1475, ConstructWithLargeContextSizeIsValid_1475)
{
    JArithmeticDecoderStats stats(65536);
    EXPECT_TRUE(stats.isValid());
}

// Test that a stats object created with context size 0 is not valid
// (zero size likely means no allocation, so cxTab would be nullptr)
TEST_F(JArithmeticDecoderStatsTest_1475, ConstructWithZeroContextSizeIsNotValid_1475)
{
    JArithmeticDecoderStats stats(0);
    EXPECT_FALSE(stats.isValid());
}

// Test that getContextSize returns the correct value
TEST_F(JArithmeticDecoderStatsTest_1475, GetContextSizeReturnsCorrectValue_1475)
{
    JArithmeticDecoderStats stats(42);
    EXPECT_EQ(stats.getContextSize(), 42);
}

// Test that getContextSize returns zero for zero-initialized stats
TEST_F(JArithmeticDecoderStatsTest_1475, GetContextSizeReturnsZeroForZeroSize_1475)
{
    JArithmeticDecoderStats stats(0);
    EXPECT_EQ(stats.getContextSize(), 0);
}

// Test that copy() produces a valid copy with same context size
TEST_F(JArithmeticDecoderStatsTest_1475, CopyProducesValidObject_1475)
{
    JArithmeticDecoderStats stats(20);
    auto copied = stats.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_TRUE(copied->isValid());
    EXPECT_EQ(copied->getContextSize(), 20);
}

// Test that copy of a zero-context-size stats produces a consistent copy
TEST_F(JArithmeticDecoderStatsTest_1475, CopyOfZeroContextSize_1475)
{
    JArithmeticDecoderStats stats(0);
    auto copied = stats.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getContextSize(), 0);
}

// Test resetContext doesn't invalidate the object
TEST_F(JArithmeticDecoderStatsTest_1475, ResetContextKeepsObjectValid_1475)
{
    JArithmeticDecoderStats stats(10);
    EXPECT_TRUE(stats.isValid());
    stats.resetContext();
    EXPECT_TRUE(stats.isValid());
    EXPECT_EQ(stats.getContextSize(), 10);
}

// Test copyFrom copies data from another stats object
TEST_F(JArithmeticDecoderStatsTest_1475, CopyFromAnotherStats_1475)
{
    JArithmeticDecoderStats stats1(16);
    JArithmeticDecoderStats stats2(16);

    // Set an entry in stats1, then copy to stats2
    stats1.setEntry(0, 0, 0);
    stats2.copyFrom(stats1);

    // Both should remain valid and have same context size
    EXPECT_TRUE(stats1.isValid());
    EXPECT_TRUE(stats2.isValid());
    EXPECT_EQ(stats2.getContextSize(), 16);
}

// Test setEntry with valid index doesn't crash and object remains valid
TEST_F(JArithmeticDecoderStatsTest_1475, SetEntryKeepsObjectValid_1475)
{
    JArithmeticDecoderStats stats(256);
    stats.setEntry(0, 0, 0);
    stats.setEntry(1, 1, 1);
    stats.setEntry(255, 0, 1);
    EXPECT_TRUE(stats.isValid());
}

// Test that copy is independent of the original (modifying copy doesn't affect original)
TEST_F(JArithmeticDecoderStatsTest_1475, CopyIsIndependent_1475)
{
    JArithmeticDecoderStats stats(32);
    stats.setEntry(0, 5, 1);

    auto copied = stats.copy();
    ASSERT_NE(copied, nullptr);

    // Modify the copy
    copied->setEntry(0, 0, 0);
    copied->resetContext();

    // Original should still be valid and unchanged in size
    EXPECT_TRUE(stats.isValid());
    EXPECT_EQ(stats.getContextSize(), 32);
}

// Test constructing with negative context size
TEST_F(JArithmeticDecoderStatsTest_1475, ConstructWithNegativeContextSize_1475)
{
    JArithmeticDecoderStats stats(-1);
    // Negative size likely means no allocation
    EXPECT_FALSE(stats.isValid());
}

// Test that resetContext on a freshly constructed object works
TEST_F(JArithmeticDecoderStatsTest_1475, ResetContextOnFreshObject_1475)
{
    JArithmeticDecoderStats stats(50);
    stats.resetContext();
    EXPECT_TRUE(stats.isValid());
    EXPECT_EQ(stats.getContextSize(), 50);
}

// Test multiple resetContext calls
TEST_F(JArithmeticDecoderStatsTest_1475, MultipleResetContextCalls_1475)
{
    JArithmeticDecoderStats stats(8);
    stats.setEntry(0, 3, 1);
    stats.resetContext();
    stats.resetContext();
    stats.resetContext();
    EXPECT_TRUE(stats.isValid());
    EXPECT_EQ(stats.getContextSize(), 8);
}

// Test copyFrom with same-sized objects
TEST_F(JArithmeticDecoderStatsTest_1475, CopyFromSameSizedObjects_1475)
{
    JArithmeticDecoderStats src(100);
    JArithmeticDecoderStats dst(100);

    src.setEntry(50, 2, 1);
    dst.copyFrom(src);

    EXPECT_TRUE(dst.isValid());
    EXPECT_EQ(dst.getContextSize(), 100);
}

// Test that context size of 1 works correctly with setEntry
TEST_F(JArithmeticDecoderStatsTest_1475, ContextSizeOneSetEntry_1475)
{
    JArithmeticDecoderStats stats(1);
    stats.setEntry(0, 0, 0);
    EXPECT_TRUE(stats.isValid());
    EXPECT_EQ(stats.getContextSize(), 1);
}

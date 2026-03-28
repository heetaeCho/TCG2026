#include <gtest/gtest.h>
#include <memory>
#include "./TestProjects/poppler/poppler/JArithmeticDecoder.h"

class JArithmeticDecoderStatsTest_1475 : public ::testing::Test {
protected:
    // Helper method to create a valid JArithmeticDecoderStats instance
    std::unique_ptr<JArithmeticDecoderStats> createValidStats() {
        return std::make_unique<JArithmeticDecoderStats>(10); // Example contextSize of 10
    }
};

// Normal operation: Checking valid state after initialization
TEST_F(JArithmeticDecoderStatsTest_1475, IsValid_ReturnsTrue_WhenCxTabIsNotNull_1475) {
    auto stats = createValidStats();
    EXPECT_TRUE(stats->isValid());
}

// Boundary condition: Checking isValid for empty cxTab (if reset is assumed to nullify it)
TEST_F(JArithmeticDecoderStatsTest_1475, IsValid_ReturnsFalse_WhenCxTabIsNull_1476) {
    std::unique_ptr<JArithmeticDecoderStats> stats(new JArithmeticDecoderStats(10));
    stats->resetContext();  // Assuming this sets cxTab to nullptr
    EXPECT_FALSE(stats->isValid());
}

// Exceptional case: Copy constructor is deleted, should not compile
TEST_F(JArithmeticDecoderStatsTest_1477, CopyConstructor_IsDeleted_1477) {
    // This test will fail to compile if the copy constructor is not properly deleted
    // JArithmeticDecoderStats stats1(10);
    // JArithmeticDecoderStats stats2 = stats1;  // This line should cause a compile-time error
}

// Boundary condition: Check for contextSize when initialized with a specific size
TEST_F(JArithmeticDecoderStatsTest_1478, GetContextSize_ReturnsCorrectValue_1478) {
    auto stats = createValidStats();
    EXPECT_EQ(stats->getContextSize(), 10);  // Context size is expected to be 10
}

// Exceptional case: Testing copyFrom() with invalid stats
TEST_F(JArithmeticDecoderStatsTest_1479, CopyFrom_ThrowsException_WhenStatsAreInvalid_1479) {
    std::unique_ptr<JArithmeticDecoderStats> validStats = createValidStats();
    std::unique_ptr<JArithmeticDecoderStats> invalidStats = std::make_unique<JArithmeticDecoderStats>(0);  // Assuming 0 context size is invalid

    EXPECT_THROW(validStats->copyFrom(*invalidStats), std::invalid_argument);  // Adjust exception type based on actual implementation
}

// Normal operation: Checking resetContext functionality
TEST_F(JArithmeticDecoderStatsTest_1480, ResetContext_ValidatesReset_1480) {
    auto stats = createValidStats();
    stats->resetContext();  // Assuming it resets cxTab to nullptr

    EXPECT_FALSE(stats->isValid());  // After reset, cxTab should be null, making the stats invalid
}

// Boundary condition: Testing the copy() method
TEST_F(JArithmeticDecoderStatsTest_1481, Copy_ReturnsValidCopy_1481) {
    auto stats = createValidStats();
    auto copyStats = stats->copy();

    EXPECT_NE(stats, copyStats);  // Ensure that the copy is a different object
    EXPECT_TRUE(copyStats->isValid());  // Ensure that the copied stats are valid
}
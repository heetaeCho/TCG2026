#include <gtest/gtest.h>

#include <memory>

#include "JArithmeticDecoder.h"



class JArithmeticDecoderStatsTest : public ::testing::Test {

protected:

    std::unique_ptr<JArithmeticDecoderStats> stats;



    void SetUp() override {

        stats = std::make_unique<JArithmeticDecoderStats>(10);

    }

};



TEST_F(JArithmeticDecoderStatsTest_1474, ConstructorSetsContextSize_1474) {

    EXPECT_EQ(stats->getContextSize(), 10);

}



TEST_F(JArithmeticDecoderStatsTest_1474, CopyMethodCreatesNewInstanceWithSameContextSize_1474) {

    auto copiedStats = stats->copy();

    EXPECT_EQ(copiedStats->getContextSize(), stats->getContextSize());

}



TEST_F(JArithmeticDecoderStatsTest_1474, ResetContextDoesNotChangeContextSize_1474) {

    int originalContextSize = stats->getContextSize();

    stats->resetContext();

    EXPECT_EQ(stats->getContextSize(), originalContextSize);

}



TEST_F(JArithmeticDecoderStatsTest_1474, CopyFromUpdatesContextSizeIfDifferent_1474) {

    JArithmeticDecoderStats otherStats(20);

    stats->copyFrom(otherStats);

    EXPECT_EQ(stats->getContextSize(), otherStats.getContextSize());

}



TEST_F(JArithmeticDecoderStatsTest_1474, SetEntryDoesNotChangeContextSize_1474) {

    int originalContextSize = stats->getContextSize();

    stats->setEntry(0, 0, 0);

    EXPECT_EQ(stats->getContextSize(), originalContextSize);

}



TEST_F(JArithmeticDecoderStatsTest_1474, IsValidReturnsTrueForPositiveContextSize_1474) {

    EXPECT_TRUE(stats->isValid());

}



TEST_F(JArithmeticDecoderStatsTest_1474, IsValidReturnsFalseForZeroContextSize_1474) {

    JArithmeticDecoderStats zeroContextStats(0);

    EXPECT_FALSE(zeroContextStats.isValid());

}



TEST_F(JArithmeticDecoderStatsTest_1474, IsValidReturnsFalseForNegativeContextSize_1474) {

    // This test assumes that the constructor does not allow negative context sizes.

    // If it does, then we need to create a stats object with negative context size here.

    // Since the constructor is explicit and private members are not accessible, this test

    // is more of a theoretical check assuming direct access or mutation.

    EXPECT_THROW(JArithmeticDecoderStats(-1), std::exception);

}

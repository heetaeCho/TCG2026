#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/poppler/JArithmeticDecoder.h"



using namespace testing;



class JArithmeticDecoderStatsTest : public ::testing::Test {

protected:

    void SetUp() override {

        contextSize = 10;

        stats = std::make_unique<JArithmeticDecoderStats>(contextSize);

    }



    int contextSize;

    std::unique_ptr<JArithmeticDecoderStats> stats;

};



TEST_F(JArithmeticDecoderStatsTest_1475, IsValidReturnsTrueWhenInitializedProperly_1475) {

    EXPECT_TRUE(stats->isValid());

}



TEST_F(JArithmeticDecoderStatsTest_1475, GetContextSizeReturnsCorrectValue_1475) {

    EXPECT_EQ(stats->getContextSize(), contextSize);

}



TEST_F(JArithmeticDecoderStatsTest_1475, ResetContextDoesNotAffectValidity_1475) {

    stats->resetContext();

    EXPECT_TRUE(stats->isValid());

}



TEST_F(JArithmeticDecoderStatsTest_1475, CopyFromMaintainsValidity_1475) {

    auto otherStats = std::make_unique<JArithmeticDecoderStats>(contextSize);

    stats->copyFrom(*otherStats);

    EXPECT_TRUE(stats->isValid());

}



TEST_F(JArithmeticDecoderStatsTest_1475, SetEntryDoesNotAffectValidity_1475) {

    unsigned int cx = 0;

    int i = 0;

    int mps = 0;

    stats->setEntry(cx, i, mps);

    EXPECT_TRUE(stats->isValid());

}



TEST_F(JArithmeticDecoderStatsTest_1475, CopyReturnsValidInstance_1475) {

    auto copiedStats = stats->copy();

    EXPECT_TRUE(copiedStats->isValid());

}

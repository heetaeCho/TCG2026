#include <gtest/gtest.h>

#include "CIDFontsWidthsBuilder.h"

#include <vector>



class CIDFontsWidthsBuilderTest_1508 : public ::testing::Test {

protected:

    CIDFontsWidthsBuilder builder;

};



TEST_F(CIDFontsWidthsBuilderTest_1508, TakeSegmentsReturnsEmptyInitially_1508) {

    auto segments = builder.takeSegments();

    EXPECT_TRUE(segments.empty());

}



TEST_F(CIDFontsWidthsBuilderTest_1508, TakeSegmentsClearsInternalState_1508) {

    builder.addWidth(0, 1);

    builder.takeSegments();

    auto segments = builder.takeSegments();

    EXPECT_TRUE(segments.empty());

}



TEST_F(CIDFontsWidthsBuilderTest_1508, TakeSegmentsContainsAddedSegment_1508) {

    builder.addWidth(0, 1);

    auto segments = builder.takeSegments();

    EXPECT_EQ(segments.size(), 1);

}



TEST_F(CIDFontsWidthsBuilderTest_1508, MultipleTakeSegmentsReturnIndependentResults_1508) {

    builder.addWidth(0, 1);

    auto firstCall = builder.takeSegments();

    builder.addWidth(2, 3);

    auto secondCall = builder.takeSegments();

    EXPECT_NE(firstCall, secondCall);

}



TEST_F(CIDFontsWidthsBuilderTest_1508, AddWidthDoesNotAffectTakeSegmentsUntilFinishCalled_1508) {

    builder.addWidth(0, 1);

    auto segmentsBeforeFinish = builder.takeSegments();

    EXPECT_TRUE(segmentsBeforeFinish.empty());

}

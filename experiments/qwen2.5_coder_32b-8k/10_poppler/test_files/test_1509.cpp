#include <gtest/gtest.h>

#include "CIDFontsWidthsBuilder.h"



class CIDFontsWidthsBuilderTest_1509 : public ::testing::Test {

protected:

    CIDFontsWidthsBuilder::SegmentBuilder segmentBuilder;

};



TEST_F(CIDFontsWidthsBuilderTest_1509, AcceptFirstValue_1509) {

    EXPECT_TRUE(segmentBuilder.accept(0, 10));

}



TEST_F(CIDFontsWidthsBuilderTest_1509, AcceptConsecutiveValuesSame_1509) {

    segmentBuilder.accept(0, 10);

    EXPECT_TRUE(segmentBuilder.accept(1, 10));

}



TEST_F(CIDFontsWidthsBuilderTest_1509, AcceptConsecutiveValuesDifferent_1509) {

    segmentBuilder.accept(0, 10);

    EXPECT_TRUE(segmentBuilder.accept(1, 20));

}



TEST_F(CIDFontsWidthsBuilderTest_1509, AcceptNonConsecutiveIndex_1509) {

    segmentBuilder.accept(0, 10);

    EXPECT_FALSE(segmentBuilder.accept(2, 20));

}



TEST_F(CIDFontsWidthsBuilderTest_1509, AcceptFourSameValues_1509) {

    segmentBuilder.accept(0, 10);

    segmentBuilder.accept(1, 10);

    segmentBuilder.accept(2, 10);

    EXPECT_TRUE(segmentBuilder.accept(3, 10));

}



TEST_F(CIDFontsWidthsBuilderTest_1509, AcceptFourDifferentValues_1509) {

    segmentBuilder.accept(0, 10);

    segmentBuilder.accept(1, 20);

    segmentBuilder.accept(2, 30);

    EXPECT_TRUE(segmentBuilder.accept(3, 40));

}



TEST_F(CIDFontsWidthsBuilderTest_1509, AcceptFiveSameValues_1509) {

    segmentBuilder.accept(0, 10);

    segmentBuilder.accept(1, 10);

    segmentBuilder.accept(2, 10);

    segmentBuilder.accept(3, 10);

    EXPECT_TRUE(segmentBuilder.accept(4, 10));

}



TEST_F(CIDFontsWidthsBuilderTest_1509, AcceptFiveDifferentValues_1509) {

    segmentBuilder.accept(0, 10);

    segmentBuilder.accept(1, 20);

    segmentBuilder.accept(2, 30);

    segmentBuilder.accept(3, 40);

    EXPECT_FALSE(segmentBuilder.accept(4, 50));

}



TEST_F(CIDFontsWidthsBuilderTest_1509, AcceptAfterFullSegmentSameValues_1509) {

    segmentBuilder.accept(0, 10);

    segmentBuilder.accept(1, 10);

    segmentBuilder.accept(2, 10);

    segmentBuilder.accept(3, 10);

    EXPECT_FALSE(segmentBuilder.accept(4, 10));

}



TEST_F(CIDFontsWidthsBuilderTest_1509, AcceptAfterFullSegmentDifferentValues_1509) {

    segmentBuilder.accept(0, 10);

    segmentBuilder.accept(1, 20);

    segmentBuilder.accept(2, 30);

    segmentBuilder.accept(3, 40);

    EXPECT_FALSE(segmentBuilder.accept(4, 50));

}



TEST_F(CIDFontsWidthsBuilderTest_1509, AcceptAfterFullSegmentWithDifferentValuesSame_1509) {

    segmentBuilder.accept(0, 10);

    segmentBuilder.accept(1, 20);

    segmentBuilder.accept(2, 30);

    segmentBuilder.accept(3, 40);

    EXPECT_FALSE(segmentBuilder.accept(4, 40));

}



TEST_F(CIDFontsWidthsBuilderTest_1509, AcceptAfterFullSegmentWithDifferentValuesUniqueEnd_1509) {

    segmentBuilder.accept(0, 10);

    segmentBuilder.accept(1, 20);

    segmentBuilder.accept(2, 30);

    segmentBuilder.accept(3, 40);

    EXPECT_FALSE(segmentBuilder.accept(4, 30));

}

#include <gtest/gtest.h>

#include "JBIG2Stream.h"  // Assuming JBIG2Segment is declared in this header



class JBIG2SegmentTest_1811 : public ::testing::Test {

protected:

    JBIG2Segment* segment;



    void SetUp() override {

        segment = new JBIG2Segment(0);

    }



    void TearDown() override {

        delete segment;

    }

};



TEST_F(JBIG2SegmentTest_1811, SetAndGetSegNum_1811) {

    unsigned int testSegNum = 42;

    segment->setSegNum(testSegNum);

    EXPECT_EQ(segment->getSegNum(), testSegNum);

}



TEST_F(JBIG2SegmentTest_1811, DefaultConstructorSetsSegNumToZero_1811) {

    EXPECT_EQ(segment->getSegNum(), 0U);

}



TEST_F(JBIG2SegmentTest_1811, BoundaryCondition_MaxUnsignedInt_1811) {

    unsigned int maxUint = UINT_MAX;

    segment->setSegNum(maxUint);

    EXPECT_EQ(segment->getSegNum(), maxUint);

}

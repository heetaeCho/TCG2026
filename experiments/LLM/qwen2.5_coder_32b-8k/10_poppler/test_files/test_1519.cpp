#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/BBoxOutputDev.h"



class BBoxOutputDevTest_1519 : public ::testing::Test {

protected:

    BBoxOutputDev* bbox_output_dev;



    void SetUp() override {

        bbox_output_dev = new BBoxOutputDev();

    }



    void TearDown() override {

        delete bbox_output_dev;

    }

};



TEST_F(BBoxOutputDevTest_1519, UseDrawCharReturnsTrue_1519) {

    EXPECT_TRUE(bbox_output_dev->useDrawChar());

}



// Assuming getX1, getY1, getX2, and getY2 are expected to return 0.0 by default

TEST_F(BBoxOutputDevTest_1519, GetX1InitialValueIsZero_1519) {

    EXPECT_DOUBLE_EQ(0.0, bbox_output_dev->getX1());

}



TEST_F(BBoxOutputDevTest_1519,GetY1InitialValueIsZero_1519) {

    EXPECT_DOUBLE_EQ(0.0, bbox_output_dev->getY1());

}



TEST_F(BBoxOutputDevTest_1519, GetX2InitialValueIsZero_1519) {

    EXPECT_DOUBLE_EQ(0.0, bbox_output_dev->getX2());

}



TEST_F(BBoxOutputDevTest_1519,GetY2InitialValueIsZero_1519) {

    EXPECT_DOUBLE_EQ(0.0, bbox_output_dev->getY2());

}



// Assuming getHasGraphics is expected to return 0 by default

TEST_F(BBoxOutputDevTest_1519, GetHasGraphicsInitialValueIsFalse_1519) {

    EXPECT_FALSE(bbox_output_dev->getHasGraphics());

}

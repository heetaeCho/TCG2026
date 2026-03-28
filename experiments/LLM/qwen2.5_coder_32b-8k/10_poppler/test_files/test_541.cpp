#include <gtest/gtest.h>

#include "GfxState.h"



class GfxSubpathTest_541 : public ::testing::Test {

protected:

    void SetUp() override {

        subpath = new GfxSubpath(0.0, 0.0);

    }



    void TearDown() override {

        delete subpath;

    }



    GfxSubpath* subpath;

};



TEST_F(GfxSubpathTest_541, InitialState_541) {

    EXPECT_EQ(subpath->getNumPoints(), 1);

    EXPECT_DOUBLE_EQ(subpath->getX(0), 0.0);

    EXPECT_DOUBLE_EQ(subpath->getY(0), 0.0);

    EXPECT_FALSE(subpath->getCurve(0));

    EXPECT_FALSE(subpath->isClosed());

}



TEST_F(GfxSubpathTest_541, LineTo_AddsPoint_541) {

    subpath->lineTo(1.0, 2.0);

    EXPECT_EQ(subpath->getNumPoints(), 2);

    EXPECT_DOUBLE_EQ(subpath->getX(1), 1.0);

    EXPECT_DOUBLE_EQ(subpath->getY(1), 2.0);

    EXPECT_FALSE(subpath->getCurve(1));

}



TEST_F(GfxSubpathTest_541, CurveTo_AddsPoints_541) {

    subpath->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

    EXPECT_EQ(subpath->getNumPoints(), 4);

    EXPECT_TRUE(subpath->getCurve(1));

    EXPECT_TRUE(subpath->getCurve(2));

    EXPECT_TRUE(subpath->getCurve(3));

}



TEST_F(GfxSubpathTest_541, Close_ClosesPath_541) {

    subpath->close();

    EXPECT_TRUE(subpath->isClosed());

}



TEST_F(GfxSubpathTest_541, Offset_ModifiesCoordinates_541) {

    subpath->lineTo(1.0, 2.0);

    subpath->offset(3.0, 4.0);

    EXPECT_DOUBLE_EQ(subpath->getX(0), 3.0);

    EXPECT_DOUBLE_EQ(subpath->getY(0), 4.0);

    EXPECT_DOUBLE_EQ(subpath->getX(1), 4.0);

    EXPECT_DOUBLE_EQ(subpath->getY(1), 6.0);

}



TEST_F(GfxSubpathTest_541, Copy_ReturnsIdenticalInstance_541) {

    subpath->lineTo(1.0, 2.0);

    GfxSubpath* copy = subpath->copy();

    EXPECT_EQ(copy->getNumPoints(), subpath->getNumPoints());

    EXPECT_DOUBLE_EQ(copy->getX(0), subpath->getX(0));

    EXPECT_DOUBLE_EQ(copy->getY(0), subpath->getY(0));

    EXPECT_DOUBLE_EQ(copy->getX(1), subpath->getX(1));

    EXPECT_DOUBLE_EQ(copy->getY(1), subpath->getY(1));

    delete copy;

}



TEST_F(GfxSubpathTest_541, GetLastX_ReturnsCorrectValue_541) {

    subpath->lineTo(1.0, 2.0);

    EXPECT_DOUBLE_EQ(subpath->getLastX(), 1.0);

}



TEST_F(GfxSubpathTest_541, GetLastY_ReturnsCorrectValue_541) {

    subpath->lineTo(1.0, 2.0);

    EXPECT_DOUBLE_EQ(subpath->getLastY(), 2.0);

}

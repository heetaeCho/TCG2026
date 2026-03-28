#include <gtest/gtest.h>

#include "GfxState.h"



class GfxSubpathTest : public ::testing::Test {

protected:

    GfxSubpath* subpath;



    void SetUp() override {

        subpath = new GfxSubpath(0.0, 0.0);

    }



    void TearDown() override {

        delete subpath;

    }

};



TEST_F(GfxSubpathTest_547, ConstructorInitializesPoints_547) {

    EXPECT_DOUBLE_EQ(subpath->getX(0), 0.0);

    EXPECT_DOUBLE_EQ(subpath->getY(0), 0.0);

}



TEST_F(GfxSubpathTest_547, LineToAddsPoint_547) {

    subpath->lineTo(1.0, 2.0);

    EXPECT_EQ(subpath->getNumPoints(), 2);

    EXPECT_DOUBLE_EQ(subpath->getX(1), 1.0);

    EXPECT_DOUBLE_EQ(subpath->getY(1), 2.0);

}



TEST_F(GfxSubpathTest_547, CurveToAddsPoints_547) {

    subpath->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

    EXPECT_EQ(subpath->getNumPoints(), 4);

    EXPECT_DOUBLE_EQ(subpath->getX(1), 1.0);

    EXPECT_DOUBLE_EQ(subpath->getY(1), 2.0);

    EXPECT_DOUBLE_EQ(subpath->getX(2), 3.0);

    EXPECT_DOUBLE_EQ(subpath->getY(2), 4.0);

    EXPECT_DOUBLE_EQ(subpath->getX(3), 5.0);

    EXPECT_DOUBLE_EQ(subpath->getY(3), 6.0);

}



TEST_F(GfxSubpathTest_547, CloseMarksPathAsClosed_547) {

    subpath->close();

    EXPECT_TRUE(subpath->isClosed());

}



TEST_F(GfxSubpathTest_547, OffsetMovesAllPoints_547) {

    subpath->lineTo(1.0, 2.0);

    subpath->offset(3.0, 4.0);

    EXPECT_DOUBLE_EQ(subpath->getX(0), 3.0);

    EXPECT_DOUBLE_EQ(subpath->getY(0), 4.0);

    EXPECT_DOUBLE_EQ(subpath->getX(1), 4.0);

    EXPECT_DOUBLE_EQ(subpath->getY(1), 6.0);

}



TEST_F(GfxSubpathTest_547, CopyCreatesIndependentInstance_547) {

    subpath->lineTo(1.0, 2.0);

    GfxSubpath* copy = subpath->copy();

    delete subpath;

    EXPECT_DOUBLE_EQ(copy->getX(1), 1.0);

    EXPECT_DOUBLE_EQ(copy->getY(1), 2.0);

    delete copy;

}



TEST_F(GfxSubpathTest_547, GetLastXReturnsCorrectValue_547) {

    subpath->lineTo(1.0, 2.0);

    EXPECT_DOUBLE_EQ(subpath->getLastX(), 1.0);

}



TEST_F(GfxSubpathTest_547, GetLastYReturnsCorrectValue_547) {

    subpath->lineTo(1.0, 2.0);

    EXPECT_DOUBLE_EQ(subpath->getLastY(), 2.0);

}



TEST_F(GfxSubpathTest_547, SetXUpdatesPoint_547) {

    subpath->setX(0, 3.0);

    EXPECT_DOUBLE_EQ(subpath->getX(0), 3.0);

}



TEST_F(GfxSubpathTest_547, SetYUpdatesPoint_547) {

    subpath->setY(0, 4.0);

    EXPECT_DOUBLE_EQ(subpath->getY(0), 4.0);

}



TEST_F(GfxSubpathTest_547, GetCurveReturnsFalseInitially_547) {

    EXPECT_FALSE(subpath->getCurve(0));

}

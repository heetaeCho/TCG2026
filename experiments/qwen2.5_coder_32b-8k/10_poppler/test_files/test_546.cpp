#include <gtest/gtest.h>

#include "GfxState.h"



class GfxSubpathTest_546 : public ::testing::Test {

protected:

    void SetUp() override {

        subpath = new GfxSubpath(0.0, 0.0);

    }



    void TearDown() override {

        delete subpath;

    }



    GfxSubpath* subpath;

};



TEST_F(GfxSubpathTest_546, GetNumPointsInitiallyZero_546) {

    EXPECT_EQ(subpath->getNumPoints(), 0);

}



TEST_F(GfxSubpathTest_546, LineToIncreasesPointCount_546) {

    subpath->lineTo(1.0, 2.0);

    EXPECT_EQ(subpath->getNumPoints(), 1);

}



TEST_F(GfxSubpathTest_546, CurveToIncreasesPointCountByThree_546) {

    subpath->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

    EXPECT_EQ(subpath->getNumPoints(), 3);

}



TEST_F(GfxSubpathTest_546, CloseMarksSubpathAsClosed_546) {

    subpath->close();

    EXPECT_TRUE(subpath->isClosed());

}



TEST_F(GfxSubpathTest_546, OffsetMovesAllPoints_546) {

    subpath->lineTo(1.0, 2.0);

    subpath->offset(3.0, 4.0);

    EXPECT_EQ(subpath->getX(0), 4.0);

    EXPECT_EQ(subpath->getY(0), 6.0);

}



TEST_F(GfxSubpathTest_546, CopyCreatesIndependentInstance_546) {

    subpath->lineTo(1.0, 2.0);

    GfxSubpath* copy = subpath->copy();

    EXPECT_EQ(copy->getNumPoints(), 1);

    delete copy;

}



TEST_F(GfxSubpathTest_546, SetXUpdatesPointCoordinate_546) {

    subpath->lineTo(1.0, 2.0);

    subpath->setX(0, 5.0);

    EXPECT_EQ(subpath->getX(0), 5.0);

}



TEST_F(GfxSubpathTest_546, SetYUpdatesPointCoordinate_546) {

    subpath->lineTo(1.0, 2.0);

    subpath->setY(0, 6.0);

    EXPECT_EQ(subpath->getY(0), 6.0);

}



TEST_F(GfxSubpathTest_546, GetLastXReturnsCorrectValue_546) {

    subpath->lineTo(1.0, 2.0);

    EXPECT_EQ(subpath->getLastX(), 1.0);

}



TEST_F(GfxSubpathTest_546, GetLastYReturnsCorrectValue_546) {

    subpath->lineTo(1.0, 2.0);

    EXPECT_EQ(subpath->getLastY(), 2.0);

}

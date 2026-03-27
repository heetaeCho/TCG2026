#include <gtest/gtest.h>

#include "GfxState.h"



class GfxSubpathTest_550 : public ::testing::Test {

protected:

    GfxSubpath* subpath;



    void SetUp() override {

        subpath = new GfxSubpath(0.0, 0.0);

    }



    void TearDown() override {

        delete subpath;

    }

};



TEST_F(GfxSubpathTest_550, InitialStateNotClosed_550) {

    EXPECT_FALSE(subpath->isClosed());

}



TEST_F(GfxSubpathTest_550, CloseSetsClosedTrue_550) {

    subpath->close();

    EXPECT_TRUE(subpath->isClosed());

}



TEST_F(GfxSubpathTest_550, LineToIncreasesPointCount_550) {

    int initialCount = subpath->getNumPoints();

    subpath->lineTo(1.0, 1.0);

    EXPECT_EQ(subpath->getNumPoints(), initialCount + 1);

}



TEST_F(GfxSubpathTest_550, CurveToIncreasesPointCountByThree_550) {

    int initialCount = subpath->getNumPoints();

    subpath->curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);

    EXPECT_EQ(subpath->getNumPoints(), initialCount + 3);

}



TEST_F(GfxSubpathTest_550, OffsetDoesNotChangePointCount_550) {

    int initialCount = subpath->getNumPoints();

    subpath->offset(1.0, 1.0);

    EXPECT_EQ(subpath->getNumPoints(), initialCount);

}



TEST_F(GfxSubpathTest_550, CopyReturnsNewInstanceWithSamePoints_550) {

    subpath->lineTo(1.0, 1.0);

    GfxSubpath* copiedSubpath = subpath->copy();

    EXPECT_EQ(subpath->getNumPoints(), copiedSubpath->getNumPoints());

    EXPECT_EQ(subpath->getX(0), copiedSubpath->getX(0));

    EXPECT_EQ(subpath->getY(0), copiedSubpath->getY(0));

    EXPECT_EQ(subpath->getX(1), copiedSubpath->getX(1));

    EXPECT_EQ(subpath->getY(1), copiedSubpath->getY(1));

    delete copiedSubpath;

}



TEST_F(GfxSubpathTest_550, GetLastXReturnsCorrectValue_550) {

    subpath->lineTo(1.0, 1.0);

    EXPECT_EQ(subpath->getLastX(), 1.0);

}



TEST_F(GfxSubpathTest_550, GetLastYReturnsCorrectValue_550) {

    subpath->lineTo(1.0, 2.0);

    EXPECT_EQ(subpath->getLastY(), 2.0);

}



TEST_F(GfxSubpathTest_550, SetXUpdatesPointCorrectly_550) {

    subpath->lineTo(1.0, 1.0);

    subpath->setX(1, 3.0);

    EXPECT_EQ(subpath->getX(1), 3.0);

}



TEST_F(GfxSubpathTest_550, SetYUpdatesPointCorrectly_550) {

    subpath->lineTo(1.0, 1.0);

    subpath->setY(1, 4.0);

    EXPECT_EQ(subpath->getY(1), 4.0);

}



TEST_F(GfxSubpathTest_550, GetCurveReturnsFalseForStraightLines_550) {

    subpath->lineTo(1.0, 1.0);

    EXPECT_FALSE(subpath->getCurve(0));

}



TEST_F(GfxSubpathTest_550, GetCurveReturnsTrueForCurves_550) {

    subpath->curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);

    EXPECT_TRUE(subpath->getCurve(0));

}

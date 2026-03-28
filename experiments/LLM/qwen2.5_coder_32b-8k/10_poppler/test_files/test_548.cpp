#include <gtest/gtest.h>

#include "GfxState.h"



class GfxSubpathTest : public ::testing::Test {

protected:

    void SetUp() override {

        subpath = new GfxSubpath(0.0, 0.0);

    }



    void TearDown() override {

        delete subpath;

    }



    GfxSubpath* subpath;

};



TEST_F(GfxSubpathTest_548, InitialLastXIsZero_548) {

    EXPECT_EQ(subpath->getLastX(), 0.0);

}



TEST_F(GfxSubpathTest_548, LineToUpdatesLastX_548) {

    subpath->lineTo(1.0, 2.0);

    EXPECT_EQ(subpath->getLastX(), 1.0);

}



TEST_F(GfxSubpathTest_548, CurveToUpdatesLastX_548) {

    subpath->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

    EXPECT_EQ(subpath->getLastX(), 5.0);

}



TEST_F(GfxSubpathTest_548, GetNumPointsInitiallyOne_548) {

    EXPECT_EQ(subpath->getNumPoints(), 1);

}



TEST_F(GfxSubpathTest_548, LineToIncreasesPointCount_548) {

    subpath->lineTo(1.0, 2.0);

    EXPECT_EQ(subpath->getNumPoints(), 2);

}



TEST_F(GfxSubpathTest_548, CurveToIncreasesPointCountByThree_548) {

    subpath->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

    EXPECT_EQ(subpath->getNumPoints(), 4);

}



TEST_F(GfxSubpathTest_548, CloseSetsClosedTrue_548) {

    subpath->close();

    EXPECT_TRUE(subpath->isClosed());

}



TEST_F(GfxSubpathTest_548, OffsetModifiesLastX_548) {

    subpath->lineTo(1.0, 2.0);

    subpath->offset(3.0, 0.0);

    EXPECT_EQ(subpath->getLastX(), 4.0);

}



TEST_F(GfxSubpathTest_548, CopyPreservesLastX_548) {

    subpath->lineTo(1.0, 2.0);

    GfxSubpath* copy = subpath->copy();

    EXPECT_EQ(copy->getLastX(), 1.0);

    delete copy;

}



TEST_F(GfxSubpathTest_548, GetXReturnsCorrectValue_548) {

    subpath->lineTo(1.0, 2.0);

    EXPECT_EQ(subpath->getX(1), 1.0);

}



TEST_F(GfxSubpathTest_548, SetXUpdatesPointX_548) {

    subpath->setX(0, 1.0);

    EXPECT_EQ(subpath->getX(0), 1.0);

}



TEST_F(GfxSubpathTest_548, GetYReturnsCorrectValue_548) {

    subpath->lineTo(1.0, 2.0);

    EXPECT_EQ(subpath->getY(1), 2.0);

}



TEST_F(GfxSubpathTest_548, SetYUpdatesPointY_548) {

    subpath->setY(0, 2.0);

    EXPECT_EQ(subpath->getY(0), 2.0);

}



TEST_F(GfxSubpathTest_548, GetCurveInitiallyFalse_548) {

    EXPECT_FALSE(subpath->getCurve(0));

}



TEST_F(GfxSubpathTest_548, CurveToSetsCurveTrueForControlPoints_548) {

    subpath->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

    EXPECT_TRUE(subpath->getCurve(1));

    EXPECT_TRUE(subpath->getCurve(2));

}



TEST_F(GfxSubpathTest_548, GetLastYInitiallyZero_548) {

    EXPECT_EQ(subpath->getLastY(), 0.0);

}



TEST_F(GfxSubpathTest_548, LineToUpdatesLastY_548) {

    subpath->lineTo(1.0, 2.0);

    EXPECT_EQ(subpath->getLastY(), 2.0);

}



TEST_F(GfxSubpathTest_548, CurveToUpdatesLastY_548) {

    subpath->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

    EXPECT_EQ(subpath->getLastY(), 6.0);

}

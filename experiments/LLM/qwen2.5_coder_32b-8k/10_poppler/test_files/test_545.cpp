#include <gtest/gtest.h>

#include "GfxState.h"



class GfxSubpathTest : public ::testing::Test {

protected:

    GfxSubpath *subpath;



    void SetUp() override {

        subpath = new GfxSubpath(0.0, 0.0);

    }



    void TearDown() override {

        delete subpath;

    }

};



TEST_F(GfxSubpathTest_545, InitialStateGetNumPoints_545) {

    EXPECT_EQ(subpath->getNumPoints(), 1);

}



TEST_F(GfxSubpathTest_545, LineToIncreasesPointCount_545) {

    subpath->lineTo(1.0, 1.0);

    EXPECT_EQ(subpath->getNumPoints(), 2);

}



TEST_F(GfxSubpathTest_545, CurveToIncreasesPointCountByThree_545) {

    subpath->curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);

    EXPECT_EQ(subpath->getNumPoints(), 4);

}



TEST_F(GfxSubpathTest_545, GetXReturnsInitialXValue_545) {

    EXPECT_DOUBLE_EQ(subpath->getX(0), 0.0);

}



TEST_F(GfxSubpathTest_545, GetYReturnsInitialYValue_545) {

    EXPECT_DOUBLE_EQ(subpath->getY(0), 0.0);

}



TEST_F(GfxSubpathTest_545, SetXChangesXValue_545) {

    subpath->setX(0, 1.0);

    EXPECT_DOUBLE_EQ(subpath->getX(0), 1.0);

}



TEST_F(GfxSubpathTest_545, SetYChangesYValue_545) {

    subpath->setY(0, 1.0);

    EXPECT_DOUBLE_EQ(subpath->getY(0), 1.0);

}



TEST_F(GfxSubpathTest_545, LastXReturnsCorrectValueAfterLineTo_545) {

    subpath->lineTo(2.0, 3.0);

    EXPECT_DOUBLE_EQ(subpath->getLastX(), 2.0);

}



TEST_F(GfxSubpathTest_545, LastYReturnsCorrectValueAfterLineTo_545) {

    subpath->lineTo(2.0, 3.0);

    EXPECT_DOUBLE_EQ(subpath->getLastY(), 3.0);

}



TEST_F(GfxSubpathTest_545, CloseMarksPathAsClosed_545) {

    subpath->close();

    EXPECT_TRUE(subpath->isClosed());

}



TEST_F(GfxSubpathTest_545, OffsetMovesPointsCorrectly_545) {

    subpath->lineTo(1.0, 1.0);

    subpath->offset(2.0, 3.0);

    EXPECT_DOUBLE_EQ(subpath->getX(0), 2.0);

    EXPECT_DOUBLE_EQ(subpath->getY(0), 3.0);

    EXPECT_DOUBLE_EQ(subpath->getX(1), 3.0);

    EXPECT_DOUBLE_EQ(subpath->getY(1), 4.0);

}



TEST_F(GfxSubpathTest_545, GetCurveInitiallyFalse_545) {

    EXPECT_FALSE(subpath->getCurve(0));

}



TEST_F(GfxSubpathTest_545, CurveToSetsCurveFlagTrue_545) {

    subpath->curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);

    EXPECT_TRUE(subpath->getCurve(0));

}



TEST_F(GfxSubpathTest_545, BoundaryConditionGetNumPointsAfterMultipleOperations_545) {

    subpath->lineTo(1.0, 1.0);

    subpath->curveTo(2.0, 2.0, 3.0, 3.0, 4.0, 4.0);

    subpath->close();

    EXPECT_EQ(subpath->getNumPoints(), 5);

}



TEST_F(GfxSubpathTest_545, BoundaryConditionGetXAndYWithInvalidIndex_545) {

    EXPECT_DOUBLE_EQ(subpath->getX(1), 0.0); // Assuming out-of-bounds returns default value

    EXPECT_DOUBLE_EQ(subpath->getY(1), 0.0);

}



TEST_F(GfxSubpathTest_545, BoundaryConditionGetCurveWithInvalidIndex_545) {

    EXPECT_FALSE(subpath->getCurve(1)); // Assuming out-of-bounds returns false

}

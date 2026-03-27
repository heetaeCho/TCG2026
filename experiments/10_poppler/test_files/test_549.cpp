#include <gtest/gtest.h>

#include "GfxState.h"



class GfxSubpathTest_549 : public ::testing::Test {

protected:

    void SetUp() override {

        subpath = new GfxSubpath(0.0, 0.0);

    }



    void TearDown() override {

        delete subpath;

    }



    GfxSubpath* subpath;

};



TEST_F(GfxSubpathTest_549, InitialYValue_549) {

    EXPECT_DOUBLE_EQ(subpath->getLastY(), 0.0);

}



TEST_F(GfxSubpathTest_549, LineToUpdatesLastY_549) {

    subpath->lineTo(1.0, 2.0);

    EXPECT_DOUBLE_EQ(subpath->getLastY(), 2.0);

}



TEST_F(GfxSubpathTest_549, CurveToUpdatesLastY_549) {

    subpath->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

    EXPECT_DOUBLE_EQ(subpath->getLastY(), 6.0);

}



TEST_F(GfxSubpathTest_549, OffsetUpdatesLastY_549) {

    subpath->lineTo(1.0, 2.0);

    subpath->offset(0.0, 3.0);

    EXPECT_DOUBLE_EQ(subpath->getLastY(), 5.0);

}



TEST_F(GfxSubpathTest_549, CopyPreservesLastY_549) {

    subpath->lineTo(1.0, 2.0);

    GfxSubpath* copy = subpath->copy();

    EXPECT_DOUBLE_EQ(copy->getLastY(), 2.0);

    delete copy;

}



TEST_F(GfxSubpathTest_549, GetNumPointsAfterLineTo_549) {

    subpath->lineTo(1.0, 2.0);

    EXPECT_EQ(subpath->getNumPoints(), 2);

}



TEST_F(GfxSubpathTest_549, GetNumPointsAfterCurveTo_549) {

    subpath->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

    EXPECT_EQ(subpath->getNumPoints(), 4);

}



TEST_F(GfxSubpathTest_549, GetYBoundaryCondition_549) {

    subpath->lineTo(1.0, 2.0);

    EXPECT_DOUBLE_EQ(subpath->getY(0), 0.0);

    EXPECT_DOUBLE_EQ(subpath->getY(1), 2.0);

}



TEST_F(GfxSubpathTest_549, SetYUpdatesCorrectly_549) {

    subpath->lineTo(1.0, 2.0);

    subpath->setY(1, 3.0);

    EXPECT_DOUBLE_EQ(subpath->getY(1), 3.0);

}



TEST_F(GfxSubpathTest_549, IsClosedInitiallyFalse_549) {

    EXPECT_FALSE(subpath->isClosed());

}



TEST_F(GfxSubpathTest_549, CloseSetsIsClosedTrue_549) {

    subpath->close();

    EXPECT_TRUE(subpath->isClosed());

}

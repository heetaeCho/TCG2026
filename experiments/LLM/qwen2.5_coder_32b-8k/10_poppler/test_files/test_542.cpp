#include <gtest/gtest.h>

#include "GfxState.h"



class GfxSubpathTest_542 : public ::testing::Test {

protected:

    void SetUp() override {

        subpath = new GfxSubpath(0.0, 0.0);

    }



    void TearDown() override {

        delete subpath;

    }



    GfxSubpath* subpath;

};



TEST_F(GfxSubpathTest_542, InitialStateNumPoints_542) {

    EXPECT_EQ(subpath->getNumPoints(), 1);

}



TEST_F(GfxSubpathTest_542, LineToIncreasesPointCount_542) {

    subpath->lineTo(1.0, 1.0);

    EXPECT_EQ(subpath->getNumPoints(), 2);

}



TEST_F(GfxSubpathTest_542, CurveToIncreasesPointCount_542) {

    subpath->curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);

    EXPECT_EQ(subpath->getNumPoints(), 4);

}



TEST_F(GfxSubpathTest_542, CloseMarksPathAsClosed_542) {

    subpath->close();

    EXPECT_TRUE(subpath->isClosed());

}



TEST_F(GfxSubpathTest_542, GetLastPointAfterLineTo_542) {

    subpath->lineTo(1.0, 2.0);

    EXPECT_EQ(subpath->getLastX(), 1.0);

    EXPECT_EQ(subpath->getLastY(), 2.0);

}



TEST_F(GfxSubpathTest_542, GetLastPointAfterCurveTo_542) {

    subpath->curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);

    EXPECT_EQ(subpath->getLastX(), 3.0);

    EXPECT_EQ(subpath->getLastY(), 3.0);

}



TEST_F(GfxSubpathTest_542, SetPointModifiesCoordinates_542) {

    subpath->lineTo(1.0, 1.0);

    subpath->setX(1, 5.0);

    subpath->setY(1, 6.0);

    EXPECT_EQ(subpath->getX(1), 5.0);

    EXPECT_EQ(subpath->getY(1), 6.0);

}



TEST_F(GfxSubpathTest_542, OffsetMovesPoints_542) {

    subpath->lineTo(1.0, 1.0);

    subpath->offset(2.0, 3.0);

    EXPECT_EQ(subpath->getX(0), 2.0);

    EXPECT_EQ(subpath->getY(0), 3.0);

    EXPECT_EQ(subpath->getX(1), 3.0);

    EXPECT_EQ(subpath->getY(1), 4.0);

}



TEST_F(GfxSubpathTest_542, CopyCreatesIdenticalPath_542) {

    subpath->lineTo(1.0, 1.0);

    GfxSubpath* copied = subpath->copy();

    EXPECT_EQ(subpath->getNumPoints(), copied->getNumPoints());

    for (int i = 0; i < subpath->getNumPoints(); ++i) {

        EXPECT_EQ(subpath->getX(i), copied->getX(i));

        EXPECT_EQ(subpath->getY(i), copied->getY(i));

    }

    delete copied;

}



TEST_F(GfxSubpathTest_542, GetCurveInitiallyFalse_542) {

    subpath->lineTo(1.0, 1.0);

    EXPECT_FALSE(subpath->getCurve(0));

    EXPECT_FALSE(subpath->getCurve(1));

}



TEST_F(GfxSubpathTest_542, GetCurveTrueAfterCurveTo_542) {

    subpath->curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);

    EXPECT_FALSE(subpath->getCurve(0));

    EXPECT_TRUE(subpath->getCurve(1));

    EXPECT_TRUE(subpath->getCurve(2));

}



TEST_F(GfxSubpathTest_542, BoundaryConditionInitialGetPoint_542) {

    EXPECT_EQ(subpath->getX(0), 0.0);

    EXPECT_EQ(subpath->getY(0), 0.0);

}



TEST_F(GfxSubpathTest_542, BoundaryConditionOutofBoundsGetPoint_542) {

    EXPECT_THROW(subpath->getX(1), std::out_of_range); // Assuming implementation throws exception for out of bounds

    EXPECT_THROW(subpath->getY(1), std::out_of_range);

}



TEST_F(GfxSubpathTest_542, BoundaryConditionSetPoint_542) {

    EXPECT_THROW(subpath->setX(1, 1.0), std::out_of_range);

    EXPECT_THROW(subpath->setY(1, 1.0), std::out_of_range);

}

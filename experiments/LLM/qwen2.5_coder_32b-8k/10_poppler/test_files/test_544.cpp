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



TEST_F(GfxSubpathTest_544, InitialCoordinates_544) {

    EXPECT_DOUBLE_EQ(subpath->getX(0), 0.0);

    EXPECT_DOUBLE_EQ(subpath->getY(0), 0.0);

}



TEST_F(GfxSubpathTest_544, LineToUpdatesCoordinates_544) {

    subpath->lineTo(1.0, 2.0);

    EXPECT_DOUBLE_EQ(subpath->getX(1), 1.0);

    EXPECT_DOUBLE_EQ(subpath->getY(1), 2.0);

}



TEST_F(GfxSubpathTest_544, CurveToUpdatesCoordinates_544) {

    subpath->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

    EXPECT_DOUBLE_EQ(subpath->getX(1), 1.0);

    EXPECT_DOUBLE_EQ(subpath->getY(1), 2.0);

    EXPECT_DOUBLE_EQ(subpath->getX(2), 3.0);

    EXPECT_DOUBLE_EQ(subpath->getY(2), 4.0);

    EXPECT_DOUBLE_EQ(subpath->getX(3), 5.0);

    EXPECT_DOUBLE_EQ(subpath->getY(3), 6.0);

}



TEST_F(GfxSubpathTest_544, CloseMarksPathAsClosed_544) {

    subpath->close();

    EXPECT_TRUE(subpath->isClosed());

}



TEST_F(GfxSubpathTest_544, OffsetAdjustsCoordinates_544) {

    subpath->lineTo(1.0, 2.0);

    subpath->offset(3.0, 4.0);

    EXPECT_DOUBLE_EQ(subpath->getX(0), 3.0);

    EXPECT_DOUBLE_EQ(subpath->getY(0), 4.0);

    EXPECT_DOUBLE_EQ(subpath->getX(1), 4.0);

    EXPECT_DOUBLE_EQ(subpath->getY(1), 6.0);

}



TEST_F(GfxSubpathTest_544, GetNumPointsCountsCorrectly_544) {

    EXPECT_EQ(subpath->getNumPoints(), 1);

    subpath->lineTo(1.0, 2.0);

    EXPECT_EQ(subpath->getNumPoints(), 2);

}



TEST_F(GfxSubpathTest_544, GetLastCoordinatesReturnsCorrectValues_544) {

    subpath->lineTo(1.0, 2.0);

    EXPECT_DOUBLE_EQ(subpath->getLastX(), 1.0);

    EXPECT_DOUBLE_EQ(subpath->getLastY(), 2.0);

}



TEST_F(GfxSubpathTest_544, SetCoordinatesUpdatesCorrectly_544) {

    subpath->setX(0, 3.0);

    subpath->setY(0, 4.0);

    EXPECT_DOUBLE_EQ(subpath->getX(0), 3.0);

    EXPECT_DOUBLE_EQ(subpath->getY(0), 4.0);

}



TEST_F(GfxSubpathTest_544, BoundaryConditionIndexOutOfRange_544) {

    EXPECT_THROW(subpath->getX(1), std::exception);

    EXPECT_THROW(subpath->getY(1), std::exception);

}

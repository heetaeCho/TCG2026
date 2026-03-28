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



TEST_F(GfxSubpathTest_543, InitialPointCoordinates_543) {

    EXPECT_EQ(subpath->getX(0), 0.0);

    EXPECT_EQ(subpath->getY(0), 0.0);

}



TEST_F(GfxSubpathTest_543, LineToUpdatesCoordinates_543) {

    subpath->lineTo(1.0, 2.0);

    EXPECT_EQ(subpath->getX(1), 1.0);

    EXPECT_EQ(subpath->getY(1), 2.0);

}



TEST_F(GfxSubpathTest_543, CurveToUpdateCoordinates_543) {

    subpath->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

    EXPECT_EQ(subpath->getNumPoints(), 4);

    EXPECT_EQ(subpath->getX(1), 1.0);

    EXPECT_EQ(subpath->getY(1), 2.0);

    EXPECT_EQ(subpath->getX(2), 3.0);

    EXPECT_EQ(subpath->getY(2), 4.0);

    EXPECT_EQ(subpath->getX(3), 5.0);

    EXPECT_EQ(subpath->getY(3), 6.0);

}



TEST_F(GfxSubpathTest_543, CloseMarksPathAsClosed_543) {

    EXPECT_FALSE(subpath->isClosed());

    subpath->close();

    EXPECT_TRUE(subpath->isClosed());

}



TEST_F(GfxSubpathTest_543, OffsetChangesCoordinates_543) {

    subpath->lineTo(1.0, 2.0);

    subpath->offset(1.0, 1.0);

    EXPECT_EQ(subpath->getX(0), 1.0);

    EXPECT_EQ(subpath->getY(0), 1.0);

    EXPECT_EQ(subpath->getX(1), 2.0);

    EXPECT_EQ(subpath->getY(1), 3.0);

}



TEST_F(GfxSubpathTest_543, CopyCreatesIndependentInstance_543) {

    subpath->lineTo(1.0, 2.0);

    GfxSubpath* copy = subpath->copy();

    EXPECT_EQ(copy->getX(1), 1.0);

    EXPECT_EQ(copy->getY(1), 2.0);



    copy->setX(1, 3.0);

    EXPECT_EQ(subpath->getX(1), 1.0);

    EXPECT_EQ(copy->getX(1), 3.0);



    delete copy;

}



TEST_F(GfxSubpathTest_543, GetLastCoordinates_ReturnsCorrectValues_543) {

    subpath->lineTo(1.0, 2.0);

    EXPECT_EQ(subpath->getLastX(), 1.0);

    EXPECT_EQ(subpath->getLastY(), 2.0);



    subpath->curveTo(3.0, 4.0, 5.0, 6.0, 7.0, 8.0);

    EXPECT_EQ(subpath->getLastX(), 7.0);

    EXPECT_EQ(subpath->getLastY(), 8.0);

}



TEST_F(GfxSubpathTest_543, GetNumPoints_ReturnsCorrectCount_543) {

    EXPECT_EQ(subpath->getNumPoints(), 1);

    subpath->lineTo(1.0, 2.0);

    EXPECT_EQ(subpath->getNumPoints(), 2);

    subpath->curveTo(3.0, 4.0, 5.0, 6.0, 7.0, 8.0);

    EXPECT_EQ(subpath->getNumPoints(), 4);

}



TEST_F(GfxSubpathTest_543, GetCurve_ReturnsFalseForStraightLines_543) {

    subpath->lineTo(1.0, 2.0);

    EXPECT_FALSE(subpath->getCurve(1));

}



TEST_F(GfxSubpathTest_543, GetCurve_ReturnsTrueForCurves_543) {

    subpath->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

    EXPECT_TRUE(subpath->getCurve(1));

    EXPECT_TRUE(subpath->getCurve(2));

}



TEST_F(GfxSubpathTest_543, SetCoordinatesUpdatesPoints_543) {

    subpath->lineTo(1.0, 2.0);

    subpath->setX(1, 3.0);

    subpath->setY(1, 4.0);

    EXPECT_EQ(subpath->getX(1), 3.0);

    EXPECT_EQ(subpath->getY(1), 4.0);

}



TEST_F(GfxSubpathTest_543, AccessingOutOfRangePoint_543) {

    EXPECT_THROW(subpath->getX(1), std::out_of_range);

    EXPECT_THROW(subpath->getY(1), std::out_of_range);

}

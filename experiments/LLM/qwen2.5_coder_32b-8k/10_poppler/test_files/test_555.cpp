#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"



class GfxPathTest : public ::testing::Test {

protected:

    GfxPath* path;



    void SetUp() override {

        path = new GfxPath();

    }



    void TearDown() override {

        delete path;

    }

};



TEST_F(GfxPathTest_555, InitialStateCheck_555) {

    EXPECT_EQ(path->getNumSubpaths(), 0);

    EXPECT_FALSE(path->isCurPt());

    EXPECT_FALSE(path->isPath());

}



TEST_F(GfxPathTest_555, MoveToSetsCurrentPoint_555) {

    path->moveTo(10.0, 20.0);

    EXPECT_TRUE(path->isCurPt());

    EXPECT_EQ(path->getLastX(), 10.0);

    EXPECT_EQ(path->getLastY(), 20.0);

}



TEST_F(GfxPathTest_555, LineToAddsSubpath_555) {

    path->moveTo(10.0, 20.0);

    path->lineTo(30.0, 40.0);

    EXPECT_EQ(path->getNumSubpaths(), 1);

}



TEST_F(GfxPathTest_555, CurveToAddsSubpath_555) {

    path->moveTo(10.0, 20.0);

    path->curveTo(30.0, 40.0, 50.0, 60.0, 70.0, 80.0);

    EXPECT_EQ(path->getNumSubpaths(), 1);

}



TEST_F(GfxPathTest_555, CloseCompletesSubpath_555) {

    path->moveTo(10.0, 20.0);

    path->lineTo(30.0, 40.0);

    path->close();

    EXPECT_EQ(path->getNumSubpaths(), 1);

}



TEST_F(GfxPathTest_555, AppendMergesPaths_555) {

    GfxPath* anotherPath = new GfxPath();

    anotherPath->moveTo(10.0, 20.0);

    path->append(anotherPath);

    EXPECT_EQ(path->getNumSubpaths(), 1);

    delete anotherPath;

}



TEST_F(GfxPathTest_555, OffsetMovesAllPoints_555) {

    path->moveTo(10.0, 20.0);

    path->offset(5.0, -5.0);

    EXPECT_EQ(path->getLastX(), 15.0);

    EXPECT_EQ(path->getLastY(), 15.0);

}



TEST_F(GfxPathTest_555, CopyCreatesIndependentInstance_555) {

    path->moveTo(10.0, 20.0);

    GfxPath* copy = path->copy();

    EXPECT_TRUE(copy->isCurPt());

    EXPECT_EQ(copy->getLastX(), 10.0);

    EXPECT_EQ(copy->getLastY(), 20.0);

    delete copy;

}



TEST_F(GfxPathTest_555, BoundaryConditionEmptyPath_555) {

    EXPECT_EQ(path->getNumSubpaths(), 0);

}



TEST_F(GfxPathTest_555, BoundaryConditionNegativeCoordinates_555) {

    path->moveTo(-10.0, -20.0);

    path->lineTo(-30.0, -40.0);

    EXPECT_EQ(path->getLastX(), -30.0);

    EXPECT_EQ(path->getLastY(), -40.0);

}



TEST_F(GfxPathTest_555, BoundaryConditionLargeCoordinates_555) {

    path->moveTo(1e9, 1e9);

    path->lineTo(2e9, 2e9);

    EXPECT_EQ(path->getLastX(), 2e9);

    EXPECT_EQ(path->getLastY(), 2e9);

}

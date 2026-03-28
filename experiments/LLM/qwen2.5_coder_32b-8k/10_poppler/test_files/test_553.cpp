#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/GfxState.h"



class GfxPathTest_553 : public ::testing::Test {

protected:

    GfxPath* path;



    void SetUp() override {

        path = new GfxPath();

    }



    void TearDown() override {

        delete path;

    }

};



TEST_F(GfxPathTest_553, IsPathInitiallyFalse_553) {

    EXPECT_FALSE(path->isPath());

}



TEST_F(GfxPathTest_553, MoveToSetsPathTrue_553) {

    path->moveTo(0.0, 0.0);

    EXPECT_TRUE(path->isPath());

}



TEST_F(GfxPathTest_553, LineToWithoutMoveToDoesNotSetPathTrue_553) {

    path->lineTo(1.0, 1.0);

    EXPECT_FALSE(path->isPath());

}



TEST_F(GfxPathTest_553, CurveToWithoutMoveToDoesNotSetPathTrue_553) {

    path->curveTo(0.0, 0.0, 1.0, 1.0, 2.0, 2.0);

    EXPECT_FALSE(path->isPath());

}



TEST_F(GfxPathTest_553, CloseWithoutMoveToDoesNotSetPathTrue_553) {

    path->close();

    EXPECT_FALSE(path->isPath());

}



TEST_F(GfxPathTest_553, AppendAnotherEmptyPathDoesNothing_553) {

    GfxPath* anotherPath = new GfxPath();

    path->append(anotherPath);

    EXPECT_FALSE(path->isPath());

    delete anotherPath;

}



TEST_F(GfxPathTest_553, AppendNonEmptyPathSetsPathTrue_553) {

    GfxPath* anotherPath = new GfxPath();

    anotherPath->moveTo(0.0, 0.0);

    path->append(anotherPath);

    EXPECT_TRUE(path->isPath());

    delete anotherPath;

}



TEST_F(GfxPathTest_553, OffsetDoesNotChangeIsPathStatusIfInitiallyFalse_553) {

    path->offset(1.0, 1.0);

    EXPECT_FALSE(path->isPath());

}



TEST_F(GfxPathTest_553, OffsetDoesNotChangeIsPathStatusIfInitiallyTrue_553) {

    path->moveTo(0.0, 0.0);

    path->offset(1.0, 1.0);

    EXPECT_TRUE(path->isPath());

}



TEST_F(GfxPathTest_553, CopyOfEmptyPathIsAlsoEmpty_553) {

    GfxPath* copiedPath = path->copy();

    EXPECT_FALSE(copiedPath->isPath());

    delete copiedPath;

}



TEST_F(GfxPathTest_553, CopyOfNonEmptyPathPreservesIsPathStatus_553) {

    path->moveTo(0.0, 0.0);

    GfxPath* copiedPath = path->copy();

    EXPECT_TRUE(copiedPath->isPath());

    delete copiedPath;

}



TEST_F(GfxPathTest_553, GetNumSubpathsInitiallyZero_553) {

    EXPECT_EQ(path->getNumSubpaths(), 0);

}



TEST_F(GfxPathTest_553, MoveToIncreasesNumSubpaths_553) {

    path->moveTo(0.0, 0.0);

    EXPECT_EQ(path->getNumSubpaths(), 1);

}



TEST_F(GfxPathTest_553, LineToAddsPointsWithoutCreatingNewSubpath_553) {

    path->moveTo(0.0, 0.0);

    path->lineTo(1.0, 1.0);

    EXPECT_EQ(path->getNumSubpaths(), 1);

}



TEST_F(GfxPathTest_553, CurveToAddsPointsWithoutCreatingNewSubpath_553) {

    path->moveTo(0.0, 0.0);

    path->curveTo(0.0, 0.0, 1.0, 1.0, 2.0, 2.0);

    EXPECT_EQ(path->getNumSubpaths(), 1);

}



TEST_F(GfxPathTest_553, CloseIncreasesNumSubpathsIfCalledAfterMoveTo_553) {

    path->moveTo(0.0, 0.0);

    path->close();

    EXPECT_EQ(path->getNumSubpaths(), 1);

}



TEST_F(GfxPathTest_553, AppendMergesSubpathsFromAnotherPath_553) {

    GfxPath* anotherPath = new GfxPath();

    anotherPath->moveTo(0.0, 0.0);

    path->moveTo(1.0, 1.0);

    path->append(anotherPath);

    EXPECT_EQ(path->getNumSubpaths(), 2);

    delete anotherPath;

}



TEST_F(GfxPathTest_553, GetLastXInitiallyZero_553) {

    EXPECT_DOUBLE_EQ(path->getLastX(), 0.0);

}



TEST_F(GfxPathTest_553, GetLastYInitiallyZero_553) {

    EXPECT_DOUBLE_EQ(path->getLastY(), 0.0);

}



TEST_F(GfxPathTest_553, MoveToSetsLastXY_553) {

    path->moveTo(1.5, -2.5);

    EXPECT_DOUBLE_EQ(path->getLastX(), 1.5);

    EXPECT_DOUBLE_EQ(path->getLastY(), -2.5);

}



TEST_F(GfxPathTest_553, LineToUpdatesLastXY_553) {

    path->moveTo(0.0, 0.0);

    path->lineTo(1.5, -2.5);

    EXPECT_DOUBLE_EQ(path->getLastX(), 1.5);

    EXPECT_DOUBLE_EQ(path->getLastY(), -2.5);

}



TEST_F(GfxPathTest_553, CurveToUpdateLastXYWithEndPoint_553) {

    path->moveTo(0.0, 0.0);

    path->curveTo(0.0, 0.0, 1.0, 1.0, 2.0, 2.0);

    EXPECT_DOUBLE_EQ(path->getLastX(), 2.0);

    EXPECT_DOUBLE_EQ(path->getLastY(), 2.0);

}



TEST_F(GfxPathTest_553, CloseDoesNotUpdateLastXYIfNoSubpath_553) {

    path->close();

    EXPECT_DOUBLE_EQ(path->getLastX(), 0.0);

    EXPECT_DOUBLE_EQ(path->getLastY(), 0.0);

}



TEST_F(GfxPathTest_553, CloseUpdatesLastXYToStartOfCurrentSubpath_553) {

    path->moveTo(1.5, -2.5);

    path->lineTo(0.0, 0.0);

    path->close();

    EXPECT_DOUBLE_EQ(path->getLastX(), 1.5);

    EXPECT_DOUBLE_EQ(path->getLastY(), -2.5);

}



TEST_F(GfxPathTest_553, GetSubpathReturnsNullForInvalidIndex_553) {

    EXPECT_EQ(path->getSubpath(0), nullptr);

}



TEST_F(GfxPathTest_553, GetSubpathReturnsValidPointerAfterMoveTo_553) {

    path->moveTo(1.0, 1.0);

    EXPECT_NE(path->getSubpath(0), nullptr);

}

#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/GfxState.h"



class GfxPathTest_554 : public ::testing::Test {

protected:

    GfxPath *path;



    void SetUp() override {

        path = new GfxPath();

    }



    void TearDown() override {

        delete path;

    }

};



TEST_F(GfxPathTest_554, InitialNumSubpathsIsZero_554) {

    EXPECT_EQ(path->getNumSubpaths(), 0);

}



TEST_F(GfxPathTest_554, MoveToIncreasesNumSubpaths_554) {

    path->moveTo(1.0, 2.0);

    EXPECT_EQ(path->getNumSubpaths(), 1);

}



TEST_F(GfxPathTest_554, LineToDoesNotIncreaseNumSubpaths_554) {

    path->moveTo(1.0, 2.0);

    path->lineTo(3.0, 4.0);

    EXPECT_EQ(path->getNumSubpaths(), 1);

}



TEST_F(GfxPathTest_554, CurveToDoesNotIncreaseNumSubpaths_554) {

    path->moveTo(1.0, 2.0);

    path->curveTo(3.0, 4.0, 5.0, 6.0, 7.0, 8.0);

    EXPECT_EQ(path->getNumSubpaths(), 1);

}



TEST_F(GfxPathTest_554, CloseIncreasesNumSubpathsIfNotClosed_554) {

    path->moveTo(1.0, 2.0);

    path->lineTo(3.0, 4.0);

    path->close();

    EXPECT_EQ(path->getNumSubpaths(), 1);

}



TEST_F(GfxPathTest_554, CloseDoesNotIncreaseNumSubpathsIfAlreadyClosed_554) {

    path->moveTo(1.0, 2.0);

    path->lineTo(3.0, 4.0);

    path->close();

    path->close();

    EXPECT_EQ(path->getNumSubpaths(), 1);

}



TEST_F(GfxPathTest_554, AppendIncreasesNumSubpaths_554) {

    GfxPath *path2 = new GfxPath();

    path2->moveTo(1.0, 2.0);

    path->append(path2);

    delete path2;

    EXPECT_EQ(path->getNumSubpaths(), 1);

}



TEST_F(GfxPathTest_554, OffsetDoesNotChangeNumSubpaths_554) {

    path->moveTo(1.0, 2.0);

    path->offset(3.0, 4.0);

    EXPECT_EQ(path->getNumSubpaths(), 1);

}



TEST_F(GfxPathTest_554, CopyPreservesNumSubpaths_554) {

    path->moveTo(1.0, 2.0);

    GfxPath *pathCopy = path->copy();

    EXPECT_EQ(pathCopy->getNumSubpaths(), 1);

    delete pathCopy;

}



TEST_F(GfxPathTest_554, IsCurPtInitiallyFalse_554) {

    EXPECT_FALSE(path->isCurPt());

}



TEST_F(GfxPathTest_554, IsCurPtTrueAfterMoveTo_554) {

    path->moveTo(1.0, 2.0);

    EXPECT_TRUE(path->isCurPt());

}



TEST_F(GfxPathTest_554, IsPathInitiallyFalse_554) {

    EXPECT_FALSE(path->isPath());

}



TEST_F(GfxPathTest_554, IsPathTrueAfterMoveTo_554) {

    path->moveTo(1.0, 2.0);

    EXPECT_TRUE(path->isPath());

}



TEST_F(GfxPathTest_554, LastXAndYInitiallyZero_554) {

    EXPECT_DOUBLE_EQ(path->getLastX(), 0.0);

    EXPECT_DOUBLE_EQ(path->getLastY(), 0.0);

}



TEST_F(GfxPathTest_554, LastXAndYUpdatedAfterMoveTo_554) {

    path->moveTo(1.0, 2.0);

    EXPECT_DOUBLE_EQ(path->getLastX(), 1.0);

    EXPECT_DOUBLE_EQ(path->getLastY(), 2.0);

}



TEST_F(GfxPathTest_554, LastXAndYUpdatedAfterLineTo_554) {

    path->moveTo(1.0, 2.0);

    path->lineTo(3.0, 4.0);

    EXPECT_DOUBLE_EQ(path->getLastX(), 3.0);

    EXPECT_DOUBLE_EQ(path->getLastY(), 4.0);

}



TEST_F(GfxPathTest_554, LastXAndYUpdatedAfterCurveTo_554) {

    path->moveTo(1.0, 2.0);

    path->curveTo(3.0, 4.0, 5.0, 6.0, 7.0, 8.0);

    EXPECT_DOUBLE_EQ(path->getLastX(), 7.0);

    EXPECT_DOUBLE_EQ(path->getLastY(), 8.0);

}

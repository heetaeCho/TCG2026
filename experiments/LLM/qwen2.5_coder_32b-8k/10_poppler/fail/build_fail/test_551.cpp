#include <gtest/gtest.h>

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



TEST_F(GfxPathTest_551, CopyCreatesNewInstance_551) {

    GfxPath* copiedPath = path->copy();

    EXPECT_NE(path, copiedPath);

    delete copiedPath;

}



TEST_F(GfxPathTest_551, CopyPreservesInitialValues_551) {

    path->moveTo(10.0, 20.0);

    GfxPath* copiedPath = path->copy();

    EXPECT_EQ(copiedPath->getLastX(), 10.0);

    EXPECT_EQ(copiedPath->getLastY(), 20.0);

    delete copiedPath;

}



TEST_F(GfxPathTest_551, MoveToSetsLastCoordinates_551) {

    path->moveTo(10.0, 20.0);

    EXPECT_EQ(path->getLastX(), 10.0);

    EXPECT_EQ(path->getLastY(), 20.0);

}



TEST_F(GfxPathTest_551, LineToUpdatesLastCoordinates_551) {

    path->moveTo(10.0, 20.0);

    path->lineTo(30.0, 40.0);

    EXPECT_EQ(path->getLastX(), 30.0);

    EXPECT_EQ(path->getLastY(), 40.0);

}



TEST_F(GfxPathTest_551, CurveToUpdatesLastCoordinates_551) {

    path->moveTo(10.0, 20.0);

    path->curveTo(30.0, 40.0, 50.0, 60.0, 70.0, 80.0);

    EXPECT_EQ(path->getLastX(), 70.0);

    EXPECT_EQ(path->getLastY(), 80.0);

}



TEST_F(GfxPathTest_551, CloseDoesNotChangeCoordinates_551) {

    path->moveTo(10.0, 20.0);

    path->close();

    EXPECT_EQ(path->getLastX(), 10.0);

    EXPECT_EQ(path->getLastY(), 20.0);

}



TEST_F(GfxPathTest_551, OffsetUpdatesCoordinates_551) {

    path->moveTo(10.0, 20.0);

    path->offset(5.0, 10.0);

    EXPECT_EQ(path->getLastX(), 15.0);

    EXPECT_EQ(path->getLastY(), 30.0);

}



TEST_F(GfxPathTest_551, AppendMergesSubpaths_551) {

    GfxPath* otherPath = new GfxPath();

    otherPath->moveTo(30.0, 40.0);



    path->moveTo(10.0, 20.0);

    path->append(otherPath);



    EXPECT_EQ(path->getNumSubpaths(), 2);

    delete otherPath;

}



TEST_F(GfxPathTest_551, GetNumSubpathsInitiallyZero_551) {

    EXPECT_EQ(path->getNumSubpaths(), 0);

}



TEST_F(GfxPathTest_551, GetNumSubpathsAfterMoveTo_551) {

    path->moveTo(10.0, 20.0);

    EXPECT_EQ(path->getNumSubpaths(), 1);

}



TEST_F(GfxPathTest_551, GetSubpathReturnsCorrectInstance_551) {

    path->moveTo(10.0, 20.0);

    GfxSubpath* subpath = path->getSubpath(0);

    EXPECT_NE(subpath, nullptr);

}



TEST_F(GfxPathTest_551, GetSubpathThrowsOnInvalidIndex_551) {

    EXPECT_THROW(path->getSubpath(0), std::out_of_range);

}

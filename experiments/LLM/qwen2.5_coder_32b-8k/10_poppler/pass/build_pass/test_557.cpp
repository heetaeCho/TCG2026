#include <gtest/gtest.h>

#include "GfxState.h"



class GfxPathTest_557 : public ::testing::Test {

protected:

    GfxPath *path;



    void SetUp() override {

        path = new GfxPath();

    }



    void TearDown() override {

        delete path;

    }

};



TEST_F(GfxPathTest_557, InitialLastYIsZero_557) {

    EXPECT_EQ(path->getLastY(), 0.0);

}



TEST_F(GfxPathTest_557, MoveToSetsLastY_557) {

    path->moveTo(10.0, 20.0);

    EXPECT_EQ(path->getLastY(), 20.0);

}



TEST_F(GfxPathTest_557, LineToUpdatesLastY_557) {

    path->moveTo(10.0, 20.0);

    path->lineTo(30.0, 40.0);

    EXPECT_EQ(path->getLastY(), 40.0);

}



TEST_F(GfxPathTest_557, CurveToUpdateLastY_557) {

    path->moveTo(10.0, 20.0);

    path->curveTo(15.0, 25.0, 25.0, 35.0, 30.0, 40.0);

    EXPECT_EQ(path->getLastY(), 40.0);

}



TEST_F(GfxPathTest_557, CloseDoesNotChangeLastY_557) {

    path->moveTo(10.0, 20.0);

    path->lineTo(30.0, 40.0);

    double lastYBeforeClose = path->getLastY();

    path->close();

    EXPECT_EQ(path->getLastY(), lastYBeforeClose);

}



TEST_F(GfxPathTest_557, MultipleSubpathsGetLastYFromLatest_557) {

    path->moveTo(10.0, 20.0);

    path->lineTo(30.0, 40.0);

    path->close();

    path->moveTo(50.0, 60.0);

    path->lineTo(70.0, 80.0);

    EXPECT_EQ(path->getLastY(), 80.0);

}



TEST_F(GfxPathTest_557, AppendUpdatesLastYFromAppendedPath_557) {

    GfxPath *otherPath = new GfxPath();

    otherPath->moveTo(10.0, 20.0);

    otherPath->lineTo(30.0, 40.0);

    path->append(otherPath);

    EXPECT_EQ(path->getLastY(), 40.0);

    delete otherPath;

}



TEST_F(GfxPathTest_557, OffsetUpdatesLastY_557) {

    path->moveTo(10.0, 20.0);

    path->lineTo(30.0, 40.0);

    path->offset(0.0, 5.0);

    EXPECT_EQ(path->getLastY(), 45.0);

}

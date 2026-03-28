#include <gtest/gtest.h>

#include "GfxState.h"



class GfxPathTest : public ::testing::Test {

protected:

    GfxPath path;



    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(GfxPathTest_556, LastX_AfterMoveTo_ReturnsCorrectValue_556) {

    double x = 10.0;

    double y = 20.0;

    path.moveTo(x, y);

    EXPECT_EQ(path.getLastX(), x);

}



TEST_F(GfxPathTest_556, LastX_AfterLineTo_ReturnsCorrectValue_556) {

    double xStart = 10.0;

    double yStart = 20.0;

    path.moveTo(xStart, yStart);



    double xEnd = 30.0;

    path.lineTo(xEnd, 20.0);

    EXPECT_EQ(path.getLastX(), xEnd);

}



TEST_F(GfxPathTest_556, LastX_AfterCurveTo_ReturnsCorrectValue_556) {

    double xStart = 10.0;

    double yStart = 20.0;

    path.moveTo(xStart, yStart);



    double xControl1 = 20.0;

    double yControl1 = 30.0;

    double xControl2 = 40.0;

    double yControl2 = 50.0;

    double xEnd = 60.0;

    path.curveTo(xControl1, yControl1, xControl2, yControl2, xEnd, 20.0);

    EXPECT_EQ(path.getLastX(), xEnd);

}



TEST_F(GfxPathTest_556, LastX_WithMultipleSubpaths_ReturnsCorrectValue_556) {

    double xStart1 = 10.0;

    double yStart1 = 20.0;

    path.moveTo(xStart1, yStart1);



    double xEnd1 = 30.0;

    path.lineTo(xEnd1, 20.0);



    double xStart2 = 40.0;

    double yStart2 = 50.0;

    path.moveTo(xStart2, yStart2);



    double xEnd2 = 60.0;

    path.lineTo(xEnd2, 50.0);

    EXPECT_EQ(path.getLastX(), xEnd2);

}



TEST_F(GfxPathTest_556, LastX_WithoutMoveTo_ReturnsZeroByDefault_556) {

    EXPECT_EQ(path.getLastX(), 0.0);

}

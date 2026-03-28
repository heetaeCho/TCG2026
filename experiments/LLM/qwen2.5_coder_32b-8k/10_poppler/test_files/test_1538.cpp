#include <gtest/gtest.h>

#include "SplashPath.h"



class SplashPathTest_1538 : public ::testing::Test {

protected:

    SplashPath* path;



    void SetUp() override {

        path = new SplashPath();

    }



    void TearDown() override {

        delete path;

    }

};



TEST_F(SplashPathTest_1538, OnePointSubpathInitiallyFalse_1538) {

    EXPECT_FALSE(path->onePointSubpath());

}



TEST_F(SplashPathTest_1538, OnePointSubpathTrueAfterMoveToAndLineTo_1538) {

    path->moveTo(0.0, 0.0);

    path->lineTo(1.0, 1.0);

    EXPECT_TRUE(path->onePointSubpath());

}



TEST_F(SplashPathTest_1538, OnePointSubpathFalseAfterMoveToAndCurveTo_1538) {

    path->moveTo(0.0, 0.0);

    path->curveTo(0.25, 0.25, 0.75, 0.75, 1.0, 1.0);

    EXPECT_FALSE(path->onePointSubpath());

}



TEST_F(SplashPathTest_1538, OnePointSubpathFalseAfterMultipleMoveToAndLineTo_1538) {

    path->moveTo(0.0, 0.0);

    path->lineTo(1.0, 1.0);

    path->moveTo(2.0, 2.0);

    EXPECT_FALSE(path->onePointSubpath());

}



TEST_F(SplashPathTest_1538, OnePointSubpathFalseAfterClose_1538) {

    path->moveTo(0.0, 0.0);

    path->lineTo(1.0, 1.0);

    path->close(false);

    EXPECT_FALSE(path->onePointSubpath());

}



TEST_F(SplashPathTest_1538, OnePointSubpathTrueAfterForceClose_1538) {

    path->moveTo(0.0, 0.0);

    path->lineTo(1.0, 1.0);

    path->close(true);

    EXPECT_TRUE(path->onePointSubpath());

}

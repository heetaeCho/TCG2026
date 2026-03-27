#include <gtest/gtest.h>

#include "TestProjects/poppler/splash/SplashPath.h"



class SplashPathTest_1537 : public ::testing::Test {

protected:

    SplashPath path;

};



TEST_F(SplashPathTest_1537, NoCurrentPointInitially_1537) {

    EXPECT_TRUE(path.noCurrentPoint());

}



TEST_F(SplashPathTest_1537, MoveToSetsCurrentPoint_1537) {

    EXPECT_EQ(path.moveTo(0.0, 0.0), splashOk);

    EXPECT_FALSE(path.noCurrentPoint());

}



TEST_F(SplashPathTest_1537, LineToWithoutMoveToFails_1537) {

    EXPECT_TRUE(path.lineTo(0.0, 0.0) != splashOk);

}



TEST_F(SplashPathTest_1537, CurveToWithoutMoveToFails_1537) {

    EXPECT_TRUE(path.curveTo(0.0, 0.0, 0.0, 0.0, 0.0, 0.0) != splashOk);

}



TEST_F(SplashPathTest_1537, CloseWithoutMoveToFails_1537) {

    EXPECT_TRUE(path.close(false) != splashOk);

}



TEST_F(SplashPathTest_1537, GetCurPtAfterMoveTo_1537) {

    SplashCoord x = 0.0, y = 0.0;

    path.moveTo(1.0, 2.0);

    EXPECT_TRUE(path.getCurPt(&x, &y));

    EXPECT_DOUBLE_EQ(x, 1.0);

    EXPECT_DOUBLE_EQ(y, 2.0);

}



TEST_F(SplashPathTest_1537, GetCurPtWithoutMoveToReturnsFalse_1537) {

    SplashCoord x = 0.0, y = 0.0;

    EXPECT_FALSE(path.getCurPt(&x, &y));

}



TEST_F(SplashPathTest_1537, AppendEmptyPathDoesNotChangeState_1537) {

    SplashPath emptyPath;

    path.append(&emptyPath);

    EXPECT_TRUE(path.noCurrentPoint());

}



TEST_F(SplashPathTest_1537, AppendNonEmptyPathUpdatesState_1537) {

    SplashPath anotherPath;

    anotherPath.moveTo(1.0, 2.0);

    path.append(&anotherPath);

    EXPECT_FALSE(path.noCurrentPoint());

}

#include <gtest/gtest.h>

#include "SplashPath.h"



class SplashPathTest : public ::testing::Test {

protected:

    SplashPath path;

};



TEST_F(SplashPathTest_1536, GetPointNormalOperation_1536) {

    double x, y;

    unsigned char f;



    // Assuming the path has at least one point for testing

    path.moveTo(1.0, 2.0);



    path.getPoint(0, &x, &y, &f);

    EXPECT_DOUBLE_EQ(x, 1.0);

    EXPECT_DOUBLE_EQ(y, 2.0);

    EXPECT_EQ(f, splashPathFirst | splashPathLast); // Expecting the first and last flags

}



TEST_F(SplashPathTest_1536, GetPointBoundaryConditionEmptyPath_1536) {

    double x, y;

    unsigned char f;



    // Assuming getPoint on an empty path doesn't crash and sets values to 0/default

    EXPECT_NO_THROW(path.getPoint(0, &x, &y, &f));

    EXPECT_DOUBLE_EQ(x, 0.0);

    EXPECT_DOUBLE_EQ(y, 0.0);

    EXPECT_EQ(f, 0); // Default flag value if no points are present

}



TEST_F(SplashPathTest_1536, GetPointBoundaryConditionIndexOutOfRange_1536) {

    double x, y;

    unsigned char f;



    path.moveTo(1.0, 2.0);



    // Assuming getPoint with index out of range doesn't crash and sets values to 0/default

    EXPECT_NO_THROW(path.getPoint(1, &x, &y, &f));

    EXPECT_DOUBLE_EQ(x, 0.0);

    EXPECT_DOUBLE_EQ(y, 0.0);

    EXPECT_EQ(f, 0); // Default flag value if index is out of range

}



TEST_F(SplashPathTest_1536, GetPointMultiplePoints_1536) {

    double x, y;

    unsigned char f;



    path.moveTo(1.0, 2.0);

    path.lineTo(3.0, 4.0);



    path.getPoint(0, &x, &y, &f);

    EXPECT_DOUBLE_EQ(x, 1.0);

    EXPECT_DOUBLE_EQ(y, 2.0);

    EXPECT_EQ(f, splashPathFirst); // First point flag



    path.getPoint(1, &x, &y, &f);

    EXPECT_DOUBLE_EQ(x, 3.0);

    EXPECT_DOUBLE_EQ(y, 4.0);

    EXPECT_EQ(f, splashPathLast); // Last point flag

}



TEST_F(SplashPathTest_1536, GetPointCurvePoint_1536) {

    double x, y;

    unsigned char f;



    path.moveTo(1.0, 2.0);

    path.curveTo(3.0, 4.0, 5.0, 6.0, 7.0, 8.0);



    path.getPoint(1, &x, &y, &f);

    EXPECT_DOUBLE_EQ(x, 3.0);

    EXPECT_DOUBLE_EQ(y, 4.0);

    EXPECT_EQ(f, splashPathCurve); // Curve point flag



    path.getPoint(2, &x, &y, &f);

    EXPECT_DOUBLE_EQ(x, 5.0);

    EXPECT_DOUBLE_EQ(y, 6.0);

    EXPECT_EQ(f, splashPathCurve); // Curve point flag



    path.getPoint(3, &x, &y, &f);

    EXPECT_DOUBLE_EQ(x, 7.0);

    EXPECT_DOUBLE_EQ(y, 8.0);

    EXPECT_EQ(f, splashPathLast | splashPathCurve); // Last curve point flag

}



TEST_F(SplashPathTest_1536, GetPointAfterClose_1536) {

    double x, y;

    unsigned char f;



    path.moveTo(1.0, 2.0);

    path.lineTo(3.0, 4.0);

    path.close(false);



    path.getPoint(0, &x, &y, &f);

    EXPECT_DOUBLE_EQ(x, 1.0);

    EXPECT_DOUBLE_EQ(y, 2.0);

    EXPECT_EQ(f, splashPathFirst); // First point flag



    path.getPoint(1, &x, &y, &f);

    EXPECT_DOUBLE_EQ(x, 3.0);

    EXPECT_DOUBLE_EQ(y, 4.0);

    EXPECT_EQ(f, splashPathLast | splashPathClosed); // Last and closed point flags

}

#include <gtest/gtest.h>

#include <gmock/gmock.h>



extern void radialCorner1(double x, double y, double &b, double dx, double dy, double cr, double dr, double mindr, bool &valid, double *range);



class RadialCornerTest_1890 : public ::testing::Test {

protected:

    double b;

    bool valid;

    double range[2];

};



TEST_F(RadialCornerTest_1890, NormalOperation_1890) {

    double x = 1.0, y = 1.0, dx = 1.0, dy = 1.0, cr = 1.0, dr = 1.0, mindr = 0.5;

    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);

    EXPECT_TRUE(valid);

}



TEST_F(RadialCornerTest_1890, BoundaryCondition_xZero_1890) {

    double x = 0.0, y = 1.0, dx = 1.0, dy = 1.0, cr = 1.0, dr = 1.0, mindr = 0.5;

    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);

    EXPECT_TRUE(valid);

}



TEST_F(RadialCornerTest_1890, BoundaryCondition_yZero_1890) {

    double x = 1.0, y = 0.0, dx = 1.0, dy = 1.0, cr = 1.0, dr = 1.0, mindr = 0.5;

    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);

    EXPECT_TRUE(valid);

}



TEST_F(RadialCornerTest_1890, BoundaryCondition_bZero_1890) {

    double x = 0.0, y = 0.0, dx = 0.0, dy = 0.0, cr = 1.0, dr = 1.0, mindr = 0.5;

    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);

    EXPECT_FALSE(valid);

}



TEST_F(RadialCornerTest_1890, ExceptionalCase_mindrGreaterThanTcornerDr_1890) {

    double x = 1.0, y = 1.0, dx = -1.0, dy = -1.0, cr = 2.0, dr = 1.0, mindr = 5.0;

    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);

    EXPECT_FALSE(valid);

}



TEST_F(RadialCornerTest_1890, BoundaryCondition_tcornerDrEqualsMindr_1890) {

    double x = 1.0, y = 1.0, dx = -1.0, dy = -1.0, cr = 2.0, dr = 1.0, mindr = 0.5;

    radialCorner1(x, y, b, dx, dy, cr, dr, mindr, valid, range);

    EXPECT_TRUE(valid);

}

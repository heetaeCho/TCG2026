#include <gtest/gtest.h>

#include "SplashPath.h"

#include "SplashFTFont.cc"



class GlyphPathTest_2610 : public ::testing::Test {

protected:

    void SetUp() override {

        path = new SplashPath();

        fontPath.path = path;

        fontPath.textScale = 1.0;  // Default scale

    }



    void TearDown() override {

        delete path;

    }



    SplashFTFontPath fontPath;

    SplashPath* path;

};



TEST_F(GlyphPathTest_2610, CubicToAddsCurve_2610) {

    FT_Vector ctrl1 = {64, 0};

    FT_Vector ctrl2 = {128, 128};

    FT_Vector pt = {192, 64};



    glyphPathCubicTo(&ctrl1, &ctrl2, &pt, &fontPath);



    int length = path->getLength();

    ASSERT_EQ(length, 3); // One moveTo and two curve points



    double x, y;

    unsigned char f;



    path->getPoint(0, &x, &y, &f);

    EXPECT_DOUBLE_EQ(x, 1.0); // Starting point should be (0, 0) scaled by textScale

    EXPECT_DOUBLE_EQ(y, 0.0);

    EXPECT_TRUE(f & splashPathFirst);



    path->getPoint(1, &x, &y, &f);

    EXPECT_DOUBLE_EQ(x, 1.0);

    EXPECT_DOUBLE_EQ(y, 0.0);

    EXPECT_TRUE(f & splashPathCurve);



    path->getPoint(2, &x, &y, &f);

    EXPECT_DOUBLE_EQ(x, 3.0);

    EXPECT_DOUBLE_EQ(y, 1.0);

    EXPECT_TRUE(f & splashPathCurve);

}



TEST_F(GlyphPathTest_2610, CubicToWithNonDefaultScale_2610) {

    FT_Vector ctrl1 = {64, 0};

    FT_Vector ctrl2 = {128, 128};

    FT_Vector pt = {192, 64};



    fontPath.textScale = 2.0;  // Change the scale



    glyphPathCubicTo(&ctrl1, &ctrl2, &pt, &fontPath);



    int length = path->getLength();

    ASSERT_EQ(length, 3); // One moveTo and two curve points



    double x, y;

    unsigned char f;



    path->getPoint(0, &x, &y, &f);

    EXPECT_DOUBLE_EQ(x, 2.0); // Starting point should be (0, 0) scaled by textScale

    EXPECT_DOUBLE_EQ(y, 0.0);

    EXPECT_TRUE(f & splashPathFirst);



    path->getPoint(1, &x, &y, &f);

    EXPECT_DOUBLE_EQ(x, 2.0);

    EXPECT_DOUBLE_EQ(y, 0.0);

    EXPECT_TRUE(f & splashPathCurve);



    path->getPoint(2, &x, &y, &f);

    EXPECT_DOUBLE_EQ(x, 6.0);

    EXPECT_DOUBLE_EQ(y, 2.0);

    EXPECT_TRUE(f & splashPathCurve);

}



TEST_F(GlyphPathTest_2610, CubicToWithZeroScale_2610) {

    FT_Vector ctrl1 = {64, 0};

    FT_Vector ctrl2 = {128, 128};

    FT_Vector pt = {192, 64};



    fontPath.textScale = 0.0;  // Zero scale



    glyphPathCubicTo(&ctrl1, &ctrl2, &pt, &fontPath);



    int length = path->getLength();

    ASSERT_EQ(length, 3); // One moveTo and two curve points



    double x, y;

    unsigned char f;



    path->getPoint(0, &x, &y, &f);

    EXPECT_DOUBLE_EQ(x, 0.0); // Starting point should be (0, 0) scaled by textScale

    EXPECT_DOUBLE_EQ(y, 0.0);

    EXPECT_TRUE(f & splashPathFirst);



    path->getPoint(1, &x, &y, &f);

    EXPECT_DOUBLE_EQ(x, 0.0);

    EXPECT_DOUBLE_EQ(y, 0.0);

    EXPECT_TRUE(f & splashPathCurve);



    path->getPoint(2, &x, &y, &f);

    EXPECT_DOUBLE_EQ(x, 0.0);

    EXPECT_DOUBLE_EQ(y, 0.0);

    EXPECT_TRUE(f & splashPathCurve);

}



TEST_F(GlyphPathTest_2610, CubicToWithNegativeScale_2610) {

    FT_Vector ctrl1 = {64, 0};

    FT_Vector ctrl2 = {128, 128};

    FT_Vector pt = {192, 64};



    fontPath.textScale = -1.0;  // Negative scale



    glyphPathCubicTo(&ctrl1, &ctrl2, &pt, &fontPath);



    int length = path->getLength();

    ASSERT_EQ(length, 3); // One moveTo and two curve points



    double x, y;

    unsigned char f;



    path->getPoint(0, &x, &y, &f);

    EXPECT_DOUBLE_EQ(x, -1.0); // Starting point should be (0, 0) scaled by textScale

    EXPECT_DOUBLE_EQ(y, 0.0);

    EXPECT_TRUE(f & splashPathFirst);



    path->getPoint(1, &x, &y, &f);

    EXPECT_DOUBLE_EQ(x, -1.0);

    EXPECT_DOUBLE_EQ(y, 0.0);

    EXPECT_TRUE(f & splashPathCurve);



    path->getPoint(2, &x, &y, &f);

    EXPECT_DOUBLE_EQ(x, -3.0);

    EXPECT_DOUBLE_EQ(y, -1.0);

    EXPECT_TRUE(f & splashPathCurve);

}

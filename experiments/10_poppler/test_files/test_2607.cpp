#include <gtest/gtest.h>

#include "SplashFTFont.cc"

#include "SplashPath.h"



class GlyphPathTest_2607 : public ::testing::Test {

protected:

    void SetUp() override {

        fontPath.path = new SplashPath();

        fontPath.textScale = 1.0;

    }



    void TearDown() override {

        delete fontPath.path;

    }



    SplashFTFontPath fontPath;

};



TEST_F(GlyphPathTest_2607, MoveToUpdatesPathCoordinates_2607) {

    FT_Vector pt;

    pt.x = 128; // 2.0 after scaling

    pt.y = 64;  // 1.0 after scaling



    glyphPathMoveTo(&pt, &fontPath);



    double x, y;

    unsigned char flag;

    fontPath.path->getPoint(0, &x, &y, &flag);

    

    EXPECT_EQ(x, 2.0);

    EXPECT_EQ(y, 1.0);

    EXPECT_EQ(flag, splashPathFirst);

}



TEST_F(GlyphPathTest_2607, MoveToWithNonZeroTextScaleScalesCoordinates_2607) {

    fontPath.textScale = 2.0;

    FT_Vector pt;

    pt.x = 128; // 4.0 after scaling

    pt.y = 64;  // 2.0 after scaling



    glyphPathMoveTo(&pt, &fontPath);



    double x, y;

    unsigned char flag;

    fontPath.path->getPoint(0, &x, &y, &flag);

    

    EXPECT_EQ(x, 4.0);

    EXPECT_EQ(y, 2.0);

    EXPECT_EQ(flag, splashPathFirst);

}



TEST_F(GlyphPathTest_2607, MoveToWithNeedCloseClosesPreviousSubpath_2607) {

    fontPath.path->moveTo(1.0, 1.0);

    fontPath.path->lineTo(2.0, 2.0);

    fontPath.needClose = true;



    FT_Vector pt;

    pt.x = 128; // 2.0 after scaling

    pt.y = 64;  // 1.0 after scaling



    glyphPathMoveTo(&pt, &fontPath);



    unsigned char flag;

    fontPath.path->getPoint(1, nullptr, nullptr, &flag);

    

    EXPECT_EQ(flag, splashPathClosed);

}



TEST_F(GlyphPathTest_2607, MoveToWithNoPreviousPointsDoesNotCloseSubpath_2607) {

    FT_Vector pt;

    pt.x = 128; // 2.0 after scaling

    pt.y = 64;  // 1.0 after scaling



    glyphPathMoveTo(&pt, &fontPath);



    EXPECT_EQ(fontPath.path->getLength(), 1);

}



TEST_F(GlyphPathTest_2607, MoveToWithNegativeCoordinatesHandlesCorrectly_2607) {

    FT_Vector pt;

    pt.x = -128; // -2.0 after scaling

    pt.y = -64;  // -1.0 after scaling



    glyphPathMoveTo(&pt, &fontPath);



    double x, y;

    unsigned char flag;

    fontPath.path->getPoint(0, &x, &y, &flag);

    

    EXPECT_EQ(x, -2.0);

    EXPECT_EQ(y, -1.0);

    EXPECT_EQ(flag, splashPathFirst);

}

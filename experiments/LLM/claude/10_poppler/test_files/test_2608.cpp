#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "splash/SplashPath.h"
#include "splash/SplashTypes.h"

// Replicate the struct used internally
struct SplashFTFontPath {
    SplashPath *path;
    SplashCoord textScale;
    bool needClose;
};

// Declare the static function we're testing. Since it's static in the .cc file,
// we need to either include it or redefine the signature. We'll use a workaround
// by including the source or declaring it extern if possible.
// Since glyphPathLineTo is static, we replicate its signature and test via 
// the FT_Outline_Funcs mechanism or by directly calling it.

// We need to access the static function. One approach: include the .cc file
// to get access to the static function.
// This is a common testing pattern for static functions.
#include "splash/SplashFTFont.cc"

class GlyphPathLineToTest_2608 : public ::testing::Test {
protected:
    void SetUp() override {
        path = new SplashPath();
        // Must have a current point for lineTo to work
        path->moveTo(0.0, 0.0);
        
        ftFontPath.path = path;
        ftFontPath.textScale = 1.0;
        ftFontPath.needClose = false;
    }

    void TearDown() override {
        delete path;
    }

    SplashPath *path;
    SplashFTFontPath ftFontPath;
};

TEST_F(GlyphPathLineToTest_2608, ReturnsZero_2608) {
    FT_Vector pt;
    pt.x = 64;
    pt.y = 64;
    
    int result = glyphPathLineTo(&pt, &ftFontPath);
    EXPECT_EQ(result, 0);
}

TEST_F(GlyphPathLineToTest_2608, AddsPointToPath_2608) {
    FT_Vector pt;
    pt.x = 128;  // 128/64 * 1.0 = 2.0
    pt.y = 256;  // 256/64 * 1.0 = 4.0
    
    int initialLength = path->getLength();
    
    glyphPathLineTo(&pt, &ftFontPath);
    
    EXPECT_EQ(path->getLength(), initialLength + 1);
}

TEST_F(GlyphPathLineToTest_2608, CorrectCoordinatesWithTextScaleOne_2608) {
    FT_Vector pt;
    pt.x = 128;  // 128/64 * 1.0 = 2.0
    pt.y = 256;  // 256/64 * 1.0 = 4.0
    
    glyphPathLineTo(&pt, &ftFontPath);
    
    int len = path->getLength();
    double x, y;
    unsigned char f;
    path->getPoint(len - 1, &x, &y, &f);
    
    EXPECT_DOUBLE_EQ(x, 2.0);
    EXPECT_DOUBLE_EQ(y, 4.0);
}

TEST_F(GlyphPathLineToTest_2608, CorrectCoordinatesWithTextScaleTwo_2608) {
    ftFontPath.textScale = 2.0;
    
    FT_Vector pt;
    pt.x = 128;  // 128 * 2.0 / 64 = 4.0
    pt.y = 256;  // 256 * 2.0 / 64 = 8.0
    
    glyphPathLineTo(&pt, &ftFontPath);
    
    int len = path->getLength();
    double x, y;
    unsigned char f;
    path->getPoint(len - 1, &x, &y, &f);
    
    EXPECT_DOUBLE_EQ(x, 4.0);
    EXPECT_DOUBLE_EQ(y, 8.0);
}

TEST_F(GlyphPathLineToTest_2608, SetsNeedCloseTrue_2608) {
    FT_Vector pt;
    pt.x = 64;
    pt.y = 64;
    
    EXPECT_FALSE(ftFontPath.needClose);
    
    glyphPathLineTo(&pt, &ftFontPath);
    
    EXPECT_TRUE(ftFontPath.needClose);
}

TEST_F(GlyphPathLineToTest_2608, ZeroCoordinates_2608) {
    FT_Vector pt;
    pt.x = 0;
    pt.y = 0;
    
    glyphPathLineTo(&pt, &ftFontPath);
    
    int len = path->getLength();
    double x, y;
    unsigned char f;
    path->getPoint(len - 1, &x, &y, &f);
    
    EXPECT_DOUBLE_EQ(x, 0.0);
    EXPECT_DOUBLE_EQ(y, 0.0);
}

TEST_F(GlyphPathLineToTest_2608, NegativeCoordinates_2608) {
    FT_Vector pt;
    pt.x = -128;  // -128/64 * 1.0 = -2.0
    pt.y = -256;  // -256/64 * 1.0 = -4.0
    
    glyphPathLineTo(&pt, &ftFontPath);
    
    int len = path->getLength();
    double x, y;
    unsigned char f;
    path->getPoint(len - 1, &x, &y, &f);
    
    EXPECT_DOUBLE_EQ(x, -2.0);
    EXPECT_DOUBLE_EQ(y, -4.0);
}

TEST_F(GlyphPathLineToTest_2608, FractionalResult_2608) {
    FT_Vector pt;
    pt.x = 32;  // 32/64 * 1.0 = 0.5
    pt.y = 16;  // 16/64 * 1.0 = 0.25
    
    glyphPathLineTo(&pt, &ftFontPath);
    
    int len = path->getLength();
    double x, y;
    unsigned char f;
    path->getPoint(len - 1, &x, &y, &f);
    
    EXPECT_DOUBLE_EQ(x, 0.5);
    EXPECT_DOUBLE_EQ(y, 0.25);
}

TEST_F(GlyphPathLineToTest_2608, MultipleLineToCalls_2608) {
    FT_Vector pt1, pt2, pt3;
    pt1.x = 64;  pt1.y = 64;
    pt2.x = 128; pt2.y = 128;
    pt3.x = 192; pt3.y = 192;
    
    int initialLength = path->getLength();
    
    glyphPathLineTo(&pt1, &ftFontPath);
    glyphPathLineTo(&pt2, &ftFontPath);
    glyphPathLineTo(&pt3, &ftFontPath);
    
    EXPECT_EQ(path->getLength(), initialLength + 3);
    
    double x, y;
    unsigned char f;
    
    path->getPoint(initialLength, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 1.0);
    EXPECT_DOUBLE_EQ(y, 1.0);
    
    path->getPoint(initialLength + 1, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 2.0);
    EXPECT_DOUBLE_EQ(y, 2.0);
    
    path->getPoint(initialLength + 2, &x, &y, &f);
    EXPECT_DOUBLE_EQ(x, 3.0);
    EXPECT_DOUBLE_EQ(y, 3.0);
}

TEST_F(GlyphPathLineToTest_2608, LargeCoordinates_2608) {
    FT_Vector pt;
    pt.x = 640000;  // 640000/64 * 1.0 = 10000.0
    pt.y = 640000;
    
    glyphPathLineTo(&pt, &ftFontPath);
    
    int len = path->getLength();
    double x, y;
    unsigned char f;
    path->getPoint(len - 1, &x, &y, &f);
    
    EXPECT_DOUBLE_EQ(x, 10000.0);
    EXPECT_DOUBLE_EQ(y, 10000.0);
}

TEST_F(GlyphPathLineToTest_2608, TextScaleZero_2608) {
    ftFontPath.textScale = 0.0;
    
    FT_Vector pt;
    pt.x = 128;
    pt.y = 256;
    
    glyphPathLineTo(&pt, &ftFontPath);
    
    int len = path->getLength();
    double x, y;
    unsigned char f;
    path->getPoint(len - 1, &x, &y, &f);
    
    EXPECT_DOUBLE_EQ(x, 0.0);
    EXPECT_DOUBLE_EQ(y, 0.0);
}

TEST_F(GlyphPathLineToTest_2608, NeedCloseRemainsTrue_2608) {
    ftFontPath.needClose = true;
    
    FT_Vector pt;
    pt.x = 64;
    pt.y = 64;
    
    glyphPathLineTo(&pt, &ftFontPath);
    
    EXPECT_TRUE(ftFontPath.needClose);
}

TEST_F(GlyphPathLineToTest_2608, SmallTextScale_2608) {
    ftFontPath.textScale = 0.5;
    
    FT_Vector pt;
    pt.x = 128;  // 128 * 0.5 / 64 = 1.0
    pt.y = 256;  // 256 * 0.5 / 64 = 2.0
    
    glyphPathLineTo(&pt, &ftFontPath);
    
    int len = path->getLength();
    double x, y;
    unsigned char f;
    path->getPoint(len - 1, &x, &y, &f);
    
    EXPECT_DOUBLE_EQ(x, 1.0);
    EXPECT_DOUBLE_EQ(y, 2.0);
}

TEST_F(GlyphPathLineToTest_2608, NegativeTextScale_2608) {
    ftFontPath.textScale = -1.0;
    
    FT_Vector pt;
    pt.x = 128;  // 128 * (-1.0) / 64 = -2.0
    pt.y = 256;  // 256 * (-1.0) / 64 = -4.0
    
    glyphPathLineTo(&pt, &ftFontPath);
    
    int len = path->getLength();
    double x, y;
    unsigned char f;
    path->getPoint(len - 1, &x, &y, &f);
    
    EXPECT_DOUBLE_EQ(x, -2.0);
    EXPECT_DOUBLE_EQ(y, -4.0);
}

TEST_F(GlyphPathLineToTest_2608, UnitCoordinate_2608) {
    FT_Vector pt;
    pt.x = 1;   // 1/64 * 1.0 = 0.015625
    pt.y = 1;
    
    glyphPathLineTo(&pt, &ftFontPath);
    
    int len = path->getLength();
    double x, y;
    unsigned char f;
    path->getPoint(len - 1, &x, &y, &f);
    
    EXPECT_DOUBLE_EQ(x, 1.0 / 64.0);
    EXPECT_DOUBLE_EQ(y, 1.0 / 64.0);
}

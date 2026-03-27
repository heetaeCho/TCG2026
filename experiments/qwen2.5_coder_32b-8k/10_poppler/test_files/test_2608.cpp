#include <gtest/gtest.h>

#include "SplashPath.h"

#include "SplashFTFont.cc"



class GlyphPathLineToTest_2608 : public ::testing::Test {

protected:

    SplashFTFontPath fontPath;

    SplashPath path;

    

    void SetUp() override {

        fontPath.path = &path;

        fontPath.textScale = 1.0; // Default scale

    }

};



TEST_F(GlyphPathLineToTest_2608, NormalOperation_2608) {

    FT_Vector pt = {64, 64}; // This should translate to (1,1) with textScale = 1.0

    int result = glyphPathLineTo(&pt, &fontPath);

    

    EXPECT_EQ(result, 0); // Should return 0 on success

    

    double x, y;

    unsigned char flags;

    path.getPoint(0, &x, &y, &flags);

    

    EXPECT_DOUBLE_EQ(x, 1.0);

    EXPECT_DOUBLE_EQ(y, 1.0);

    EXPECT_EQ(flags, splashPathLast | splashPathClosed); // lineTo marks the end of a subpath

}



TEST_F(GlyphPathLineToTest_2608, BoundaryConditions_ZeroCoordinates_2608) {

    FT_Vector pt = {0, 0}; // Should translate to (0,0)

    int result = glyphPathLineTo(&pt, &fontPath);

    

    EXPECT_EQ(result, 0); // Should return 0 on success

    

    double x, y;

    unsigned char flags;

    path.getPoint(0, &x, &y, &flags);

    

    EXPECT_DOUBLE_EQ(x, 0.0);

    EXPECT_DOUBLE_EQ(y, 0.0);

    EXPECT_EQ(flags, splashPathLast | splashPathClosed); // lineTo marks the end of a subpath

}



TEST_F(GlyphPathLineToTest_2608, BoundaryConditions_MaxCoordinates_2608) {

    FT_Vector pt = {INT_MAX, INT_MAX}; // Very large value, should scale down to reasonable values

    int result = glyphPathLineTo(&pt, &fontPath);

    

    EXPECT_EQ(result, 0); // Should return 0 on success

    

    double x, y;

    unsigned char flags;

    path.getPoint(0, &x, &y, &flags);

    

    EXPECT_TRUE(x < INT_MAX && y < INT_MAX); // Scaled down

    EXPECT_EQ(flags, splashPathLast | splashPathClosed); // lineTo marks the end of a subpath

}



TEST_F(GlyphPathLineToTest_2608, BoundaryConditions_NegativeCoordinates_2608) {

    FT_Vector pt = {-64, -64}; // This should translate to (-1,-1)

    int result = glyphPathLineTo(&pt, &fontPath);

    

    EXPECT_EQ(result, 0); // Should return 0 on success

    

    double x, y;

    unsigned char flags;

    path.getPoint(0, &x, &y, &flags);

    

    EXPECT_DOUBLE_EQ(x, -1.0);

    EXPECT_DOUBLE_EQ(y, -1.0);

    EXPECT_EQ(flags, splashPathLast | splashPathClosed); // lineTo marks the end of a subpath

}



TEST_F(GlyphPathLineToTest_2608, NeedCloseFlag_2608) {

    FT_Vector pt = {64, 64};

    int result = glyphPathLineTo(&pt, &fontPath);

    

    EXPECT_EQ(result, 0); // Should return 0 on success

    

    EXPECT_TRUE(fontPath.needClose);

}

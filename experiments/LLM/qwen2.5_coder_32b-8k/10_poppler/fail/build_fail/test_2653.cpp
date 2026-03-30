#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mock GooString if necessary, but for this function, we can treat it as a black box.

extern "C" {

    extern bool parseJpegOptions();

    extern GooString jpegOpt;

    extern int jpegQuality;

    extern bool jpegProgressive;

    extern bool jpegOptimize;

}



TEST(parseJpegOptionsTest_2653, ValidQuality_2653) {

    jpegOpt = "quality=50";

    EXPECT_TRUE(parseJpegOptions());

    EXPECT_EQ(jpegQuality, 50);

}



TEST(parseJpegOptionsTest_2653, QualityBelowRange_2653) {

    jpegOpt = "quality=-1";

    EXPECT_FALSE(parseJpegOptions());

}



TEST(parseJpegOptionsTest_2653, QualityAboveRange_2653) {

    jpegOpt = "quality=101";

    EXPECT_FALSE(parseJpegOptions());

}



TEST(parseJpegOptionsTest_2653, ValidProgressiveY_2653) {

    jpegOpt = "progressive=y";

    EXPECT_TRUE(parseJpegOptions());

    EXPECT_TRUE(jpegProgressive);

}



TEST(parseJpegOptionsTest_2653, ValidProgressiveN_2653) {

    jpegOpt = "progressive=n";

    EXPECT_TRUE(parseJpegOptions());

    EXPECT_FALSE(jpegProgressive);

}



TEST(parseJpegOptionsTest_2653, InvalidProgressiveValue_2653) {

    jpegOpt = "progressive=invalid";

    EXPECT_FALSE(parseJpegOptions());

}



TEST(parseJpegOptionsTest_2653, ValidOptimizeY_2653) {

    jpegOpt = "optimize=y";

    EXPECT_TRUE(parseJpegOptions());

    EXPECT_TRUE(jpegOptimize);

}



TEST(parseJpegOptionsTest_2653, ValidOptimiseY_2653) {

    jpegOpt = "optimise=y";

    EXPECT_TRUE(parseJpegOptions());

    EXPECT_TRUE(jpegOptimize);

}



TEST(parseJpegOptionsTest_2653, ValidOptimizeN_2653) {

    jpegOpt = "optimize=n";

    EXPECT_TRUE(parseJpegOptions());

    EXPECT_FALSE(jpegOptimize);

}



TEST(parseJpegOptionsTest_2653, InvalidOptimizeValue_2653) {

    jpegOpt = "optimize=invalid";

    EXPECT_FALSE(parseJpegOptions());

}



TEST(parseJpegOptionsTest_2653, MultipleValidOptions_2653) {

    jpegOpt = "quality=75,progressive=y,optimize=n";

    EXPECT_TRUE(parseJpegOptions());

    EXPECT_EQ(jpegQuality, 75);

    EXPECT_TRUE(jpegProgressive);

    EXPECT_FALSE(jpegOptimize);

}



TEST(parseJpegOptionsTest_2653, UnknownOption_2653) {

    jpegOpt = "unknown=option";

    EXPECT_FALSE(parseJpegOptions());

}



TEST(parseJpegOptionsTest_2653, EmptyString_2653) {

    jpegOpt = "";

    EXPECT_TRUE(parseJpegOptions());

}

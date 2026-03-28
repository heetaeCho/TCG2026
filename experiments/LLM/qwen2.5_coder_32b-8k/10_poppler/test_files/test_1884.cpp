#include <gtest/gtest.h>

#include "GfxState.cc" // Assuming GfxState.cc contains the function definition



class CMSColorSpaceTypeTest_1884 : public ::testing::Test {

protected:

    // You can set up any common state or mock objects here if needed.

};



TEST_F(CMSColorSpaceTypeTest_1884, XYZ_ReturnsPT_XYZ_1884) {

    EXPECT_EQ(getCMSColorSpaceType(cmsSigXYZData), PT_XYZ);

}



TEST_F(CMSColorSpaceTypeTest_1884, Lab_ReturnsPT_Lab_1884) {

    EXPECT_EQ(getCMSColorSpaceType(cmsSigLabData), PT_Lab);

}



TEST_F(CMSColorSpaceTypeTest_1884, Luv_ReturnsPT_YUV_1884) {

    EXPECT_EQ(getCMSColorSpaceType(cmsSigLuvData), PT_YUV);

}



TEST_F(CMSColorSpaceTypeTest_1884, YCbCr_ReturnsPT_YCbCr_1884) {

    EXPECT_EQ(getCMSColorSpaceType(cmsSigYCbCrData), PT_YCbCr);

}



TEST_F(CMSColorSpaceTypeTest_1884, Yxy_ReturnsPT_Yxy_1884) {

    EXPECT_EQ(getCMSColorSpaceType(cmsSigYxyData), PT_Yxy);

}



TEST_F(CMSColorSpaceTypeTest_1884, Rgb_ReturnsPT_RGB_1884) {

    EXPECT_EQ(getCMSColorSpaceType(cmsSigRgbData), PT_RGB);

}



TEST_F(CMSColorSpaceTypeTest_1884, Gray_ReturnsPT_GRAY_1884) {

    EXPECT_EQ(getCMSColorSpaceType(cmsSigGrayData), PT_GRAY);

}



TEST_F(CMSColorSpaceTypeTest_1884, Hsv_ReturnsPT_HSV_1884) {

    EXPECT_EQ(getCMSColorSpaceType(cmsSigHsvData), PT_HSV);

}



TEST_F(CMSColorSpaceTypeTest_1884, Hls_ReturnsPT_HLS_1884) {

    EXPECT_EQ(getCMSColorSpaceType(cmsSigHlsData), PT_HLS);

}



TEST_F(CMSColorSpaceTypeTest_1884, Cmyk_ReturnsPT_CMYK_1884) {

    EXPECT_EQ(getCMSColorSpaceType(cmsSigCmykData), PT_CMYK);

}



TEST_F(CMSColorSpaceTypeTest_1884, Cmy_ReturnsPT_CMY_1884) {

    EXPECT_EQ(getCMSColorSpaceType(cmsSigCmyData), PT_CMY);

}



TEST_F(CMSColorSpaceTypeTest_1884, MultiColor_ReturnsDefaultRGB_1884) {

    EXPECT_EQ(getCMSColorSpaceType(cmsSig2colorData), PT_RGB);

    EXPECT_EQ(getCMSColorSpaceType(cmsSig3colorData), PT_RGB);

    EXPECT_EQ(getCMSColorSpaceType(cmsSig4colorData), PT_RGB);

    EXPECT_EQ(getCMSColorSpaceType(cmsSig5colorData), PT_RGB);

    EXPECT_EQ(getCMSColorSpaceType(cmsSig6colorData), PT_RGB);

    EXPECT_EQ(getCMSColorSpaceType(cmsSig7colorData), PT_RGB);

    EXPECT_EQ(getCMSColorSpaceType(cmsSig8colorData), PT_RGB);

    EXPECT_EQ(getCMSColorSpaceType(cmsSig9colorData), PT_RGB);

    EXPECT_EQ(getCMSColorSpaceType(cmsSig10colorData), PT_RGB);

    EXPECT_EQ(getCMSColorSpaceType(cmsSig11colorData), PT_RGB);

    EXPECT_EQ(getCMSColorSpaceType(cmsSig12colorData), PT_RGB);

    EXPECT_EQ(getCMSColorSpaceType(cmsSig13colorData), PT_RGB);

    EXPECT_EQ(getCMSColorSpaceType(cmsSig14colorData), PT_RGB);

    EXPECT_EQ(getCMSColorSpaceType(cmsSig15colorData), PT_RGB);

}



TEST_F(CMSColorSpaceTypeTest_1884, Default_ReturnsDefaultRGB_1884) {

    EXPECT_EQ(getCMSColorSpaceType(static_cast<cmsColorSpaceSignature>(0xFFFFFFFF)), PT_RGB); // Example of an undefined signature

}

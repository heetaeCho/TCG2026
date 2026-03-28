#include <gtest/gtest.h>
#include <lcms2.h>

// Declaration of the function under test
unsigned int getCMSColorSpaceType(cmsColorSpaceSignature cs);

// Test normal operation for each known color space signature

TEST(GetCMSColorSpaceTypeTest_1884, XYZData_ReturnsXYZ_1884) {
    EXPECT_EQ(getCMSColorSpaceType(cmsSigXYZData), PT_XYZ);
}

TEST(GetCMSColorSpaceTypeTest_1884, LabData_ReturnsLab_1884) {
    EXPECT_EQ(getCMSColorSpaceType(cmsSigLabData), PT_Lab);
}

TEST(GetCMSColorSpaceTypeTest_1884, LuvData_ReturnsYUV_1884) {
    EXPECT_EQ(getCMSColorSpaceType(cmsSigLuvData), PT_YUV);
}

TEST(GetCMSColorSpaceTypeTest_1884, YCbCrData_ReturnsYCbCr_1884) {
    EXPECT_EQ(getCMSColorSpaceType(cmsSigYCbCrData), PT_YCbCr);
}

TEST(GetCMSColorSpaceTypeTest_1884, YxyData_ReturnsYxy_1884) {
    EXPECT_EQ(getCMSColorSpaceType(cmsSigYxyData), PT_Yxy);
}

TEST(GetCMSColorSpaceTypeTest_1884, RgbData_ReturnsRGB_1884) {
    EXPECT_EQ(getCMSColorSpaceType(cmsSigRgbData), PT_RGB);
}

TEST(GetCMSColorSpaceTypeTest_1884, GrayData_ReturnsGRAY_1884) {
    EXPECT_EQ(getCMSColorSpaceType(cmsSigGrayData), PT_GRAY);
}

TEST(GetCMSColorSpaceTypeTest_1884, HsvData_ReturnsHSV_1884) {
    EXPECT_EQ(getCMSColorSpaceType(cmsSigHsvData), PT_HSV);
}

TEST(GetCMSColorSpaceTypeTest_1884, HlsData_ReturnsHLS_1884) {
    EXPECT_EQ(getCMSColorSpaceType(cmsSigHlsData), PT_HLS);
}

TEST(GetCMSColorSpaceTypeTest_1884, CmykData_ReturnsCMYK_1884) {
    EXPECT_EQ(getCMSColorSpaceType(cmsSigCmykData), PT_CMYK);
}

TEST(GetCMSColorSpaceTypeTest_1884, CmyData_ReturnsCMY_1884) {
    EXPECT_EQ(getCMSColorSpaceType(cmsSigCmyData), PT_CMY);
}

// Test multi-color data signatures that fall through to default (return PT_RGB)

TEST(GetCMSColorSpaceTypeTest_1884, Sig2colorData_ReturnsRGB_1884) {
    EXPECT_EQ(getCMSColorSpaceType(cmsSig2colorData), PT_RGB);
}

TEST(GetCMSColorSpaceTypeTest_1884, Sig3colorData_ReturnsRGB_1884) {
    EXPECT_EQ(getCMSColorSpaceType(cmsSig3colorData), PT_RGB);
}

TEST(GetCMSColorSpaceTypeTest_1884, Sig4colorData_ReturnsRGB_1884) {
    EXPECT_EQ(getCMSColorSpaceType(cmsSig4colorData), PT_RGB);
}

TEST(GetCMSColorSpaceTypeTest_1884, Sig5colorData_ReturnsRGB_1884) {
    EXPECT_EQ(getCMSColorSpaceType(cmsSig5colorData), PT_RGB);
}

TEST(GetCMSColorSpaceTypeTest_1884, Sig6colorData_ReturnsRGB_1884) {
    EXPECT_EQ(getCMSColorSpaceType(cmsSig6colorData), PT_RGB);
}

TEST(GetCMSColorSpaceTypeTest_1884, Sig7colorData_ReturnsRGB_1884) {
    EXPECT_EQ(getCMSColorSpaceType(cmsSig7colorData), PT_RGB);
}

TEST(GetCMSColorSpaceTypeTest_1884, Sig8colorData_ReturnsRGB_1884) {
    EXPECT_EQ(getCMSColorSpaceType(cmsSig8colorData), PT_RGB);
}

TEST(GetCMSColorSpaceTypeTest_1884, Sig9colorData_ReturnsRGB_1884) {
    EXPECT_EQ(getCMSColorSpaceType(cmsSig9colorData), PT_RGB);
}

TEST(GetCMSColorSpaceTypeTest_1884, Sig10colorData_ReturnsRGB_1884) {
    EXPECT_EQ(getCMSColorSpaceType(cmsSig10colorData), PT_RGB);
}

TEST(GetCMSColorSpaceTypeTest_1884, Sig11colorData_ReturnsRGB_1884) {
    EXPECT_EQ(getCMSColorSpaceType(cmsSig11colorData), PT_RGB);
}

TEST(GetCMSColorSpaceTypeTest_1884, Sig12colorData_ReturnsRGB_1884) {
    EXPECT_EQ(getCMSColorSpaceType(cmsSig12colorData), PT_RGB);
}

TEST(GetCMSColorSpaceTypeTest_1884, Sig13colorData_ReturnsRGB_1884) {
    EXPECT_EQ(getCMSColorSpaceType(cmsSig13colorData), PT_RGB);
}

TEST(GetCMSColorSpaceTypeTest_1884, Sig14colorData_ReturnsRGB_1884) {
    EXPECT_EQ(getCMSColorSpaceType(cmsSig14colorData), PT_RGB);
}

TEST(GetCMSColorSpaceTypeTest_1884, Sig15colorData_ReturnsRGB_1884) {
    EXPECT_EQ(getCMSColorSpaceType(cmsSig15colorData), PT_RGB);
}

// Test default/unknown value returns PT_RGB

TEST(GetCMSColorSpaceTypeTest_1884, UnknownSignature_ReturnsRGB_1884) {
    // Use an arbitrary value that doesn't match any known signature
    cmsColorSpaceSignature unknownSig = static_cast<cmsColorSpaceSignature>(0x00000000);
    EXPECT_EQ(getCMSColorSpaceType(unknownSig), PT_RGB);
}

TEST(GetCMSColorSpaceTypeTest_1884, AnotherUnknownSignature_ReturnsRGB_1884) {
    // Use another arbitrary unknown value
    cmsColorSpaceSignature unknownSig = static_cast<cmsColorSpaceSignature>(0xFFFFFFFF);
    EXPECT_EQ(getCMSColorSpaceType(unknownSig), PT_RGB);
}

// Boundary: verify that the return type is consistent and the RGB value is as expected
TEST(GetCMSColorSpaceTypeTest_1884, RGBReturnValueIsCorrect_1884) {
    unsigned int result = getCMSColorSpaceType(cmsSigRgbData);
    EXPECT_EQ(result, static_cast<unsigned int>(PT_RGB));
}

// Verify that known types return distinct values from each other (where applicable)
TEST(GetCMSColorSpaceTypeTest_1884, KnownTypesAreDistinct_1884) {
    unsigned int xyz = getCMSColorSpaceType(cmsSigXYZData);
    unsigned int lab = getCMSColorSpaceType(cmsSigLabData);
    unsigned int yuv = getCMSColorSpaceType(cmsSigLuvData);
    unsigned int ycbcr = getCMSColorSpaceType(cmsSigYCbCrData);
    unsigned int yxy = getCMSColorSpaceType(cmsSigYxyData);
    unsigned int rgb = getCMSColorSpaceType(cmsSigRgbData);
    unsigned int gray = getCMSColorSpaceType(cmsSigGrayData);
    unsigned int hsv = getCMSColorSpaceType(cmsSigHsvData);
    unsigned int hls = getCMSColorSpaceType(cmsSigHlsData);
    unsigned int cmyk = getCMSColorSpaceType(cmsSigCmykData);
    unsigned int cmy = getCMSColorSpaceType(cmsSigCmyData);

    // All known mappings should produce different PT_* values
    std::set<unsigned int> values = {xyz, lab, yuv, ycbcr, yxy, rgb, gray, hsv, hls, cmyk, cmy};
    EXPECT_EQ(values.size(), 11u);
}

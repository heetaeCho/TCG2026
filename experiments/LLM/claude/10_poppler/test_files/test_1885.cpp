#include <gtest/gtest.h>
#include <lcms2.h>

// Declaration of the function under test
unsigned int getCMSNChannels(cmsColorSpaceSignature cs);

// Test 3-channel color spaces
TEST(GetCMSNChannelsTest_1885, XYZDataReturns3_1885) {
    EXPECT_EQ(3u, getCMSNChannels(cmsSigXYZData));
}

TEST(GetCMSNChannelsTest_1885, LuvDataReturns3_1885) {
    EXPECT_EQ(3u, getCMSNChannels(cmsSigLuvData));
}

TEST(GetCMSNChannelsTest_1885, LabDataReturns3_1885) {
    EXPECT_EQ(3u, getCMSNChannels(cmsSigLabData));
}

TEST(GetCMSNChannelsTest_1885, YCbCrDataReturns3_1885) {
    EXPECT_EQ(3u, getCMSNChannels(cmsSigYCbCrData));
}

TEST(GetCMSNChannelsTest_1885, YxyDataReturns3_1885) {
    EXPECT_EQ(3u, getCMSNChannels(cmsSigYxyData));
}

TEST(GetCMSNChannelsTest_1885, RgbDataReturns3_1885) {
    EXPECT_EQ(3u, getCMSNChannels(cmsSigRgbData));
}

TEST(GetCMSNChannelsTest_1885, HsvDataReturns3_1885) {
    EXPECT_EQ(3u, getCMSNChannels(cmsSigHsvData));
}

TEST(GetCMSNChannelsTest_1885, HlsDataReturns3_1885) {
    EXPECT_EQ(3u, getCMSNChannels(cmsSigHlsData));
}

TEST(GetCMSNChannelsTest_1885, CmyDataReturns3_1885) {
    EXPECT_EQ(3u, getCMSNChannels(cmsSigCmyData));
}

TEST(GetCMSNChannelsTest_1885, Sig3colorDataReturns3_1885) {
    EXPECT_EQ(3u, getCMSNChannels(cmsSig3colorData));
}

// Test 1-channel color space
TEST(GetCMSNChannelsTest_1885, GrayDataReturns1_1885) {
    EXPECT_EQ(1u, getCMSNChannels(cmsSigGrayData));
}

// Test 4-channel color spaces
TEST(GetCMSNChannelsTest_1885, CmykDataReturns4_1885) {
    EXPECT_EQ(4u, getCMSNChannels(cmsSigCmykData));
}

TEST(GetCMSNChannelsTest_1885, Sig4colorDataReturns4_1885) {
    EXPECT_EQ(4u, getCMSNChannels(cmsSig4colorData));
}

// Test 2-channel color space
TEST(GetCMSNChannelsTest_1885, Sig2colorDataReturns2_1885) {
    EXPECT_EQ(2u, getCMSNChannels(cmsSig2colorData));
}

// Test 5-channel color space
TEST(GetCMSNChannelsTest_1885, Sig5colorDataReturns5_1885) {
    EXPECT_EQ(5u, getCMSNChannels(cmsSig5colorData));
}

// Test 6-channel color space
TEST(GetCMSNChannelsTest_1885, Sig6colorDataReturns6_1885) {
    EXPECT_EQ(6u, getCMSNChannels(cmsSig6colorData));
}

// Test 7-channel color space
TEST(GetCMSNChannelsTest_1885, Sig7colorDataReturns7_1885) {
    EXPECT_EQ(7u, getCMSNChannels(cmsSig7colorData));
}

// Test 8-channel color space
TEST(GetCMSNChannelsTest_1885, Sig8colorDataReturns8_1885) {
    EXPECT_EQ(8u, getCMSNChannels(cmsSig8colorData));
}

// Test 9-channel color space
TEST(GetCMSNChannelsTest_1885, Sig9colorDataReturns9_1885) {
    EXPECT_EQ(9u, getCMSNChannels(cmsSig9colorData));
}

// Test 10-channel color space
TEST(GetCMSNChannelsTest_1885, Sig10colorDataReturns10_1885) {
    EXPECT_EQ(10u, getCMSNChannels(cmsSig10colorData));
}

// Test 11-channel color space
TEST(GetCMSNChannelsTest_1885, Sig11colorDataReturns11_1885) {
    EXPECT_EQ(11u, getCMSNChannels(cmsSig11colorData));
}

// Test 12-channel color space
TEST(GetCMSNChannelsTest_1885, Sig12colorDataReturns12_1885) {
    EXPECT_EQ(12u, getCMSNChannels(cmsSig12colorData));
}

// Test 13-channel color space
TEST(GetCMSNChannelsTest_1885, Sig13colorDataReturns13_1885) {
    EXPECT_EQ(13u, getCMSNChannels(cmsSig13colorData));
}

// Test 14-channel color space
TEST(GetCMSNChannelsTest_1885, Sig14colorDataReturns14_1885) {
    EXPECT_EQ(14u, getCMSNChannels(cmsSig14colorData));
}

// Test 15-channel color space
TEST(GetCMSNChannelsTest_1885, Sig15colorDataReturns15_1885) {
    EXPECT_EQ(15u, getCMSNChannels(cmsSig15colorData));
}

// Test default case: unrecognized color space signature returns 3
TEST(GetCMSNChannelsTest_1885, UnknownColorSpaceReturnsDefault3_1885) {
    // Use a value that doesn't match any known case
    cmsColorSpaceSignature unknownSig = static_cast<cmsColorSpaceSignature>(0x00000000);
    EXPECT_EQ(3u, getCMSNChannels(unknownSig));
}

TEST(GetCMSNChannelsTest_1885, AnotherUnknownColorSpaceReturnsDefault3_1885) {
    // Use another arbitrary unknown value
    cmsColorSpaceSignature unknownSig = static_cast<cmsColorSpaceSignature>(0xFFFFFFFF);
    EXPECT_EQ(3u, getCMSNChannels(unknownSig));
}

TEST(GetCMSNChannelsTest_1885, YetAnotherUnknownColorSpaceReturnsDefault3_1885) {
    cmsColorSpaceSignature unknownSig = static_cast<cmsColorSpaceSignature>(0x12345678);
    EXPECT_EQ(3u, getCMSNChannels(unknownSig));
}

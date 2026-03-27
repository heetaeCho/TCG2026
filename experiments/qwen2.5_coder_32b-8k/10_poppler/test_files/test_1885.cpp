#include <gtest/gtest.h>

#include "GfxState.h"  // Assuming the function is declared in this header



// Test fixture for GfxState tests

class GfxStateTest_1885 : public ::testing::Test {

protected:

    // Setup and teardown can be added here if needed

};



TEST_F(GfxStateTest_1885, GetCMSNChannels_XYZData_Returns3_1885) {

    EXPECT_EQ(getCMSNChannels(cmsSigXYZData), 3);

}



TEST_F(GfxStateTest_1885, GetCMSNChannels_LuvData_Returns3_1885) {

    EXPECT_EQ(getCMSNChannels(cmsSigLuvData), 3);

}



TEST_F(GfxStateTest_1885, GetCMSNChannels_LabData_Returns3_1885) {

    EXPECT_EQ(getCMSNChannels(cmsSigLabData), 3);

}



TEST_F(GfxStateTest_1885, GetCMSNChannels_YCbCrData_Returns3_1885) {

    EXPECT_EQ(getCMSNChannels(cmsSigYCbCrData), 3);

}



TEST_F(GfxStateTest_1885, GetCMSNChannels_YxyData_Returns3_1885) {

    EXPECT_EQ(getCMSNChannels(cmsSigYxyData), 3);

}



TEST_F(GfxStateTest_1885, GetCMSNChannels_RgbData_Returns3_1885) {

    EXPECT_EQ(getCMSNChannels(cmsSigRgbData), 3);

}



TEST_F(GfxStateTest_1885, GetCMSNChannels_HsvData_Returns3_1885) {

    EXPECT_EQ(getCMSNChannels(cmsSigHsvData), 3);

}



TEST_F(GfxStateTest_1885, GetCMSNChannels_HlsData_Returns3_1885) {

    EXPECT_EQ(getCMSNChannels(cmsSigHlsData), 3);

}



TEST_F(GfxStateTest_1885, GetCMSNChannels_CmyData_Returns3_1885) {

    EXPECT_EQ(getCMSNChannels(cmsSigCmyData), 3);

}



TEST_F(GfxStateTest_1885, GetCMSNChannels_3colorData_Returns3_1885) {

    EXPECT_EQ(getCMSNChannels(cmsSig3colorData), 3);

}



TEST_F(GfxStateTest_1885, GetCMSNChannels_GrayData_Returns1_1885) {

    EXPECT_EQ(getCMSNChannels(cmsSigGrayData), 1);

}



TEST_F(GfxStateTest_1885, GetCMSNChannels_CmykData_Returns4_1885) {

    EXPECT_EQ(getCMSNChannels(cmsSigCmykData), 4);

}



TEST_F(GfxStateTest_1885, GetCMSNChannels_4colorData_Returns4_1885) {

    EXPECT_EQ(getCMSNChannels(cmsSig4colorData), 4);

}



TEST_F(GfxStateTest_1885, GetCMSNChannels_2colorData_Returns2_1885) {

    EXPECT_EQ(getCMSNChannels(cmsSig2colorData), 2);

}



TEST_F(GfxStateTest_1885, GetCMSNChannels_5colorData_Returns5_1885) {

    EXPECT_EQ(getCMSNChannels(cmsSig5colorData), 5);

}



TEST_F(GfxStateTest_1885, GetCMSNChannels_6colorData_Returns6_1885) {

    EXPECT_EQ(getCMSNChannels(cmsSig6colorData), 6);

}



TEST_F(GfxStateTest_1885, GetCMSNChannels_7colorData_Returns7_1885) {

    EXPECT_EQ(getCMSNChannels(cmsSig7colorData), 7);

}



TEST_F(GfxStateTest_1885, GetCMSNChannels_8colorData_Returns8_1885) {

    EXPECT_EQ(getCMSNChannels(cmsSig8colorData), 8);

}



TEST_F(GfxStateTest_1885, GetCMSNChannels_9colorData_Returns9_1885) {

    EXPECT_EQ(getCMSNChannels(cmsSig9colorData), 9);

}



TEST_F(GfxStateTest_1885, GetCMSNChannels_10colorData_Returns10_1885) {

    EXPECT_EQ(getCMSNChannels(cmsSig10colorData), 10);

}



TEST_F(GfxStateTest_1885, GetCMSNChannels_11colorData_Returns11_1885) {

    EXPECT_EQ(getCMSNChannels(cmsSig11colorData), 11);

}



TEST_F(GfxStateTest_1885, GetCMSNChannels_12colorData_Returns12_1885) {

    EXPECT_EQ(getCMSNChannels(cmsSig12colorData), 12);

}



TEST_F(GfxStateTest_1885, GetCMSNChannels_13colorData_Returns13_1885) {

    EXPECT_EQ(getCMSNChannels(cmsSig13colorData), 13);

}



TEST_F(GfxStateTest_1885, GetCMSNChannels_14colorData_Returns14_1885) {

    EXPECT_EQ(getCMSNChannels(cmsSig14colorData), 14);

}



TEST_F(GfxStateTest_1885, GetCMSNChannels_15colorData_Returns15_1885) {

    EXPECT_EQ(getCMSNChannels(cmsSig15colorData), 15);

}



TEST_F(GfxStateTest_1885, GetCMSNChannels_Default_Returns3_1885) {

    EXPECT_EQ(getCMSNChannels(static_cast<cmsColorSpaceSignature>(0)), 3);

}

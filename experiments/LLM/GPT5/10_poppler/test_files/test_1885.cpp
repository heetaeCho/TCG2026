#include <gtest/gtest.h>
#include "GfxState.h"  // Assuming this is where getCMSNChannels is declared

// Test fixture class for GfxState
class GfxStateTest_1885 : public ::testing::Test {
protected:
    // Any necessary setup for the tests
    void SetUp() override {
        // Setup code (if necessary)
    }

    // Any necessary teardown for the tests
    void TearDown() override {
        // Teardown code (if necessary)
    }
};

// Test normal operation for different cmsColorSpaceSignature cases
TEST_F(GfxStateTest_1885, GetCMSNChannelsXYZData_1885) {
    EXPECT_EQ(getCMSNChannels(cmsSigXYZData), 3);
}

TEST_F(GfxStateTest_1885, GetCMSNChannelsLuvData_1885) {
    EXPECT_EQ(getCMSNChannels(cmsSigLuvData), 3);
}

TEST_F(GfxStateTest_1885, GetCMSNChannelsLabData_1885) {
    EXPECT_EQ(getCMSNChannels(cmsSigLabData), 3);
}

TEST_F(GfxStateTest_1885, GetCMSNChannelsYCbCrData_1885) {
    EXPECT_EQ(getCMSNChannels(cmsSigYCbCrData), 3);
}

TEST_F(GfxStateTest_1885, GetCMSNChannelsYxyData_1885) {
    EXPECT_EQ(getCMSNChannels(cmsSigYxyData), 3);
}

TEST_F(GfxStateTest_1885, GetCMSNChannelsRgbData_1885) {
    EXPECT_EQ(getCMSNChannels(cmsSigRgbData), 3);
}

TEST_F(GfxStateTest_1885, GetCMSNChannelsHsvData_1885) {
    EXPECT_EQ(getCMSNChannels(cmsSigHsvData), 3);
}

TEST_F(GfxStateTest_1885, GetCMSNChannelsHlsData_1885) {
    EXPECT_EQ(getCMSNChannels(cmsSigHlsData), 3);
}

TEST_F(GfxStateTest_1885, GetCMSNChannelsCmyData_1885) {
    EXPECT_EQ(getCMSNChannels(cmsSigCmyData), 3);
}

TEST_F(GfxStateTest_1885, GetCMSNChannels3colorData_1885) {
    EXPECT_EQ(getCMSNChannels(cmsSig3colorData), 3);
}

TEST_F(GfxStateTest_1885, GetCMSNChannelsGrayData_1885) {
    EXPECT_EQ(getCMSNChannels(cmsSigGrayData), 1);
}

TEST_F(GfxStateTest_1885, GetCMSNChannelsCmykData_1885) {
    EXPECT_EQ(getCMSNChannels(cmsSigCmykData), 4);
}

TEST_F(GfxStateTest_1885, GetCMSNChannels4colorData_1885) {
    EXPECT_EQ(getCMSNChannels(cmsSig4colorData), 4);
}

TEST_F(GfxStateTest_1885, GetCMSNChannels2colorData_1885) {
    EXPECT_EQ(getCMSNChannels(cmsSig2colorData), 2);
}

TEST_F(GfxStateTest_1885, GetCMSNChannels5colorData_1885) {
    EXPECT_EQ(getCMSNChannels(cmsSig5colorData), 5);
}

TEST_F(GfxStateTest_1885, GetCMSNChannels6colorData_1885) {
    EXPECT_EQ(getCMSNChannels(cmsSig6colorData), 6);
}

TEST_F(GfxStateTest_1885, GetCMSNChannels7colorData_1885) {
    EXPECT_EQ(getCMSNChannels(cmsSig7colorData), 7);
}

TEST_F(GfxStateTest_1885, GetCMSNChannels8colorData_1885) {
    EXPECT_EQ(getCMSNChannels(cmsSig8colorData), 8);
}

TEST_F(GfxStateTest_1885, GetCMSNChannels9colorData_1885) {
    EXPECT_EQ(getCMSNChannels(cmsSig9colorData), 9);
}

TEST_F(GfxStateTest_1885, GetCMSNChannels10colorData_1885) {
    EXPECT_EQ(getCMSNChannels(cmsSig10colorData), 10);
}

TEST_F(GfxStateTest_1885, GetCMSNChannels11colorData_1885) {
    EXPECT_EQ(getCMSNChannels(cmsSig11colorData), 11);
}

TEST_F(GfxStateTest_1885, GetCMSNChannels12colorData_1885) {
    EXPECT_EQ(getCMSNChannels(cmsSig12colorData), 12);
}

TEST_F(GfxStateTest_1885, GetCMSNChannels13colorData_1885) {
    EXPECT_EQ(getCMSNChannels(cmsSig13colorData), 13);
}

TEST_F(GfxStateTest_1885, GetCMSNChannels14colorData_1885) {
    EXPECT_EQ(getCMSNChannels(cmsSig14colorData), 14);
}

TEST_F(GfxStateTest_1885, GetCMSNChannels15colorData_1885) {
    EXPECT_EQ(getCMSNChannels(cmsSig15colorData), 15);
}

// Test the default case when an invalid color space signature is passed
TEST_F(GfxStateTest_1885, GetCMSNChannelsDefault_1885) {
    EXPECT_EQ(getCMSNChannels(static_cast<cmsColorSpaceSignature>(9999)), 3);
}
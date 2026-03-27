#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/splash/SplashTypes.h"



extern int splashColorModeNComps[];



namespace {



void splashOutBlendDifference(SplashColorPtr src, SplashColorPtr dest, SplashColorPtr blend, SplashColorMode cm);



class BlendDifferenceTest_1586 : public ::testing::Test {

protected:

    static const int kMaxComponents = 8; // Assuming the maximum components based on provided modes

    unsigned char src[kMaxComponents];

    unsigned char dest[kMaxComponents];

    unsigned char blend[kMaxComponents];



    void setUpBuffers(int num_components) {

        for (int i = 0; i < num_components; ++i) {

            src[i] = static_cast<unsigned char>(rand() % 256);

            dest[i] = static_cast<unsigned char>(rand() % 256);

            blend[i] = 0;

        }

    }



    void verifyBlendResult(int num_components, bool cmyk_or_devicen) {

        for (int i = 0; i < num_components; ++i) {

            if (cmyk_or_devicen && i < 4) {

                EXPECT_EQ(blend[i], std::abs(255 - src[i] - (255 - dest[i])));

            } else {

                EXPECT_EQ(blend[i], std::abs(src[i] - dest[i]));

            }

        }

    }

};



TEST_F(BlendDifferenceTest_1586, PutIncreasesCount_Mono1_1586) {

    setUpBuffers(splashColorModeNComps[splashModeMono1]);

    splashOutBlendDifference(src, dest, blend, splashModeMono1);

    verifyBlendResult(splashColorModeNComps[splashModeMono1], false);

}



TEST_F(BlendDifferenceTest_1586, PutIncreasesCount_Mono8_1586) {

    setUpBuffers(splashColorModeNComps[splashModeMono8]);

    splashOutBlendDifference(src, dest, blend, splashModeMono8);

    verifyBlendResult(splashColorModeNComps[splashModeMono8], false);

}



TEST_F(BlendDifferenceTest_1586, PutIncreasesCount_RGB8_1586) {

    setUpBuffers(splashColorModeNComps[splashModeRGB8]);

    splashOutBlendDifference(src, dest, blend, splashModeRGB8);

    verifyBlendResult(splashColorModeNComps[splashModeRGB8], false);

}



TEST_F(BlendDifferenceTest_1586, PutIncreasesCount_BGR8_1586) {

    setUpBuffers(splashColorModeNComps[splashModeBGR8]);

    splashOutBlendDifference(src, dest, blend, splashModeBGR8);

    verifyBlendResult(splashColorModeNComps[splashModeBGR8], false);

}



TEST_F(BlendDifferenceTest_1586, PutIncreasesCount_XBGR8_1586) {

    setUpBuffers(splashColorModeNComps[splashModeXBGR8]);

    splashOutBlendDifference(src, dest, blend, splashModeXBGR8);

    verifyBlendResult(splashColorModeNComps[splashModeXBGR8], false);

}



TEST_F(BlendDifferenceTest_1586, PutIncreasesCount_CMYK8_1586) {

    setUpBuffers(splashColorModeNComps[splashModeCMYK8]);

    splashOutBlendDifference(src, dest, blend, splashModeCMYK8);

    verifyBlendResult(splashColorModeNComps[splashModeCMYK8], true);

}



TEST_F(BlendDifferenceTest_1586, PutIncreasesCount_DeviceN8_1586) {

    setUpBuffers(splashColorModeNComps[splashModeDeviceN8]);

    splashOutBlendDifference(src, dest, blend, splashModeDeviceN8);

    verifyBlendResult(splashColorModeNComps[splashModeDeviceN8], true);



    // Special case for DeviceN8 where both src and dest are 0

    for (int i = 4; i < splashColorModeNComps[splashModeDeviceN8]; ++i) {

        src[i] = 0;

        dest[i] = 0;

    }

    splashOutBlendDifference(src, dest, blend, splashModeDeviceN8);

    for (int i = 4; i < splashColorModeNComps[splashModeDeviceN8]; ++i) {

        EXPECT_EQ(blend[i], 0);

    }

}



TEST_F(BlendDifferenceTest_1586, BoundaryCondition_AllZeroes_1586) {

    memset(src, 0, sizeof(src));

    memset(dest, 0, sizeof(dest));

    splashOutBlendDifference(src, dest, blend, splashModeRGB8);

    for (int i = 0; i < splashColorModeNComps[splashModeRGB8]; ++i) {

        EXPECT_EQ(blend[i], 0);

    }

}



TEST_F(BlendDifferenceTest_1586, BoundaryCondition_AllOnes_1586) {

    memset(src, 255, sizeof(src));

    memset(dest, 255, sizeof(dest));

    splashOutBlendDifference(src, dest, blend, splashModeRGB8);

    for (int i = 0; i < splashColorModeNComps[splashModeRGB8]; ++i) {

        EXPECT_EQ(blend[i], 0);

    }

}



} // namespace

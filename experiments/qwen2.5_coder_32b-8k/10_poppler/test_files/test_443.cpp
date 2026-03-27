#include <gtest/gtest.h>

#include "GfxState.h"



class GfxDeviceCMYKColorSpaceTest : public ::testing::Test {

protected:

    std::unique_ptr<GfxDeviceCMYKColorSpace> colorSpace;



    void SetUp() override {

        colorSpace = std::make_unique<GfxDeviceCMYKColorSpace>();

    }

};



TEST_F(GfxDeviceCMYKColorSpaceTest_443, UseGetRGBLine_ReturnsTrue_443) {

    EXPECT_TRUE(colorSpace->useGetRGBLine());

}



// Additional test cases for other functions



TEST_F(GfxDeviceCMYKColorSpaceTest_443, GetNComps_ReturnsExpectedValue_443) {

    int nComps = colorSpace->getNComps();

    EXPECT_EQ(nComps, 4); // Assuming CMYK has 4 components

}



TEST_F(GfxDeviceCMYKColorSpaceTest_443, UseGetCMYKLine_ReturnsFalseByDefault_443) {

    EXPECT_FALSE(colorSpace->useGetCMYKLine());

}



TEST_F(GfxDeviceCMYKColorSpaceTest_443, UseGetDeviceNLine_ReturnsFalseByDefault_443) {

    EXPECT_FALSE(colorSpace->useGetDeviceNLine());

}



TEST_F(GfxDeviceCMYKColorSpaceTest_443, GetMode_ReturnsCorrectValue_443) {

    GfxColorSpaceMode mode = colorSpace->getMode();

    EXPECT_EQ(mode, gfxDeviceCMYK);

}

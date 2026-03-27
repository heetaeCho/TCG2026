#include <gtest/gtest.h>

#include "GfxState.h"

#include <memory>



class GfxDeviceRGBColorSpaceTest : public ::testing::Test {

protected:

    std::unique_ptr<GfxDeviceRGBColorSpace> colorSpace;



    void SetUp() override {

        colorSpace = std::make_unique<GfxDeviceRGBColorSpace>();

    }

};



TEST_F(GfxDeviceRGBColorSpaceTest_422, GetMode_ReturnsDeviceRGB_422) {

    EXPECT_EQ(colorSpace->getMode(), csDeviceRGB);

}



TEST_F(GfxDeviceRGBColorSpaceTest_422, Copy_ReturnsNonNullUniquePtr_422) {

    auto copy = colorSpace->copy();

    EXPECT_NE(copy, nullptr);

}



TEST_F(GfxDeviceRGBColorSpaceTest_422, GetNComps_ReturnsThree_422) {

    EXPECT_EQ(colorSpace->getNComps(), 3);

}



TEST_F(GfxDeviceRGBColorSpaceTest_422, UseGetRGBLine_ReturnsTrue_422) {

    EXPECT_TRUE(colorSpace->useGetRGBLine());

}



TEST_F(GfxDeviceRGBColorSpaceTest_422, UseGetGrayLine_ReturnsFalse_422) {

    EXPECT_FALSE(colorSpace->useGetGrayLine());

}



TEST_F(GfxDeviceRGBColorSpaceTest_422, UseGetCMYKLine_ReturnsFalse_422) {

    EXPECT_FALSE(colorSpace->useGetCMYKLine());

}



TEST_F(GfxDeviceRGBColorSpaceTest_422, UseGetDeviceNLine_ReturnsFalse_422) {

    EXPECT_FALSE(colorSpace->useGetDeviceNLine());

}

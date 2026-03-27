#include <gtest/gtest.h>

#include "GfxState.h"



class GfxDeviceRGBColorSpaceTest : public ::testing::Test {

protected:

    GfxDeviceRGBColorSpace colorSpace;

};



TEST_F(GfxDeviceRGBColorSpaceTest_423, UseGetRGBLine_ReturnsTrue_423) {

    EXPECT_TRUE(colorSpace.useGetRGBLine());

}



TEST_F(GfxDeviceRGBColorSpaceTest_423, UseGetGrayLine_ReturnsFalseByDefault_423) {

    EXPECT_FALSE(colorSpace.useGetGrayLine());

}



TEST_F(GfxDeviceRGBColorSpaceTest_423, UseGetCMYKLine_ReturnsFalseByDefault_423) {

    EXPECT_FALSE(colorSpace.useGetCMYKLine());

}



TEST_F(GfxDeviceRGBColorSpaceTest_423, UseGetDeviceNLine_ReturnsFalseByDefault_423) {

    EXPECT_FALSE(colorSpace.useGetDeviceNLine());

}



TEST_F(GfxDeviceRGBColorSpaceTest_423, GetMode_ReturnsCorrectMode_423) {

    EXPECT_EQ(colorSpace.getMode(), gfxDeviceRGB);

}



TEST_F(GfxDeviceRGBColorSpaceTest_423, GetNComps_ReturnsThreeComponentsForRGB_423) {

    EXPECT_EQ(colorSpace.getNComps(), 3);

}

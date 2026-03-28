#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"



using namespace testing;



class GfxColorSpaceTest : public ::testing::Test {

protected:

    std::unique_ptr<GfxColorSpace> colorSpace;

    

    virtual void SetUp() {

        colorSpace = std::make_unique<GfxColorSpace>();

    }

};



TEST_F(GfxColorSpaceTest_404, CopyReturnsNonNullPointer_404) {

    EXPECT_NE(colorSpace->copy(), nullptr);

}



TEST_F(GfxColorSpaceTest_404, GetNComps_ReturnsPositiveValue_404) {

    EXPECT_GE(colorSpace->getNComps(), 0);

}



TEST_F(GfxColorSpaceTest_404, UseGetRGBLine_DefaultReturnsFalse_404) {

    EXPECT_FALSE(colorSpace->useGetRGBLine());

}



TEST_F(GfxColorSpaceTest_404, UseGetGrayLine_DefaultReturnsFalse_404) {

    EXPECT_FALSE(colorSpace->useGetGrayLine());

}



TEST_F(GfxColorSpaceTest_404, UseGetCMYKLine_DefaultReturnsFalse_404) {

    EXPECT_FALSE(colorSpace->useGetCMYKLine());

}



TEST_F(GfxColorSpaceTest_404, UseGetDeviceNLine_DefaultReturnsFalse_404) {

    EXPECT_FALSE(colorSpace->useGetDeviceNLine());

}



TEST_F(GfxColorSpaceTest_404, IsNonMarking_DefaultReturnsFalse_404) {

    EXPECT_FALSE(colorSpace->isNonMarking());

}



TEST_F(GfxColorSpaceTest_404, GetOverprintMask_DefaultReturnsZero_404) {

    EXPECT_EQ(colorSpace->getOverprintMask(), 0);

}



TEST_F(GfxColorSpaceTest_404, GetMapping_ReturnsEmptyVectorByDefault_404) {

    EXPECT_TRUE(colorSpace->getMapping().empty());

}

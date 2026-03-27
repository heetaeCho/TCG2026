#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/GfxState.h"

#include <memory>



class GfxColorSpaceTest_403 : public ::testing::Test {

protected:

    std::unique_ptr<GfxColorSpace> colorSpace;



    void SetUp() override {

        colorSpace = std::make_unique<GfxColorSpace>();

    }

};



TEST_F(GfxColorSpaceTest_403, UseGetCMYKLine_Default_403) {

    EXPECT_FALSE(colorSpace->useGetCMYKLine());

}



TEST_F(GfxColorSpaceTest_403, GetOverprintMask_Default_403) {

    EXPECT_EQ(0u, colorSpace->getOverprintMask());

}



TEST_F(GfxColorSpaceTest_403, UseGetRGBLine_Default_403) {

    EXPECT_FALSE(colorSpace->useGetRGBLine());

}



TEST_F(GfxColorSpaceTest_403, UseGetGrayLine_Default_403) {

    EXPECT_FALSE(colorSpace->useGetGrayLine());

}



TEST_F(GfxColorSpaceTest_403, UseGetDeviceNLine_Default_403) {

    EXPECT_FALSE(colorSpace->useGetDeviceNLine());

}



TEST_F(GfxColorSpaceTest_403, IsNonMarking_Default_403) {

    EXPECT_FALSE(colorSpace->isNonMarking());

}



TEST_F(GfxColorSpaceTest_403, GetMapping_Empty_Default_403) {

    const std::vector<int>& mapping = colorSpace->getMapping();

    EXPECT_TRUE(mapping.empty());

}

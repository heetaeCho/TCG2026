#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"



using namespace testing;



class GfxColorSpaceTest_401 : public Test {

protected:

    std::unique_ptr<GfxColorSpace> colorSpace;



    void SetUp() override {

        colorSpace = std::make_unique<GfxColorSpace>();

    }

};



TEST_F(GfxColorSpaceTest_401, UseGetRGBLine_Default_401) {

    EXPECT_FALSE(colorSpace->useGetRGBLine());

}



TEST_F(GfxColorSpaceTest_401, UseGetGrayLine_Default_401) {

    EXPECT_FALSE(colorSpace->useGetGrayLine());

}



TEST_F(GfxColorSpaceTest_401, UseGetCMYKLine_Default_401) {

    EXPECT_FALSE(colorSpace->useGetCMYKLine());

}



TEST_F(GfxColorSpaceTest_401, UseGetDeviceNLine_Default_401) {

    EXPECT_FALSE(colorSpace->useGetDeviceNLine());

}



TEST_F(GfxColorSpaceTest_401, IsNonMarking_Default_401) {

    EXPECT_FALSE(colorSpace->isNonMarking());

}



TEST_F(GfxColorSpaceTest_401, GetOverprintMask_Default_401) {

    EXPECT_EQ(0u, colorSpace->getOverprintMask());

}

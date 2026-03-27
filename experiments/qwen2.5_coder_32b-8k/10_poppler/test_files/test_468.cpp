#include <gtest/gtest.h>

#include "GfxState.h"



using namespace testing;



class GfxIndexedColorSpaceTest_468 : public ::testing::Test {

protected:

    std::unique_ptr<GfxColorSpace> base;

    int indexHigh = 255;

    std::unique_ptr<GfxIndexedColorSpace> colorSpace;



    void SetUp() override {

        base = std::make_unique<GfxColorSpace>();

        colorSpace = std::make_unique<GfxIndexedColorSpace>(std::move(base), indexHigh);

    }

};



TEST_F(GfxIndexedColorSpaceTest_468, UseGetDeviceNLine_ReturnsTrue_468) {

    EXPECT_TRUE(colorSpace->useGetDeviceNLine());

}



// Additional test cases based on the interface



TEST_F(GfxIndexedColorSpaceTest_468, GetIndexHigh_ReturnsCorrectValue_468) {

    EXPECT_EQ(colorSpace->getIndexHigh(), indexHigh);

}



TEST_F(GfxIndexedColorSpaceTest_468, UseGetRGBLine_ReturnsFalseByDefault_468) {

    EXPECT_FALSE(colorSpace->useGetRGBLine());

}



TEST_F(GfxIndexedColorSpaceTest_468, UseGetCMYKLine_ReturnsFalseByDefault_468) {

    EXPECT_FALSE(colorSpace->useGetCMYKLine());

}

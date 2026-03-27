#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"



class GfxIndexedColorSpaceTest_466 : public ::testing::Test {

protected:

    std::unique_ptr<GfxColorSpace> base;

    int indexHigh = 255;



    void SetUp() override {

        base = std::make_unique<GfxColorSpace>();

    }



    std::unique_ptr<GfxIndexedColorSpace> createGfxIndexedColorSpace() {

        return std::make_unique<GfxIndexedColorSpace>(std::move(base), indexHigh);

    }

};



TEST_F(GfxIndexedColorSpaceTest_466, UseGetRGBLineReturnsTrue_466) {

    auto colorSpace = createGfxIndexedColorSpace();

    EXPECT_TRUE(colorSpace->useGetRGBLine());

}



TEST_F(GfxIndexedColorSpaceTest_466, GetIndexHighReturnsCorrectValue_466) {

    auto colorSpace = createGfxIndexedColorSpace();

    EXPECT_EQ(colorSpace->getIndexHigh(), indexHigh);

}



TEST_F(GfxIndexedColorSpaceTest_466, CopyCreatesNewInstance_466) {

    auto original = createGfxIndexedColorSpace();

    auto copy = std::unique_ptr<GfxIndexedColorSpace>(static_cast<GfxIndexedColorSpace*>(original->copy().release()));

    EXPECT_NE(original.get(), copy.get());

}



TEST_F(GfxIndexedColorSpaceTest_466, GetBaseReturnsCorrectPointer_466) {

    auto colorSpace = createGfxIndexedColorSpace();

    EXPECT_EQ(colorSpace->getBase(), base.get());

}



TEST_F(GfxIndexedColorSpaceTest_466, UseGetCMYKLineReturnsFalseByDefault_466) {

    auto colorSpace = createGfxIndexedColorSpace();

    EXPECT_FALSE(colorSpace->useGetCMYKLine());

}



TEST_F(GfxIndexedColorSpaceTest_466, UseGetDeviceNLineReturnsFalseByDefault_466) {

    auto colorSpace = createGfxIndexedColorSpace();

    EXPECT_FALSE(colorSpace->useGetDeviceNLine());

}

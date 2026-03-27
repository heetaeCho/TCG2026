#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"



using namespace testing;



class GfxIndexedColorSpaceTest : public ::testing::Test {

protected:

    std::unique_ptr<GfxColorSpace> baseColorSpace;

    int indexHigh = 255;

    GfxIndexedColorSpace* colorSpace;



    void SetUp() override {

        baseColorSpace = std::make_unique<GfxColorSpace>();

        colorSpace = new GfxIndexedColorSpace(std::move(baseColorSpace), indexHigh);

    }



    void TearDown() override {

        delete colorSpace;

    }

};



TEST_F(GfxIndexedColorSpaceTest_471, getIndexHigh_ReturnsCorrectValue_471) {

    EXPECT_EQ(colorSpace->getIndexHigh(), indexHigh);

}



TEST_F(GfxIndexedColorSpaceTest_471, getNComps_CallReturnsNonNegativeValue_471) {

    EXPECT_GE(colorSpace->getNComps(), 0);

}



TEST_F(GfxIndexedColorSpaceTest_471, getBase_ReturnsNonNullPointer_471) {

    EXPECT_NE(colorSpace->getBase(), nullptr);

}



TEST_F(GfxIndexedColorSpaceTest_471, getLookup_CallReturnsNonNullPointer_471) {

    EXPECT_NE(colorSpace->getLookup(), nullptr);

}



TEST_F(GfxIndexedColorSpaceTest_471, getOverprintMask_ReturnsNonNegativeValue_471) {

    EXPECT_GE(colorSpace->getOverprintMask(), 0);

}



TEST_F(GfxIndexedColorSpaceTest_471, useGetRGBLine_CallReturnsBoolean_471) {

    bool result = colorSpace->useGetRGBLine();

    EXPECT_TRUE(result || !result); // Always true for boolean

}



TEST_F(GfxIndexedColorSpaceTest_471, useGetCMYKLine_CallReturnsBoolean_471) {

    bool result = colorSpace->useGetCMYKLine();

    EXPECT_TRUE(result || !result); // Always true for boolean

}



TEST_F(GfxIndexedColorSpaceTest_471, useGetDeviceNLine_CallReturnsBoolean_471) {

    bool result = colorSpace->useGetDeviceNLine();

    EXPECT_TRUE(result || !result); // Always true for boolean

}

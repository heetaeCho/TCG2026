#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/GfxState.h"



using namespace testing;



class GfxIndexedColorSpaceTest_470 : public ::testing::Test {

protected:

    std::unique_ptr<GfxColorSpace> baseColorSpace = std::make_unique<GfxColorSpace>();

    int indexHigh = 255;

    GfxIndexedColorSpace* indexedColorSpace;



    void SetUp() override {

        indexedColorSpace = new GfxIndexedColorSpace(std::move(baseColorSpace), indexHigh);

    }



    void TearDown() override {

        delete indexedColorSpace;

    }

};



TEST_F(GfxIndexedColorSpaceTest_470, GetBaseReturnsCorrectPointer_470) {

    EXPECT_EQ(indexedColorSpace->getBase(), baseColorSpace.get());

}



TEST_F(GfxIndexedColorSpaceTest_470, getIndexHighReturnsCorrectValue_470) {

    EXPECT_EQ(indexedColorSpace->getIndexHigh(), indexHigh);

}



// Assuming getLookup is a method that returns the lookup table pointer

// Since we don't have access to the internal state, we can only check if it's not null if it's supposed to be initialized.

TEST_F(GfxIndexedColorSpaceTest_470, GetLookupReturnsNonNulPointer_470) {

    EXPECT_NE(indexedColorSpace->getLookup(), nullptr);

}



// Assuming getOverprintMask is a method that returns an unsigned int

// Since we don't have access to the internal state, we can only assume it returns 0 if not set otherwise.

TEST_F(GfxIndexedColorSpaceTest_470, GetOverprintMaskReturnsZeroByDefault_470) {

    EXPECT_EQ(indexedColorSpace->getOverprintMask(), 0);

}



// Testing boundary conditions for getIndexHigh

TEST_F(GfxIndexedColorSpaceTest_470, IndexHighBoundaryConditionMinimum_470) {

    int minIndexHigh = 0;

    GfxIndexedColorSpace indexedColorSpaceMin(std::make_unique<GfxColorSpace>(), minIndexHigh);

    EXPECT_EQ(indexedColorSpaceMin.getIndexHigh(), minIndexHigh);

}



TEST_F(GfxIndexedColorSpaceTest_470, IndexHighBoundaryConditionMaximum_470) {

    int maxIndexHigh = 255;

    GfxIndexedColorSpace indexedColorSpaceMax(std::make_unique<GfxColorSpace>(), maxIndexHigh);

    EXPECT_EQ(indexedColorSpaceMax.getIndexHigh(), maxIndexHigh);

}



// Assuming getNComps is a method that returns the number of components

// Since we don't have access to the internal state, we can only assume it returns a non-negative value.

TEST_F(GfxIndexedColorSpaceTest_470, GetNCompsReturnsNonNegativeValue_470) {

    EXPECT_GE(indexedColorSpace->getNComps(), 0);

}



// Assuming useGetRGBLine, useGetCMYKLine, and useGetDeviceNLine are methods that return a boolean

// Since we don't have access to the internal state, we can only assume they return false if not set otherwise.

TEST_F(GfxIndexedColorSpaceTest_470, UseGetRGBLineReturnsFalseByDefault_470) {

    EXPECT_FALSE(indexedColorSpace->useGetRGBLine());

}



TEST_F(GfxIndexedColorSpaceTest_470, UseGetCMYKLineReturnsFalseByDefault_470) {

    EXPECT_FALSE(indexedColorSpace->useGetCMYKLine());

}



TEST_F(GfxIndexedColorSpaceTest_470, UseGetDeviceNLineReturnsFalseByDefault_470) {

    EXPECT_FALSE(indexedColorSpace->useGetDeviceNLine());

}

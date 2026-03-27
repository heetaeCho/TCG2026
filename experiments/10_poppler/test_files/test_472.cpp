#include <gtest/gtest.h>

#include "GfxState.h"



class GfxIndexedColorSpaceTest_472 : public ::testing::Test {

protected:

    std::unique_ptr<GfxColorSpace> baseColorSpace;

    int indexHigh = 255;

    GfxIndexedColorSpace* indexedColorSpace;



    void SetUp() override {

        baseColorSpace = std::make_unique<GfxColorSpace>();

        indexedColorSpace = new GfxIndexedColorSpace(std::move(baseColorSpace), indexHigh);

    }



    void TearDown() override {

        delete indexedColorSpace;

    }

};



TEST_F(GfxIndexedColorSpaceTest_472, GetLookupReturnsNonNullPointer_472) {

    unsigned char* lookup = indexedColorSpace->getLookup();

    EXPECT_NE(lookup, nullptr);

}



TEST_F(GfxIndexedColorSpaceTest_472, GetIndexHighReturnsCorrectValue_472) {

    int result = indexedColorSpace->getIndexHigh();

    EXPECT_EQ(result, indexHigh);

}



TEST_F(GfxIndexedColorSpaceTest_472, GetBaseReturnsNonNullPointer_472) {

    GfxColorSpace* base = indexedColorSpace->getBase();

    EXPECT_NE(base, nullptr);

}

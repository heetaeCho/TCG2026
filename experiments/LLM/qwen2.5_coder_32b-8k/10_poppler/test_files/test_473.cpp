#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"



using namespace testing;



class GfxIndexedColorSpaceTest_473 : public Test {

protected:

    std::unique_ptr<GfxColorSpace> baseColorSpace;

    GfxIndexedColorSpace* indexedColorSpace;



    void SetUp() override {

        baseColorSpace = std::make_unique<NiceMock<StrictMock<GfxColorSpace>>>();

        indexedColorSpace = new GfxIndexedColorSpace(std::move(baseColorSpace), 255);

    }



    void TearDown() override {

        delete indexedColorSpace;

    }

};



TEST_F(GfxIndexedColorSpaceTest_473, GetOverprintMask_ReturnsBaseOverprintMask_473) {

    unsigned int expectedMask = 0x1F;

    EXPECT_CALL(*baseColorSpace, getOverprintMask()).WillOnce(Return(expectedMask));



    unsigned int result = indexedColorSpace->getOverprintMask();



    EXPECT_EQ(result, expectedMask);

}



TEST_F(GfxIndexedColorSpaceTest_473, GetIndexHigh_ReturnsCorrectValue_473) {

    int indexHigh = 255;

    EXPECT_EQ(indexedColorSpace->getIndexHigh(), indexHigh);

}

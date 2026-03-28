#include <gtest/gtest.h>

#include "GfxState.h"



class GfxICCBasedColorSpaceTest_462 : public ::testing::Test {

protected:

    Ref iccProfileStream;

    std::unique_ptr<GfxColorSpace> alt;

    int nCompsA = 3; // Example number of components



    void SetUp() override {

        iccProfileStream.num = 1;

        iccProfileStream.gen = 0;

        alt = std::make_unique<GfxColorSpace>();

    }

};



TEST_F(GfxICCBasedColorSpaceTest_462, GetRefReturnsCorrectRef_462) {

    GfxICCBasedColorSpace colorSpace(nCompsA, std::move(alt), &iccProfileStream);

    EXPECT_EQ(colorSpace.getRef(), iccProfileStream);

}



TEST_F(GfxICCBasedColorSpaceTest_462, GetRefBoundaryCondition_462) {

    Ref emptyIccProfileStream;

    GfxICCBasedColorSpace colorSpace(nCompsA, std::move(alt), &emptyIccProfileStream);

    EXPECT_EQ(colorSpace.getRef(), emptyIccProfileStream);

}



TEST_F(GfxICCBasedColorSpaceTest_462, GetAltReturnsCorrectPointer_462) {

    GfxICCBasedColorSpace colorSpace(nCompsA, std::move(alt), &iccProfileStream);

    EXPECT_EQ(colorSpace.getAlt(), alt.get());

}

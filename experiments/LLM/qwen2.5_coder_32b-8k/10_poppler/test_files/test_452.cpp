#include <gtest/gtest.h>

#include "GfxState.h"



class GfxLabColorSpaceTest : public ::testing::Test {

protected:

    std::unique_ptr<GfxLabColorSpace> colorSpace;



    void SetUp() override {

        colorSpace = std::make_unique<GfxLabColorSpace>();

    }

};



TEST_F(GfxLabColorSpaceTest_452, GetBlackX_ReturnsValidValue_452) {

    EXPECT_DOUBLE_EQ(colorSpace->getBlackX(), 0.0); // Assuming default value is 0.0 for blackX

}



// Additional tests based on the provided interface



TEST_F(GfxLabColorSpaceTest_452, GetWhiteX_ReturnsValidValue_452) {

    EXPECT_DOUBLE_EQ(colorSpace->getWhiteX(), 1.0); // Assuming default value is 1.0 for whiteX

}



TEST_F(GfxLabColorSpaceTest_452, GetBlackY_ReturnsValidValue_452) {

    EXPECT_DOUBLE_EQ(colorSpace->getBlackY(), 0.0); // Assuming default value is 0.0 for blackY

}



TEST_F(GfxLabColorSpaceTest_452, GetWhiteY_ReturnsValidValue_452) {

    EXPECT_DOUBLE_EQ(colorSpace->getWhiteY(), 1.0); // Assuming default value is 1.0 for whiteY

}



TEST_F(GfxLabColorSpaceTest_452, GetBlackZ_ReturnsValidValue_452) {

    EXPECT_DOUBLE_EQ(colorSpace->getBlackZ(), 0.0); // Assuming default value is 0.0 for blackZ

}



TEST_F(GfxLabColorSpaceTest_452, GetWhiteZ_ReturnsValidValue_452) {

    EXPECT_DOUBLE_EQ(colorSpace->getWhiteZ(), 1.0); // Assuming default value is 1.0 for whiteZ

}



TEST_F(GfxLabColorSpaceTest_452, GetAMin_ReturnsValidValue_452) {

    EXPECT_DOUBLE_EQ(colorSpace->getAMin(), -128.0); // Assuming default value is -128.0 for aMin

}



TEST_F(GfxLabColorSpaceTest_452, GetAMax_ReturnsValidValue_452) {

    EXPECT_DOUBLE_EQ(colorSpace->getAMax(), 127.0); // Assuming default value is 127.0 for aMax

}



TEST_F(GfxLabColorSpaceTest_452, GetBMin_ReturnsValidValue_452) {

    EXPECT_DOUBLE_EQ(colorSpace->getBMin(), -128.0); // Assuming default value is -128.0 for bMin

}



TEST_F(GfxLabColorSpaceTest_452, GetBMax_ReturnsValidValue_452) {

    EXPECT_DOUBLE_EQ(colorSpace->getBMax(), 127.0); // Assuming default value is 127.0 for bMax

}

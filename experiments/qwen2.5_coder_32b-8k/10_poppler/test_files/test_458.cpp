#include <gtest/gtest.h>

#include "GfxState.h"



class GfxLabColorSpaceTest : public ::testing::Test {

protected:

    std::unique_ptr<GfxLabColorSpace> colorSpace;



    void SetUp() override {

        colorSpace = std::make_unique<GfxLabColorSpace>();

    }

};



TEST_F(GfxLabColorSpaceTest_458, GetBMax_ReturnsCorrectValue_458) {

    EXPECT_DOUBLE_EQ(colorSpace->getBMax(), 1.0); // Assuming default value is 1.0 for bMax

}



// Additional test cases for other public methods



TEST_F(GfxLabColorSpaceTest_458, Copy_ReturnsNonNullUniquePtr_458) {

    auto copy = colorSpace->copy();

    EXPECT_NE(copy.get(), nullptr);

}



TEST_F(GfxLabColorSpaceTest_458, GetAMin_ReturnsCorrectValue_458) {

    EXPECT_DOUBLE_EQ(colorSpace->getAMin(), 0.0); // Assuming default value is 0.0 for aMin

}



TEST_F(GfxLabColorSpaceTest_458, GetAMax_ReturnsCorrectValue_458) {

    EXPECT_DOUBLE_EQ(colorSpace->getAMax(), 1.0); // Assuming default value is 1.0 for aMax

}



TEST_F(GfxLabColorSpaceTest_458, GetBMin_ReturnsCorrectValue_458) {

    EXPECT_DOUBLE_EQ(colorSpace->getBMin(), 0.0); // Assuming default value is 0.0 for bMin

}

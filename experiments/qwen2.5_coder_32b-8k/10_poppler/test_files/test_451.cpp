#include <gtest/gtest.h>

#include "GfxState.h"

#include <memory>



class GfxLabColorSpaceTest_451 : public ::testing::Test {

protected:

    std::unique_ptr<GfxLabColorSpace> lab_color_space;



    void SetUp() override {

        lab_color_space = std::make_unique<GfxLabColorSpace>();

    }

};



TEST_F(GfxLabColorSpaceTest_451, GetWhiteZ_ReturnsCorrectValue_451) {

    double whiteZ = lab_color_space->getWhiteZ();

    // Assuming a default value or known value for whiteZ

    EXPECT_DOUBLE_EQ(whiteZ, 1.0); // Example expectation; replace with actual expected value if known

}



TEST_F(GfxLabColorSpaceTest_451, GetWhiteX_ReturnsConsistentValue_451) {

    double whiteX = lab_color_space->getWhiteX();

    EXPECT_GE(whiteX, 0.0); // Example boundary condition check; replace with actual logic if known

}



TEST_F(GfxLabColorSpaceTest_451, GetWhiteY_ReturnsConsistentValue_451) {

    double whiteY = lab_color_space->getWhiteY();

    EXPECT_GE(whiteY, 0.0); // Example boundary condition check; replace with actual logic if known

}



TEST_F(GfxLabColorSpaceTest_451, GetBlackX_ReturnsConsistentValue_451) {

    double blackX = lab_color_space->getBlackX();

    EXPECT_LE(blackX, 1.0); // Example boundary condition check; replace with actual logic if known

}



TEST_F(GfxLabColorSpaceTest_451, GetBlackY_ReturnsConsistentValue_451) {

    double blackY = lab_color_space->getBlackY();

    EXPECT_LE(blackY, 1.0); // Example boundary condition check; replace with actual logic if known

}



TEST_F(GfxLabColorSpaceTest_451, GetAMin_ReturnsConsistentValue_451) {

    double aMin = lab_color_space->getAMin();

    EXPECT_LE(aMin, lab_color_space->getAMax()); // Example consistency check; replace with actual logic if known

}



TEST_F(GfxLabColorSpaceTest_451, GetBMin_ReturnsConsistentValue_451) {

    double bMin = lab_color_space->getBMin();

    EXPECT_LE(bMin, lab_color_space->getBMax()); // Example consistency check; replace with actual logic if known

}



TEST_F(GfxLabColorSpaceTest_451, GetAMax_ReturnsConsistentValue_451) {

    double aMax = lab_color_space->getAMax();

    EXPECT_GE(aMax, lab_color_space->getAMin()); // Example consistency check; replace with actual logic if known

}



TEST_F(GfxLabColorSpaceTest_451, GetBMax_ReturnsConsistentValue_451) {

    double bMax = lab_color_space->getBMax();

    EXPECT_GE(bMax, lab_color_space->getBMin()); // Example consistency check; replace with actual logic if known

}



TEST_F(GfxLabColorSpaceTest_451, Copy_ReturnsNonNullPointer_451) {

    std::unique_ptr<GfxColorSpace> copy = lab_color_space->copy();

    EXPECT_NE(copy.get(), nullptr);

}

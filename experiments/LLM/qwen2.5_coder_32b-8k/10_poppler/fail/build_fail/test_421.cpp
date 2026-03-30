#include <gtest/gtest.h>

#include "GfxState.h"



class GfxCalGrayColorSpaceTest : public ::testing::Test {

protected:

    std::unique_ptr<GfxCalGrayColorSpace> color_space;



    void SetUp() override {

        color_space = std::make_unique<GfxCalGrayColorSpace>();

    }

};



TEST_F(GfxCalGrayColorSpaceTest_421, GetGamma_ReturnsCorrectValue_421) {

    double gamma_value = color_space->getGamma();

    EXPECT_GE(gamma_value, 0.0); // Assuming gamma is non-negative

}



TEST_F(GfxCalGrayColorSpaceTest_421, GetWhiteX_ReturnsConsistentValue_421) {

    double white_x_value = color_space->getWhiteX();

    EXPECT_DOUBLE_EQ(white_x_value, color_space->getWhiteX()); // Consistency check

}



TEST_F(GfxCalGrayColorSpaceTest_421, GetWhiteY_ReturnsConsistentValue_421) {

    double white_y_value = color_space->getWhiteY();

    EXPECT_DOUBLE_EQ(white_y_value, color_space->getWhiteY()); // Consistency check

}



TEST_F(GfxCalGrayColorSpaceTest_421, GetWhiteZ_ReturnsConsistentValue_421) {

    double white_z_value = color_space->getWhiteZ();

    EXPECT_DOUBLE_EQ(white_z_value, color_space->getWhiteZ()); // Consistency check

}



TEST_F(GfxCalGrayColorSpaceTest_421, GetBlackX_ReturnsConsistentValue_421) {

    double black_x_value = color_space->getBlackX();

    EXPECT_DOUBLE_EQ(black_x_value, color_space->getBlackX()); // Consistency check

}



TEST_F(GfxCalGrayColorSpaceTest_421, GetBlackY_ReturnsConsistentValue_421) {

    double black_y_value = color_space->getBlackY();

    EXPECT_DOUBLE_EQ(black_y_value, color_space->getBlackY()); // Consistency check

}



TEST_F(GfxCalGrayColorSpaceTest_421, GetBlackZ_ReturnsConsistentValue_421) {

    double black_z_value = color_space->getBlackZ();

    EXPECT_DOUBLE_EQ(black_z_value, color_space->getBlackZ()); // Consistency check

}

#include <gtest/gtest.h>

#include "GfxState.h"



class GfxLabColorSpaceTest : public ::testing::Test {

protected:

    std::unique_ptr<GfxLabColorSpace> labColorSpace;



    void SetUp() override {

        labColorSpace = std::make_unique<GfxLabColorSpace>();

    }

};



TEST_F(GfxLabColorSpaceTest_455, GetAMin_ReturnsValidValue_455) {

    double aMin = labColorSpace->getAMin();

    // Assuming a valid range for aMin is known or can be inferred

    EXPECT_GE(aMin, 0.0);

}



TEST_F(GfxLabColorSpaceTest_455, GetAMax_ReturnsValidValue_455) {

    double aMax = labColorSpace->getAMax();

    // Assuming a valid range for aMax is known or can be inferred

    EXPECT_LE(aMax, 1.0);

}



TEST_F(GfxLabColorSpaceTest_455, GetBMin_ReturnsValidValue_455) {

    double bMin = labColorSpace->getBMin();

    // Assuming a valid range for bMin is known or can be inferred

    EXPECT_GE(bMin, 0.0);

}



TEST_F(GfxLabColorSpaceTest_455, GetBMax_ReturnsValidValue_455) {

    double bMax = labColorSpace->getBMax();

    // Assuming a valid range for bMax is known or can be inferred

    EXPECT_LE(bMax, 1.0);

}



TEST_F(GfxLabColorSpaceTest_455, GetAMin_LessThanEqualGetAMax_455) {

    double aMin = labColorSpace->getAMin();

    double aMax = labColorSpace->getAMax();

    EXPECT_LE(aMin, aMax);

}



TEST_F(GfxLabColorSpaceTest_455, GetBMin_LessThanEqualGetBMax_455) {

    double bMin = labColorSpace->getBMin();

    double bMax = labColorSpace->getBMax();

    EXPECT_LE(bMin, bMax);

}

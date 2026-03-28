#include <gtest/gtest.h>

#include "GfxState.h"



class GfxLabColorSpaceTest_450 : public ::testing::Test {

protected:

    std::unique_ptr<GfxLabColorSpace> labColorSpace;



    void SetUp() override {

        labColorSpace = std::make_unique<GfxLabColorSpace>();

    }

};



TEST_F(GfxLabColorSpaceTest_450, GetWhiteY_ReturnsExpectedValue_450) {

    double whiteY = labColorSpace->getWhiteY();

    // Assuming a known value for testing purposes. Replace with actual expected value if known.

    EXPECT_DOUBLE_EQ(whiteY, 1.0); 

}



TEST_F(GfxLabColorSpaceTest_450, GetWhiteX_ReturnsExpectedValue_450) {

    double whiteX = labColorSpace->getWhiteX();

    // Assuming a known value for testing purposes. Replace with actual expected value if known.

    EXPECT_DOUBLE_EQ(whiteX, 0.95047); 

}



TEST_F(GfxLabColorSpaceTest_450, GetWhiteZ_ReturnsExpectedValue_450) {

    double whiteZ = labColorSpace->getWhiteZ();

    // Assuming a known value for testing purposes. Replace with actual expected value if known.

    EXPECT_DOUBLE_EQ(whiteZ, 1.08883); 

}



TEST_F(GfxLabColorSpaceTest_450, GetBlackX_ReturnsExpectedValue_450) {

    double blackX = labColorSpace->getBlackX();

    // Assuming a known value for testing purposes. Replace with actual expected value if known.

    EXPECT_DOUBLE_EQ(blackX, 0.0); 

}



TEST_F(GfxLabColorSpaceTest_450, GetBlackY_ReturnsExpectedValue_450) {

    double blackY = labColorSpace->getBlackY();

    // Assuming a known value for testing purposes. Replace with actual expected value if known.

    EXPECT_DOUBLE_EQ(blackY, 0.0); 

}



TEST_F(GfxLabColorSpaceTest_450, GetBlackZ_ReturnsExpectedValue_450) {

    double blackZ = labColorSpace->getBlackZ();

    // Assuming a known value for testing purposes. Replace with actual expected value if known.

    EXPECT_DOUBLE_EQ(blackZ, 0.0); 

}



TEST_F(GfxLabColorSpaceTest_450, GetAMin_ReturnsExpectedValue_450) {

    double aMin = labColorSpace->getAMin();

    // Assuming a known value for testing purposes. Replace with actual expected value if known.

    EXPECT_DOUBLE_EQ(aMin, -128.0); 

}



TEST_F(GfxLabColorSpaceTest_450, GetAMax_ReturnsExpectedValue_450) {

    double aMax = labColorSpace->getAMax();

    // Assuming a known value for testing purposes. Replace with actual expected value if known.

    EXPECT_DOUBLE_EQ(aMax, 127.0); 

}



TEST_F(GfxLabColorSpaceTest_450, GetBMin_ReturnsExpectedValue_450) {

    double bMin = labColorSpace->getBMin();

    // Assuming a known value for testing purposes. Replace with actual expected value if known.

    EXPECT_DOUBLE_EQ(bMin, -128.0); 

}



TEST_F(GfxLabColorSpaceTest_450, GetBMax_ReturnsExpectedValue_450) {

    double bMax = labColorSpace->getBMax();

    // Assuming a known value for testing purposes. Replace with actual expected value if known.

    EXPECT_DOUBLE_EQ(bMax, 127.0); 

}



TEST_F(GfxLabColorSpaceTest_450, GetMode_ReturnsExpectedValue_450) {

    GfxColorSpaceMode mode = labColorSpace->getMode();

    // Assuming a known value for testing purposes. Replace with actual expected value if known.

    EXPECT_EQ(mode, gfxDeviceLab); 

}



TEST_F(GfxLabColorSpaceTest_450, GetNComps_ReturnsExpectedValue_450) {

    int nComps = labColorSpace->getNComps();

    // Assuming a known value for testing purposes. Replace with actual expected value if known.

    EXPECT_EQ(nComps, 3); 

}

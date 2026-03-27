#include <gtest/gtest.h>

#include "nikonmn_int.cpp"



namespace Exiv2 {

namespace Internal {



class FlashModeUsesManualScaleTest_457 : public ::testing::Test {

protected:

    // No additional setup/teardown needed for this function

};



TEST_F(FlashModeUsesManualScaleTest_457, Mode6_ReturnsTrue_457) {

    EXPECT_TRUE(flashModeUsesManualScale(6));

}



TEST_F(FlashModeUsesManualScaleTest_457, Mode7_ReturnsTrue_457) {

    EXPECT_TRUE(flashModeUsesManualScale(7));

}



TEST_F(FlashModeUsesManualScaleTest_457, Mode0_ReturnsFalse_457) {

    EXPECT_FALSE(flashModeUsesManualScale(0));

}



TEST_F(FlashModeUsesManualScaleTest_457, Mode1_ReturnsFalse_457) {

    EXPECT_FALSE(flashModeUsesManualScale(1));

}



TEST_F(FlashModeUsesManualScaleTest_457, Mode5_ReturnsFalse_457) {

    EXPECT_FALSE(flashModeUsesManualScale(5));

}



TEST_F(FlashModeUsesManualScaleTest_457, Mode8_ReturnsFalse_457) {

    EXPECT_FALSE(flashModeUsesManualScale(8));

}



TEST_F(FlashModeUsesManualScaleTest_457, NegativeValue_ReturnsFalse_457) {

    EXPECT_FALSE(flashModeUsesManualScale(-1));

}



}  // namespace Internal

}  // namespace Exiv2
